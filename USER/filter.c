//
// Created by 刘嘉俊 on 25-1-14.
//

#include "filter.h"

/**
 * @brief 初始化滤波器
 * @param filter 指向滤波器结构体的指针
 */
void initAngleFilter(AngleFilter *filter)
{
    for (int i = 0; i < DATA_SIZE; i++)
    {
        filter->angleBuffer[i] = 0.0f;
    }
    filter->bufferIndex = 0;
    filter->filteredAngle = 0.0f;
}

/**
 * @brief 添加角度值到数据缓冲区
 * @param filter 指向滤波器结构体的指针
 * @param angle 新的角度值
 */
void addToBuffer(AngleFilter *filter, float angle)
{
    filter->angleBuffer[filter->bufferIndex] = angle;                // 将新值写入缓冲区
    filter->bufferIndex = (filter->bufferIndex + 1) % DATA_SIZE;     // 循环更新索引
}

/**
 * @brief 计算中位值平均（去掉最大最小值后平均）
 * @param filter 指向滤波器结构体的指针
 * @retval 中位值平均结果
 */
float calculateMedianAverage(AngleFilter *filter)
{
    float sortedBuffer[DATA_SIZE];
    float sum = 0.0f;

    // 复制缓冲区数据用于排序
    for (int i = 0; i < DATA_SIZE; i++)
    {
        sortedBuffer[i] = filter->angleBuffer[i];
    }

    // 冒泡排序（从小到大）
    for (int i = 0; i < DATA_SIZE - 1; i++)
    {
        for (int j = 0; j < DATA_SIZE - i - 1; j++)
        {
            if (sortedBuffer[j] > sortedBuffer[j + 1])
            {
                float temp = sortedBuffer[j];
                sortedBuffer[j] = sortedBuffer[j + 1];
                sortedBuffer[j + 1] = temp;
            }
        }
    }

    // 去掉最大值和最小值，计算平均值
    for (int i = 1; i < DATA_SIZE - 1; i++)
    {
        sum += sortedBuffer[i];
    }

    return sum / (DATA_SIZE - 2);
}

/**
 * @brief 自适应滤波系数计算
 * @param delta 数据变化率
 * @retval 动态滤波系数 α
 */
float calculateAdaptiveAlpha(float delta)
{
    // 线性自适应函数，映射到 [ALPHA_MIN, ALPHA_MAX]
    if (delta > DELTA_MAX) delta = DELTA_MAX; // 限制最大变化率
    return ALPHA_MIN + (ALPHA_MAX - ALPHA_MIN) * (delta / DELTA_MAX);
}

/**
 * @brief 自适应低通滤波器
 * @param filter 指向滤波器结构体的指针
 * @param newAngle 新的角度值
 * @retval 滤波后的角度值
 */
float adaptiveLowPassFilter(AngleFilter *filter, float newAngle)
{
    // 如果跨越 0 度（例如从 359° 到 1°），进行补偿
    if (newAngle - filter->filteredAngle > 180.0f)
    {
        newAngle -= 360.0f;
    }
    else if (filter->filteredAngle - newAngle > 180.0f)
    {
        newAngle += 360.0f;
    }

    // 计算数据变化率 Δ
    float delta = fabs(newAngle - filter->filteredAngle);

    // 动态计算滤波系数 α
    float alpha = calculateAdaptiveAlpha(delta);

    // 应用低通滤波公式
    filter->filteredAngle = alpha * newAngle + (1 - alpha) * filter->filteredAngle;

    // 将结果调整回 0-360 范围
    if (filter->filteredAngle < 0.0f)
    {
        filter->filteredAngle += 360.0f;
    }
    else if (filter->filteredAngle >= 360.0f)
    {
        filter->filteredAngle -= 360.0f;
    }

    return filter->filteredAngle;
}

/**
 * @brief 处理编码器角度的主运行函数
 * @param filter 指向滤波器结构体的指针
 * @param rawAngle 编码器的原始角度值 (0 - 4095)
 * @retval 滤波后的角度值
 */
float processAngle(AngleFilter *filter, int16_t rawAngle)
{
    // 转换为角度值
    float degree = convertRawAngleToDegrees1(rawAngle);

    // 添加到缓冲区
    addToBuffer(filter, degree);

    // 计算中位值平均
    float medianAverage = calculateMedianAverage(filter);

    // 应用自适应低通滤波
    return adaptiveLowPassFilter(filter, medianAverage);
}
