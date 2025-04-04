//
// Created by 张荣开 on 2025/4/4.
//

#include <string.h>
#include "Hardwareiic1.h"
#include "iic.h"
#include "i2c.h"

/***********************************************************************************************************************************
***********************************************************************************************************************************
**【文件名称】  IICHardware.c
**【功能描述】  硬件实现IIC时序
**              定义功能函数
**
**【函数说明】
**
***********************************************************************************************************************************/

// 函数功能：通过硬件I2C向指定寄存器写入一个字节的数据
// 参数说明：
//   hi2c: I2C句柄，用于标识具体的I2C外设
//   DevAddress: 从设备地址，注意在HAL库中需要是7位地址左移一位后的结果
//   RegAddress: 要写入数据的寄存器地址
//   data: 要写入的字节数据
void I2C_Write_One_Byte_To_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t data) {
    HAL_StatusTypeDef status;
    uint8_t tx_data[2];
    tx_data[0] = RegAddress;
    tx_data[1] = data;

    // 调用HAL库函数进行I2C主模式下的数据发送
    status = HAL_I2C_Master_Transmit(hi2c, DevAddress, tx_data, 2, 100);
    if (status != HAL_OK) {
        // 处理发送失败的情况
    }
}

// 函数功能：通过硬件I2C向指定寄存器写入多个字节的数据
// 参数说明：
//   hi2c: I2C句柄，用于标识具体的I2C外设
//   DevAddress: 从设备地址，注意在HAL库中需要是7位地址左移一位后的结果
//   RegAddress: 要写入数据的寄存器起始地址
//   pData: 指向要写入的数据数组的指针
//   Size: 要写入的数据字节数
void I2C_Write_Multiple_Bytes_To_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t *pData, uint16_t Size) {
    HAL_StatusTypeDef status;
    uint8_t *tx_data = (uint8_t *)malloc(Size + 1);
    if (tx_data == NULL) {
        // 处理内存分配失败的情况
        return;
    }
    tx_data[0] = RegAddress;
    memcpy(&tx_data[1], pData, Size);

    status = HAL_I2C_Master_Transmit(hi2c, DevAddress, tx_data, Size + 1, 100);
    free(tx_data);
    if (status != HAL_OK) {
        // 处理发送失败的情况
    }
}

// 函数功能：通过硬件I2C从指定寄存器读取一个字节的数据
// 参数说明：
//   hi2c: I2C句柄，用于标识具体的I2C外设
//   DevAddress: 从设备地址，注意在HAL库中需要是7位地址左移一位后的结果
//   RegAddress: 要读取数据的寄存器地址
//   pData: 指向用于存储读取数据的字节的指针
void I2C_Read_One_Byte_From_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t *pData) {
    HAL_StatusTypeDef status;

    // 先发送要读取的寄存器地址
    status = HAL_I2C_Master_Transmit(hi2c, DevAddress, &RegAddress, 1, 100);
    if (status != HAL_OK) {
        // 处理发送寄存器地址失败的情况
        return;
    }

    // 再接收一个字节的数据
    status = HAL_I2C_Master_Receive(hi2c, DevAddress, pData, 1, 100);
    if (status != HAL_OK) {
        // 处理接收数据失败的情况
    }
}

// 函数功能：通过硬件I2C从指定寄存器读取多个字节的数据
// 参数说明：
//   hi2c: I2C句柄，用于标识具体的I2C外设
//   DevAddress: 从设备地址，注意在HAL库中需要是7位地址左移一位后的结果
//   RegAddress: 要读取数据的寄存器起始地址
//   pData: 指向用于存储读取数据的数组的指针
//   Size: 要读取的数据字节数
void I2C_Read_Multiple_Bytes_From_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t *pData, uint16_t Size) {
    HAL_StatusTypeDef status;

    // 先发送要读取的寄存器地址
    status = HAL_I2C_Master_Transmit(hi2c, DevAddress, &RegAddress, 1, 100);
    if (status != HAL_OK) {
        // 处理发送寄存器地址失败的情况
        return;
    }

    // 再接收多个字节的数据
    status = HAL_I2C_Master_Receive(hi2c, DevAddress, pData, Size, 100);
    if (status != HAL_OK) {
        // 处理接收数据失败的情况
    }
}

int16_t Hardware_getRawAngle1(void)
{
    int getRaw1=0;
    uint8_t Raw1[2]={0,0};
    I2C_Read_Multiple_Bytes_From_Register(&hi2c1, _ams5600_Address,_stat,Raw1,2);
    getRaw1 = (Raw1[0] << 8 | Raw1[1]);
    return getRaw1;
}