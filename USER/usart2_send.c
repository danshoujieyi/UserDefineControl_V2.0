//
// Created by 刘嘉俊 on 25-1-9.
//

#include <string.h>
#include "usart2_send.h"
#include "stm32f4xx_hal.h"
#include "crc8_crc16.h"

extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_tx;

uint8_t dma_tx_buffer[2][FRAME_SIZE]; // 双缓冲区
uint8_t current_buffer = 0;           // 当前缓冲区索引
volatile uint8_t dma_busy = 0;        // DMA状态标志位

extern QueueHandle_t xQueue;    // FreeRTOS 队列句柄
static float encoder_values[6] = {0, 0, 0, 0, 0, 0};              // 存储6个编码器值
static float angles[6] = {0.0f}; // 用于临时存储队列中读取的编码器值

void PackData(float *values, uint16_t data_length, RobotArmController_t *tx_data)
{
    static uint8_t frame_seq = 0; // 帧序号
    // 设置帧头
    tx_data->frame_header.sof = 0xA5;                      // 起始字节
    tx_data->frame_header.data_length = data_length;        // 数据段长度
    tx_data->frame_header.seq = frame_seq++;                // 包序号
    if (frame_seq == 0) frame_seq = 1;  // 防止包序号溢出，最多支持255个包序号


    // 计算帧头CRC8
    tx_data->frame_header.crc8 = 0;  // 初始CRC8
    append_CRC8_check_sum((uint8_t *)(&tx_data->frame_header), FRAME_HEADER_LENGTH);  // 添加CRC8校验

    // 设置命令码
    tx_data->cmd_id = ARM_CONTROLLER_CMD_ID;

    // 数据区：6个float（每个编码器值4字节）
    // 设置数据段
    uint8_t *p;
    for (int i = 0; i < 6; i++) {
        p = (uint8_t *)&values[i];
        tx_data->data[i*4] = p[0]; // 第一个字节
        tx_data->data[i*4+1] = p[1]; // 第二个字节
        tx_data->data[i*4+2] = p[2]; // 第三个字节
        tx_data->data[i*4+3] = p[3]; // 第四个字节
    }


    // 计算帧尾CRC16
    tx_data->frame_tail = 0;  // 初始CRC16
    append_CRC16_check_sum((uint8_t *)tx_data, FRAME_SIZE );  // 添加CRC16校验
}

void DMA_Send_Frame(void)
{
    if (dma_busy == 0) { // 判断DMA是否空闲
        dma_busy = 1;    // 标志位置为忙

        // 启动DMA发送
       HAL_UART_Transmit_DMA(&huart2, dma_tx_buffer[current_buffer], FRAME_SIZE);

        // 切换到另一个缓冲区
        current_buffer = (current_buffer == 0) ? 1 : 0;
    }
}

// DMA发送完成回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2) {
        dma_busy = 0; // 标志位置为空闲
    }
}

void USART2_SendEntry(void const * argument)
{
    /* USER CODE BEGIN USART2_SendEntry */

    /* Infinite loop */
    for(;;)
    {
        // 从队列中获取编码器值（阻塞时间为 10ms，如果队列为空，则跳过）
        if (xQueueReceive(xQueue, angles, 0) == pdPASS) {
            // 更新全局的 encoder_values 数组（可选）
            for (int i = 0; i < 6; i++) {
                encoder_values[i] = angles[i];
            }

            // 打包数据到tx_data结构中
            RobotArmController_t tx_data = {0};  // 定义数据包结构体
            PackData(encoder_values, 30, &tx_data);  // 打包数据帧
            // 将打包后的数据写入DMA缓冲区
            memcpy(dma_tx_buffer[current_buffer], &tx_data, FRAME_SIZE);
            // 启动 DMA 发送
            DMA_Send_Frame();
        }

        vTaskDelay(12); // 延迟 10ms

    }
    /* USER CODE END USART2_SendEntry */
}



//// 数据拼接函数：将帧头、命令码、数据段、帧尾拼接成完整的数据包
//void Data_Concatenation(RobotArmController_t *tx_data, uint8_t *data, uint16_t data_length)
//{
//    // 设置帧头
//    tx_data->frame_header.sof = 0xA5;                      // 起始字节
//    tx_data->frame_header.data_length = data_length;        // 数据段长度
//    tx_data->frame_header.seq = frame_seq++;                      // 包序号
//    if (frame_seq == 0) frame_seq = 1;  // 防止包序号溢出，最多支持255个包序号
//
//    // 计算帧头CRC8
//    append_CRC8_check_sum((uint8_t *)(&tx_data->frame_header), FRAME_HEADER_LENGTH);  // 添加CRC8校验
//
//    // 设置命令码
//    tx_data->cmd_id = ARM_CONTROLLER_CMD_ID;
//
//    // 设置数据段
//    memcpy(tx_data->data, data, data_length);               // 填充数据段
//
//    // 计算帧尾CRC16
//    append_CRC16_check_sum((uint8_t *)tx_data, FRAME_SIZE);     // 添加CRC16校验
//}