//
// Created by 刘嘉俊 on 25-1-9.
//

#include "encode_iic.h"
#include "filter.h"
#include "arm_math.h"
#include "Hardware_i2c1.h"

// 定义AS5600读取的角度值
static float angles_encoder[6]; // 全局共享数组
static int16_t raw_angle[6] = {0}; // 全局共享变量
static AngleFilter filters[6]; // 定义 6 个编码器对应的滤波器

extern QueueHandle_t xQueue;      // 队列句柄

void EncoderEntry(void const * argument)
{
    /* USER CODE BEGIN EncoderEntry */

    // 初始化每个滤波器
    for (int i = 0; i < 6; i++)
    {
        initAngleFilter(&filters[i]);
    }

    /* Infinite loop */
    for(;;)
    {
        // 模拟获取编码器的原始角度值（实际中应替换为传感器接口）
        raw_angle[0] = Read_Encoder_Angle1();
        angles_encoder[0] = processAngle(&filters[0], raw_angle[0]);// 处理编码器角度，获取滤波后的角度值
        raw_angle[1] = getRawAngle2();
        angles_encoder[1] = processAngle(&filters[1], raw_angle[1]);
        raw_angle[2] = getRawAngle3();
        angles_encoder[2] = processAngle(&filters[2], raw_angle[2]);
        raw_angle[3] = getRawAngle4();
        angles_encoder[3] = processAngle(&filters[3], raw_angle[3]);
        raw_angle[4] = Read_Encoder_Angle5();
        angles_encoder[4] = processAngle(&filters[4], raw_angle[4]);
        raw_angle[5] = Read_Encoder_Angle6();
        angles_encoder[5] = processAngle(&filters[5], raw_angle[5]);

        // 将编码器数据放入队列
        xQueueSend(xQueue, angles_encoder, 0);

        vTaskDelay(1); // 延迟 10ms

    }
    /* USER CODE END EncoderEntry */
}

