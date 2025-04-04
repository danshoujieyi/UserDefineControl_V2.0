//
// Created by ���ٿ� on 2025/4/4.
//

#include <string.h>
#include "Hardwareiic1.h"
#include "iic.h"
#include "i2c.h"

/***********************************************************************************************************************************
***********************************************************************************************************************************
**���ļ����ơ�  IICHardware.c
**������������  Ӳ��ʵ��IICʱ��
**              ���幦�ܺ���
**
**������˵����
**
***********************************************************************************************************************************/

// �������ܣ�ͨ��Ӳ��I2C��ָ���Ĵ���д��һ���ֽڵ�����
// ����˵����
//   hi2c: I2C��������ڱ�ʶ�����I2C����
//   DevAddress: ���豸��ַ��ע����HAL������Ҫ��7λ��ַ����һλ��Ľ��
//   RegAddress: Ҫд�����ݵļĴ�����ַ
//   data: Ҫд����ֽ�����
void I2C_Write_One_Byte_To_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t data) {
    HAL_StatusTypeDef status;
    uint8_t tx_data[2];
    tx_data[0] = RegAddress;
    tx_data[1] = data;

    // ����HAL�⺯������I2C��ģʽ�µ����ݷ���
    status = HAL_I2C_Master_Transmit(hi2c, DevAddress, tx_data, 2, 100);
    if (status != HAL_OK) {
        // ������ʧ�ܵ����
    }
}

// �������ܣ�ͨ��Ӳ��I2C��ָ���Ĵ���д�����ֽڵ�����
// ����˵����
//   hi2c: I2C��������ڱ�ʶ�����I2C����
//   DevAddress: ���豸��ַ��ע����HAL������Ҫ��7λ��ַ����һλ��Ľ��
//   RegAddress: Ҫд�����ݵļĴ�����ʼ��ַ
//   pData: ָ��Ҫд������������ָ��
//   Size: Ҫд��������ֽ���
void I2C_Write_Multiple_Bytes_To_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t *pData, uint16_t Size) {
    HAL_StatusTypeDef status;
    uint8_t *tx_data = (uint8_t *)malloc(Size + 1);
    if (tx_data == NULL) {
        // �����ڴ����ʧ�ܵ����
        return;
    }
    tx_data[0] = RegAddress;
    memcpy(&tx_data[1], pData, Size);

    status = HAL_I2C_Master_Transmit(hi2c, DevAddress, tx_data, Size + 1, 100);
    free(tx_data);
    if (status != HAL_OK) {
        // ������ʧ�ܵ����
    }
}

// �������ܣ�ͨ��Ӳ��I2C��ָ���Ĵ�����ȡһ���ֽڵ�����
// ����˵����
//   hi2c: I2C��������ڱ�ʶ�����I2C����
//   DevAddress: ���豸��ַ��ע����HAL������Ҫ��7λ��ַ����һλ��Ľ��
//   RegAddress: Ҫ��ȡ���ݵļĴ�����ַ
//   pData: ָ�����ڴ洢��ȡ���ݵ��ֽڵ�ָ��
void I2C_Read_One_Byte_From_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t *pData) {
    HAL_StatusTypeDef status;

    // �ȷ���Ҫ��ȡ�ļĴ�����ַ
    status = HAL_I2C_Master_Transmit(hi2c, DevAddress, &RegAddress, 1, 100);
    if (status != HAL_OK) {
        // �����ͼĴ�����ַʧ�ܵ����
        return;
    }

    // �ٽ���һ���ֽڵ�����
    status = HAL_I2C_Master_Receive(hi2c, DevAddress, pData, 1, 100);
    if (status != HAL_OK) {
        // �����������ʧ�ܵ����
    }
}

// �������ܣ�ͨ��Ӳ��I2C��ָ���Ĵ�����ȡ����ֽڵ�����
// ����˵����
//   hi2c: I2C��������ڱ�ʶ�����I2C����
//   DevAddress: ���豸��ַ��ע����HAL������Ҫ��7λ��ַ����һλ��Ľ��
//   RegAddress: Ҫ��ȡ���ݵļĴ�����ʼ��ַ
//   pData: ָ�����ڴ洢��ȡ���ݵ������ָ��
//   Size: Ҫ��ȡ�������ֽ���
void I2C_Read_Multiple_Bytes_From_Register(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t RegAddress, uint8_t *pData, uint16_t Size) {
    HAL_StatusTypeDef status;

    // �ȷ���Ҫ��ȡ�ļĴ�����ַ
    status = HAL_I2C_Master_Transmit(hi2c, DevAddress, &RegAddress, 1, 100);
    if (status != HAL_OK) {
        // �����ͼĴ�����ַʧ�ܵ����
        return;
    }

    // �ٽ��ն���ֽڵ�����
    status = HAL_I2C_Master_Receive(hi2c, DevAddress, pData, Size, 100);
    if (status != HAL_OK) {
        // �����������ʧ�ܵ����
    }
}

int16_t Hardware_getRawAngle1(void)
{
    int getRaw1=0;
    uint8_t Raw1[2]={0,0};
    I2C_Read_Multiple_Bytes_From_Register(&hi2c1, _ams5600_Address,_stat,Raw1,2);
    getRaw1 = (Raw1[0] << 8 | Raw1[1]);
    return getRaw1;
}