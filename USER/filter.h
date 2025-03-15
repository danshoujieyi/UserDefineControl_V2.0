//
// Created by ���ο� on 25-1-14.
//

#ifndef ENGINEERING_USERDEFINE_VERSION2_FILTER_H
#define ENGINEERING_USERDEFINE_VERSION2_FILTER_H
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "iic1.h"

#define DATA_SIZE 20        // ���ݴ��ڴ�С
#define ALPHA_MIN 0.1f      // ����Ӧ��ͨ�˲�����Сϵ��
#define ALPHA_MAX 0.9f      // ����Ӧ��ͨ�˲������ϵ��
#define DELTA_MAX 200.0f    // ���Ƕȱ仯��Χ����������Ӧ����ϵ����
#define MAX_ANGLE 360.0f    // ���Ƕ�ֵ

/**
 * @brief �˲����ṹ�嶨��
 */
typedef struct
{
    float angleBuffer[DATA_SIZE];  // ���ݴ��ڣ����ڴ洢��ʷ�Ƕ�ֵ
    uint8_t bufferIndex;           // ��ǰ���ݻ���������
    float filteredAngle;           // �˲���ĽǶ�ֵ
} AngleFilter;

void initAngleFilter(AngleFilter *filter);

void addToBuffer(AngleFilter *filter, float angle);

float calculateMedianAverage(AngleFilter *filter);

float calculateAdaptiveAlpha(float delta);

float adaptiveLowPassFilter(AngleFilter *filter, float newAngle);

float processAngle(AngleFilter *filter, int16_t rawAngle);



#endif //ENGINEERING_USERDEFINE_VERSION2_FILTER_H
