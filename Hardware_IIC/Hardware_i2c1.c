//
// Created by 张荣开 on 2025/4/5.
//

#include "main.h"
#include "arm_math.h"
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
void KalmanFilter_Init(KalmanFilter *kf, double initial_x_hat, double initial_P, double Q, double R);
double KalmanFilter_Update(KalmanFilter *kf, double measurement);
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



/*****************************************************************************
*函  数：KalmanFilter_Init
*功  能：初始化一维卡尔曼滤波器的参数，为后续滤波操作做准备
*参  数：
*       kf：指向 KalmanFilter 结构体的指针，用于存储卡尔曼滤波器的状态信息
*       initial_x_hat：初始状态估计值，代表对系统初始状态的预估
*       initial_P：初始估计误差协方差，反映初始状态估计的不确定性
*       Q：系统噪声协方差，体现系统模型的不确定性
*       R：测量噪声协方差，体现测量值的不确定性
*返回值：无
*备  注：该函数需在使用卡尔曼滤波更新操作前调用，以正确设置滤波器参数
*****************************************************************************/
void KalmanFilter_Init(KalmanFilter *kf, double initial_x_hat, double initial_P, double Q, double R) {
    kf->x_hat = initial_x_hat;
    kf->P = initial_P;
    kf->Q = Q;
    kf->R = R;
}



/*****************************************************************************
*函  数：KalmanFilter_Update
*功  能：执行一维卡尔曼滤波的预测和更新步骤，根据测量值更新系统状态估计
*参  数：
*       kf：指向 KalmanFilter 结构体的指针，包含卡尔曼滤波器的当前状态信息
*       measurement：当前的测量值，例如编码器测量得到的角度值
*返回值：更新后的系统状态估计值
*备  注：该函数需在 KalmanFilter_Init 初始化后调用，每次获取新的测量值时都可调用此函数进行滤波
*****************************************************************************/
double KalmanFilter_Update(KalmanFilter *kf, double measurement) {
    // 预测步骤
    double x_hat_minus = kf->x_hat;
    double P_minus = kf->P + kf->Q;

    // 更新步骤
    double K = P_minus / (P_minus + kf->R);
    kf->x_hat = x_hat_minus + K * (measurement - x_hat_minus);
    kf->P = (1 - K) * P_minus;

    return kf->x_hat;
}