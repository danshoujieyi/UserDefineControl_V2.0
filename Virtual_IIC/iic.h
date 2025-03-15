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
 **���ļ����ơ�  i2c_moni.h
 **������������  ģ��IICʱ��
 **              �������š�����ȫ�ֽṹ�塢����ȫ�ֺ���
 **
 **������ƽ̨��  STM32F103 + ��׼��v3.5 + keil5
 **
 **����ֲ˵����  �����޸ģ���i2c_moni.h�ļ����޸ģ��Է���IIC���߸��á����븴��
 **              ������ַ���ڸ��豸�ļ����޸�
 **
 **�����¼�¼��  2020-03-05  ����
 **              2021-05-03  �����ļ���ʽ��ע�͸�ʽ
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
