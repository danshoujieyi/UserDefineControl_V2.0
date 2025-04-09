//
// Created by ���ٿ� on 2025/4/5.
//

#include "main.h"
#include "arm_math.h"
#include "i2c.h"
#include "Hardware_i2c1.h"

/************************************************
 ** �ӻ���ַ_�궨��
 ***********************************************/
#define _ams5600_Address 0x36
#define _raw_ang_hi 0x0c

/*****************************************************************************
 ** �ڲ�����
*****************************************************************************/

int16_t Read_Encoder_Angle1(void);
int16_t Read_Encoder_Angle5(void);
int16_t Read_Encoder_Angle6(void);
void KalmanFilter_Init(KalmanFilter *kf, double initial_x_hat, double initial_P, double Q, double R);
double KalmanFilter_Update(KalmanFilter *kf, double measurement);
//���๦�ܲο�stm32f4xx_hal_i2c.c�ļ�

/*****************************************************************************
*��  ����Read_Encoder_Angle1��5��6
*��  �ܣ���ָ���ӻ��豸����ȡָ����ַ�Ķ��ֵ�� ��λ���ֽ�
*��  ������
*����ֵ��angle
*��  ע��д����ȡASM5600��ֵ
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
*��  ����KalmanFilter_Init
*��  �ܣ���ʼ��һά�������˲����Ĳ�����Ϊ�����˲�������׼��
*��  ����
*       kf��ָ�� KalmanFilter �ṹ���ָ�룬���ڴ洢�������˲�����״̬��Ϣ
*       initial_x_hat����ʼ״̬����ֵ�������ϵͳ��ʼ״̬��Ԥ��
*       initial_P����ʼ�������Э�����ӳ��ʼ״̬���ƵĲ�ȷ����
*       Q��ϵͳ����Э�������ϵͳģ�͵Ĳ�ȷ����
*       R����������Э������ֲ���ֵ�Ĳ�ȷ����
*����ֵ����
*��  ע���ú�������ʹ�ÿ������˲����²���ǰ���ã�����ȷ�����˲�������
*****************************************************************************/
void KalmanFilter_Init(KalmanFilter *kf, double initial_x_hat, double initial_P, double Q, double R) {
    kf->x_hat = initial_x_hat;
    kf->P = initial_P;
    kf->Q = Q;
    kf->R = R;
}



/*****************************************************************************
*��  ����KalmanFilter_Update
*��  �ܣ�ִ��һά�������˲���Ԥ��͸��²��裬���ݲ���ֵ����ϵͳ״̬����
*��  ����
*       kf��ָ�� KalmanFilter �ṹ���ָ�룬�����������˲����ĵ�ǰ״̬��Ϣ
*       measurement����ǰ�Ĳ���ֵ����������������õ��ĽǶ�ֵ
*����ֵ�����º��ϵͳ״̬����ֵ
*��  ע���ú������� KalmanFilter_Init ��ʼ������ã�ÿ�λ�ȡ�µĲ���ֵʱ���ɵ��ô˺��������˲�
*****************************************************************************/
double KalmanFilter_Update(KalmanFilter *kf, double measurement) {
    // Ԥ�ⲽ��
    double x_hat_minus = kf->x_hat;
    double P_minus = kf->P + kf->Q;

    // ���²���
    double K = P_minus / (P_minus + kf->R);
    kf->x_hat = x_hat_minus + K * (measurement - x_hat_minus);
    kf->P = (1 - K) * P_minus;

    return kf->x_hat;
}