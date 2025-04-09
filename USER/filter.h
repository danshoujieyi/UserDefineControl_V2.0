//
// Created by 刘嘉俊 on 25-1-14.
//

#ifndef ENGINEERING_USERDEFINE_VERSION2_FILTER_H
#define ENGINEERING_USERDEFINE_VERSION2_FILTER_H
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "iic1.h"

#define DATA_SIZE 5        // 数据窗口大小
#define ALPHA_MIN 0.3f      // 自适应低通滤波的最小系数
#define ALPHA_MAX 0.7f      // 自适应低通滤波的最大系数
#define DELTA_MAX 175.0f    // 最大角度变化范围（用于自适应调整系数）

/**
 * @brief 滤波器结构体定义
 */
typedef struct
{
    float angleBuffer[DATA_SIZE];  // 数据窗口，用于存储历史角度值
    uint8_t bufferIndex;           // 当前数据缓冲区索引
    float filteredAngle;           // 滤波后的角度值
} AngleFilter;

void initAngleFilter(AngleFilter *filter);

void addToBuffer(AngleFilter *filter, float angle);

float calculateMedianAverage(AngleFilter *filter);

float calculateAdaptiveAlpha(float delta);

float adaptiveLowPassFilter(AngleFilter *filter, float newAngle);

float processAngle(AngleFilter *filter, int16_t rawAngle);



#endif //ENGINEERING_USERDEFINE_VERSION2_FILTER_H
