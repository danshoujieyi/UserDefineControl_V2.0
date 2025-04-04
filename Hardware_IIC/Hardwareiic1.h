//
// Created by 24319 on 2025/4/4.
//

#ifndef ENGINEERING_USERDEFINE_VERSION2_HARDWAREIIC1_H
#define ENGINEERING_USERDEFINE_VERSION2_HARDWAREIIC1_H

#include "stm32f4xx_hal_i2c.h"
int16_t Hardware_getRawAngle1(void);
void I2C_Write_One_Byte_To_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t data);
void I2C_Write_Multiple_Bytes_To_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t *pData, uint16_t Size);
void I2C_Read_One_Byte_From_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t *pData);
void I2C_Read_Multiple_Bytes_From_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t *pData, uint16_t Size);

#endif //ENGINEERING_USERDEFINE_VERSION2_HARDWAREIIC1_H
