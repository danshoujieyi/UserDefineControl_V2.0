//
// Created by ���ο� on 25-1-14.
//

#include "filter.h"

/**
 * @brief ��ʼ���˲���
 * @param filter ָ���˲����ṹ���ָ��
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
 * @brief ��ӽǶ�ֵ�����ݻ�����
 * @param filter ָ���˲����ṹ���ָ��
 * @param angle �µĽǶ�ֵ
 */
void addToBuffer(AngleFilter *filter, float angle)
{
    filter->angleBuffer[filter->bufferIndex] = angle;                // ����ֵд�뻺����
    filter->bufferIndex = (filter->bufferIndex + 1) % DATA_SIZE;     // ѭ����������
}

/**
 * @brief ������λֵƽ����ȥ�������Сֵ��ƽ����
 * @param filter ָ���˲����ṹ���ָ��
 * @retval ��λֵƽ�����
 */
float calculateMedianAverage(AngleFilter *filter)
{
    float sortedBuffer[DATA_SIZE];
    float sum = 0.0f;

    // ���ƻ�����������������
    for (int i = 0; i < DATA_SIZE; i++)
    {
        sortedBuffer[i] = filter->angleBuffer[i];
    }

    // ð�����򣨴�С����
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

    // ȥ�����ֵ����Сֵ������ƽ��ֵ
    for (int i = 1; i < DATA_SIZE - 1; i++)
    {
        sum += sortedBuffer[i];
    }

    return sum / (DATA_SIZE - 2);
}

/**
 * @brief ����Ӧ�˲�ϵ������
 * @param delta ���ݱ仯��
 * @retval ��̬�˲�ϵ�� ��
 */
float calculateAdaptiveAlpha(float delta)
{
    // ��������Ӧ������ӳ�䵽 [ALPHA_MIN, ALPHA_MAX]
    if (delta > DELTA_MAX) delta = DELTA_MAX; // �������仯��
    return ALPHA_MIN + (ALPHA_MAX - ALPHA_MIN) * (delta / DELTA_MAX);
}

/**
 * @brief ����Ӧ��ͨ�˲���
 * @param filter ָ���˲����ṹ���ָ��
 * @param newAngle �µĽǶ�ֵ
 * @retval �˲���ĽǶ�ֵ
 */
float adaptiveLowPassFilter(AngleFilter *filter, float newAngle)
{
    // �����Խ 0 �ȣ������ 359�� �� 1�㣩�����в���
    if (newAngle - filter->filteredAngle > 180.0f)
    {
        newAngle -= 360.0f;
    }
    else if (filter->filteredAngle - newAngle > 180.0f)
    {
        newAngle += 360.0f;
    }

    // �������ݱ仯�� ��
    float delta = fabs(newAngle - filter->filteredAngle);

    // ��̬�����˲�ϵ�� ��
    float alpha = calculateAdaptiveAlpha(delta);

    // Ӧ�õ�ͨ�˲���ʽ
    filter->filteredAngle = alpha * newAngle + (1 - alpha) * filter->filteredAngle;

    // ����������� 0-360 ��Χ
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
 * @brief ����������Ƕȵ������к���
 * @param filter ָ���˲����ṹ���ָ��
 * @param rawAngle ��������ԭʼ�Ƕ�ֵ (0 - 4095)
 * @retval �˲���ĽǶ�ֵ
 */
float processAngle(AngleFilter *filter, int16_t rawAngle)
{
    // ת��Ϊ�Ƕ�ֵ
    float degree = convertRawAngleToDegrees1(rawAngle);

    // ��ӵ�������
    addToBuffer(filter, degree);

    // ������λֵƽ��
    float medianAverage = calculateMedianAverage(filter);

    // Ӧ������Ӧ��ͨ�˲�
    return adaptiveLowPassFilter(filter, medianAverage);
}
