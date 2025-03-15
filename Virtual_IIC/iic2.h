//
// Created by SuperChen on 2025/1/8.
//

#ifndef ENGINEERING_USER_CONTROL_IIC2_H
#define ENGINEERING_USER_CONTROL_IIC2_H


/***********************************************************************************************************************************
 ***********************************************************************************************************************************
 **【文件名称】  i2c_moni.h
 **【功能描述】  模拟IIC时序
 **              定义引脚、定义全局结构体、声明全局函数
 **
 **【适用平台】  STM32F103 + 标准库v3.5 + keil5
 **
 **【移植说明】  引脚修改：在i2c_moni.h文件中修改，以方便IIC总线复用、代码复用
 **              器件地址：在各设备文件中修改
 **
 **【更新记录】  2020-03-05  创建
 **              2021-05-03  完善文件格式、注释格式
 **
***********************************************************************************************************************************/
#include <stm32f407xx.h>
#include <stdio.h>
//#include "main.h"
#include "iic.h"

// SCL
#define I2C_MONI_SCL_GPIO2      IIC_SCL2_GPIO_Port
#define I2C_MONI_SCL_PIN2       IIC_SCL2_Pin
// SDA
#define I2C_MONI_SDA_GPIO2      IIC_SDA2_GPIO_Port
#define I2C_MONI_SDA_PIN2       IIC_SDA2_Pin

/*****************************************************************************
 * 移植

 * 声明  全局函数
 * 数量：1个初始化， 4个读写
//****************************************************************************/
//void IICSoft_Init(void);          // 初始化所用引脚
//
//uint8_t   IICSoft_ReadByte    (uint8_t addr, uint8_t reg, uint8_t* byte);               // 向从机读一字节; 从机地址, 数据或者寄存器地址，数据
//uint8_t   IICSoft_ReadBueffer (uint8_t addr, uint8_t reg, uint8_t* buf,  uint8_t len);  // 向从机读多字节; 从机地址, 数据或者寄存器地址，数据
//uint8_t   IICSoft_WriteByte   (uint8_t addr, uint8_t reg, uint8_t  byte);               // 向从机写一字节; 从机地址, 数据或者寄存器地址，数据
//uint8_t   IICSoft_WriteBuffer (uint8_t addr, uint8_t reg, uint8_t* buf,  uint8_t len);  // 向从机写多字节; 从机地址, 数据或者寄存器地址，数据




int16_t getRawAngle2(void);



#endif //ENGINEERING_USER_CONTROL_IIC2_H
