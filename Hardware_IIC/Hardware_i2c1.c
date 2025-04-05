//
// Created by 张荣开 on 2025/4/5.
//

#include "main.h"
#include "../Middlewares/ST/ARM/DSP/Inc/arm_math.h"
#include "i2c.h"
#include "Hardware_i2c1.h"

/************************************************
 ** 从机地址_宏定义
 ***********************************************/
#define _ams5600_Address 0x36
#define _raw_ang_hi 0x0c

/*****************************************************************************
 ** 内部函数
*****************************************************************************/

int16_t Read_Encoder_Angle1(void);
int16_t Read_Encoder_Angle5(void);
int16_t Read_Encoder_Angle6(void);
//其余功能参考stm32f4xx_hal_i2c.c文件



/*****************************************************************************
*函  数：Read_Encoder_Angle1、5、6
*功  能：向指定从机设备，读取指定地址的多个值， 单位：字节
*参  数：无
*返回值：angle
*备  注：写死读取ASM5600的值
*****************************************************************************/
int16_t Read_Encoder_Angle1(void)
{
    int angle1=0;
    uint8_t data[2]={0,0};
    HAL_I2C_Mem_Read(&hi2c1,_ams5600_Address<<1,_raw_ang_hi,I2C_MEMADD_SIZE_8BIT,data,2,50);
    angle1 = (data[0] << 8 | data[1]);
    return angle1 ;
}
int16_t Read_Encoder_Angle5(void)
{
    int angle5=0;
    uint8_t data[2]={0,0};
    HAL_I2C_Mem_Read(&hi2c2,_ams5600_Address << 1,_raw_ang_hi,I2C_MEMADD_SIZE_8BIT,data,2,50);
    angle5 = (data[0] << 8 | data[1]);
    return angle5 ;
}
int16_t Read_Encoder_Angle6(void)
{
    int angle6=0;
    uint8_t data[2]={0,0};
    HAL_I2C_Mem_Read(&hi2c3,_ams5600_Address << 1,_raw_ang_hi,I2C_MEMADD_SIZE_8BIT,data,2,50);
    angle6 = (data[0] << 8 | data[1]);
    return angle6 ;
}