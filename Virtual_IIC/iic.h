//
// Created by SuperChen on 2025/1/8.
//

#ifndef ENGINEERING_USER_CONTROL_IIC_H
#define ENGINEERING_USER_CONTROL_IIC_H

#include "iic1.h"
#include "iic2.h"
#include "iic3.h"
#include "iic4.h"
#include "iic5.h"
#include "iic6.h"

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
#include "main.h"

typedef enum
{
/* set i2c address */
    _ams5600_Address = 0x36,
    _zmco = 0x00,
    _zpos_hi = 0x01,
    _zpos_lo = 0x02,
    _mpos_hi = 0x03,
    _mpos_lo = 0x04,
    _mang_hi = 0x05,
    _mang_lo = 0x06,
    _conf_hi = 0x07,
    _conf_lo = 0x08,
    _raw_ang_hi = 0x0c,
    _raw_ang_lo = 0x0d,
    _ang_hi = 0x0e,
    _ang_lo = 0x0f,
    _stat = 0x0b,
    _agc = 0x1a,
    _mag_hi = 0x1b,
    _mag_lo = 0x1c,
    _burn = 0xff
}AMS5600Registers_t;

#endif //ENGINEERING_USER_CONTROL_IIC_H
