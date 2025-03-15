//
// Created by 刘嘉俊 on 25-1-9.
//

#ifndef USART_ENCODER_ENCODER_IIC_H
#define USART_ENCODER_ENCODER_IIC_H
#include "cmsis_os.h"

#include <stdio.h>



//// 假设这些函数已经修改为接受地址参数
//uint8_t detectMagnet(uint8_t address);
//uint16_t getRawAngle(uint8_t address);
//float convertRawAngleToDegrees(uint16_t rawdata);
//
//void Programe_Run(void)
//{
//    for(int i = 0; i < 6; i++) {
//        encoders[i].dect = detectMagnet(encoderAddresses[i]);
//        encoders[i].rawdata = getRawAngle(encoderAddresses[i]);
//        encoders[i].degress = convertRawAngleToDegrees(encoders[i].rawdata);
//        printf("Encoder %d:\r\n", i);
//        printf("检测到磁铁状态: %d\r\n", encoders[i].dect);
//        printf("原始数据是: %d\r\n", encoders[i].rawdata);
//        printf("角度是: %f\r\n", encoders[i].degress);
//    }
//}

#endif //USART_ENCODER_ENCODER_IIC_H
