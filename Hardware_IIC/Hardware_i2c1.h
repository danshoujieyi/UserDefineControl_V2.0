//
// Created by 24319 on 2025/4/5.
//

#ifndef ENGINEERING_USERDEFINE_VERSION2_HARDWARE_I2C1_H
#define ENGINEERING_USERDEFINE_VERSION2_HARDWARE_I2C1_H


// 定义卡尔曼滤波器结构体
typedef struct {
    double x_hat;  // 状态估计值
    double P;      // 估计误差协方差
    double Q;      // 系统噪声协方差
    double R;      // 测量噪声协方差
} KalmanFilter;

int16_t Read_Encoder_Angle1(void);
int16_t Read_Encoder_Angle5(void);
int16_t Read_Encoder_Angle6(void);
void KalmanFilter_Init(KalmanFilter *kf, double initial_x_hat, double initial_P, double Q, double R);
double KalmanFilter_Update(KalmanFilter *kf, double measurement);
#endif //ENGINEERING_USERDEFINE_VERSION2_HARDWARE_I2C1_H
