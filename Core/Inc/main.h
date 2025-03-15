/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "math.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define IIC_SDA6_Pin GPIO_PIN_2
#define IIC_SDA6_GPIO_Port GPIOE
#define DIR6_Pin GPIO_PIN_3
#define DIR6_GPIO_Port GPIOE
#define IIC_SCL1_Pin GPIO_PIN_0
#define IIC_SCL1_GPIO_Port GPIOC
#define IIC_SDA1_Pin GPIO_PIN_1
#define IIC_SDA1_GPIO_Port GPIOC
#define DIR1_Pin GPIO_PIN_3
#define DIR1_GPIO_Port GPIOC
#define IIC_SCL2_Pin GPIO_PIN_2
#define IIC_SCL2_GPIO_Port GPIOA
#define IIC_SDA2_Pin GPIO_PIN_3
#define IIC_SDA2_GPIO_Port GPIOA
#define DIR2_Pin GPIO_PIN_5
#define DIR2_GPIO_Port GPIOA
#define IIC_SCL3_Pin GPIO_PIN_4
#define IIC_SCL3_GPIO_Port GPIOC
#define IIC_SDA3_Pin GPIO_PIN_5
#define IIC_SDA3_GPIO_Port GPIOC
#define DIR3_Pin GPIO_PIN_1
#define DIR3_GPIO_Port GPIOB
#define IIC_SCL4_Pin GPIO_PIN_12
#define IIC_SCL4_GPIO_Port GPIOE
#define IIC_SDA4_Pin GPIO_PIN_13
#define IIC_SDA4_GPIO_Port GPIOE
#define DIR4_Pin GPIO_PIN_15
#define DIR4_GPIO_Port GPIOE
#define IIC_SCL5_Pin GPIO_PIN_12
#define IIC_SCL5_GPIO_Port GPIOB
#define IIC_SDA5_Pin GPIO_PIN_13
#define IIC_SDA5_GPIO_Port GPIOB
#define DIR5_Pin GPIO_PIN_15
#define DIR5_GPIO_Port GPIOB
#define IIC_SCL6_Pin GPIO_PIN_1
#define IIC_SCL6_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */
void delayUs(uint32_t times);

#define Trans_Len 25   //����������
/**
  * @brief  �Զ����ȡ������������ͨѶ֡�ṹ��
  */
//typedef  struct
//{
//    uint8_t HEAD;          /*! ֡ͷ */
//    uint8_t LEN;                    /*! ���ݳ��� */
//    uint8_t DATA[Trans_Len];    /*! �������� 0-5*/
//    uint8_t SC;           /*! ��У�� */
//    uint8_t AC;           /*! ����У�� */
//}__attribute__((packed)) TransType;
//
//TransType Trans_tx_data = {
//        .HEAD = 0xFF,
//        .LEN = Trans_Len,
//        .DATA = {0},
//        .SC = 0,
//        .AC = 0,
//};

//float angle1,angle2,angle3,angle4,angle5,angle6=0;
//uint16_t rawdata1,rawdata2,rawdata3,rawdata4,rawdata5,rawdata6=0;
//float degress1,degress2,degress3,degress4,degress5,degress6 =0;
//#define average_len 10
//#define error 10

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
