//
// Created by SuperChen on 2025/1/8.
//

#include "iic1.h"

/***********************************************************************************************************************************
***********************************************************************************************************************************
**���ļ����ơ�  bsp_IICSoft.c
**������������  ģ��IICʱ��
**              ���幦�ܺ���
**
**������˵����
**
***********************************************************************************************************************************/


/************************************************
 ** ��ƽ���Ƽ�_�궨��
 ***********************************************/
#define SCL_L      (I2C_MONI_SCL_GPIO1->BSRR = (I2C_MONI_SCL_PIN1 << 16))
#define SCL_H      (I2C_MONI_SCL_GPIO1->BSRR =  I2C_MONI_SCL_PIN1)
#define SDA_L      (I2C_MONI_SDA_GPIO1->BSRR = (I2C_MONI_SDA_PIN1 << 16))
#define SDA_H      (I2C_MONI_SDA_GPIO1->BSRR =  I2C_MONI_SDA_PIN1)
#define SDA_READ   ((I2C_MONI_SDA_GPIO1->IDR & I2C_MONI_SDA_PIN1)?1:0)       // ���øĳ�����ģʽ���ܶ�


/*****************************************************************************
 ** �ڲ�����
*****************************************************************************/


static void     isBusy (void);          // ��������Ƿ����
static void     start  (void);          // ��ʼ�ź�
static void     stop   (void);          // ֹͣ�ź�
static void     ackYes (void);          // ����Ӧ���ź�
static void     ackNo  (void);          // ������Ӧ���ź�
static uint8_t  waitForAck(void);       // �ȴ�Ӧ���ź�

static void     sendByte(uint8_t data);      // ����һ���ֽ�
static uint8_t  readByte(uint8_t ack);       // ��ȡһ���ֽ�


/*****************************************************************************
*��  ����IICSoft_Init
*��  �ܣ���ʼ��ģ��IIC����
*��  ����
*����ֵ��
*��  ע��
*****************************************************************************/
void IICSoft_Init(void)
{
    // ʹ��SCL���Ŷ˿�ʱ��
    if(I2C_MONI_SCL_GPIO1 == GPIOA)   __HAL_RCC_GPIOA_CLK_ENABLE();
    if(I2C_MONI_SCL_GPIO1 == GPIOB)   __HAL_RCC_GPIOB_CLK_ENABLE();
    if(I2C_MONI_SCL_GPIO1 == GPIOC)   __HAL_RCC_GPIOC_CLK_ENABLE();
    if(I2C_MONI_SCL_GPIO1 == GPIOD)   __HAL_RCC_GPIOD_CLK_ENABLE();
    if(I2C_MONI_SCL_GPIO1 == GPIOE)   __HAL_RCC_GPIOF_CLK_ENABLE();
    // ʹ��SDA���Ŷ˿�ʱ��
    if(I2C_MONI_SDA_GPIO1 == GPIOA)  __HAL_RCC_GPIOA_CLK_ENABLE();
    if(I2C_MONI_SDA_GPIO1 == GPIOB)  __HAL_RCC_GPIOB_CLK_ENABLE();
    if(I2C_MONI_SDA_GPIO1 == GPIOC)  __HAL_RCC_GPIOC_CLK_ENABLE();
    if(I2C_MONI_SDA_GPIO1 == GPIOD)  __HAL_RCC_GPIOD_CLK_ENABLE();
    if(I2C_MONI_SDA_GPIO1 == GPIOE)  __HAL_RCC_GPIOF_CLK_ENABLE();

    // �������Ź���ģʽ: ��©���
    GPIO_InitTypeDef G;
    G.Pin   = I2C_MONI_SCL_PIN1;
    G.Mode  = GPIO_MODE_OUTPUT_OD;
    G.Speed = 500000000 ;
    HAL_GPIO_Init(I2C_MONI_SCL_GPIO1, &G);
    delayUs(1);

    G.Pin   = I2C_MONI_SDA_PIN1;
    HAL_GPIO_Init(I2C_MONI_SDA_GPIO1, &G);
    delayUs(1);

    SCL_L ;
    delayUs(1);
    SDA_H ;
}

//// ������ʱ************************
//static void delayUs( uint32_t times)
//{
//    times=times*7;
//    while(--times)
//        __nop();
//}

//void delayUs(uint32_t times)
//{
//    uint32_t tickstart = HAL_GetTick();
//    while ((HAL_GetTick() - tickstart) < times);
//}


// �ж������Ƿ��ڿ���״̬�������ǣ���ѭ�����ṩSCLʱ��������ֱ���ӻ��ͷ�SDA��
static void isBusy(void)
{
    uint32_t i=500;                  // ��Լ3ms
    //SDA_IN ();
    while((SDA_READ) == 0 && (--i))  // ��ȡsda���ϵĵ�ƽ״̬���͵�ƽ˵�����߱��ӻ����ƣ��ߵ�ƽ��˵�����߿��У�����׼�����Ϳ�ʼ�ź�
    {
        SCL_L;
        delayUs(1);
        SCL_H ;
        delayUs(1);
    }
//    if(i==0)    printf("\r\n IIC���߳�ʱ����!! \r\n");   // ������ʾ
}



/*****************************************************************************
 * ��  ����start
 * ��  �ܣ���ʼ�ź� ��SCL�ߵ�ƽ�ڼ䣬SDA�ɸ���� ����)
*****************************************************************************/
static void start(void)
{
    isBusy ();               // �ж������Ƿ��ڿ���״̬

    SCL_L;   delayUs(1);
    SDA_H;   delayUs(1);

    SCL_H;   delayUs(1);
    SDA_L;   delayUs(1);     // ��SCL�ߵ�ƽ��䣬 SDA�ɸ���� ����
    SCL_L;   delayUs(1);     // ��SCL����,ǯסSCL��,׼����������
}



/*****************************************************************************
 * ��  ����stop
 * ��  �ܣ�����ֹͣ�ź� ����SCL�ߵ�ƽ��䣬 SDA�ɵ���� ���䣩
*****************************************************************************/
static void stop(void)
{
    SCL_L;   delayUs(1);
    SDA_L;   delayUs(1);

    SCL_H;   delayUs(1);
    SDA_H ;  delayUs(1);     // ��SCL�ߵ�ƽ��䣬 SDA�ɵ���� ����
}



/*****************************************************************************
 * ��  ����ackYes
 * ��  �ܣ���������Ӧ���ź� ���ڵ�9��ʱ������SAL�ߵ�ƽ�ڼ�, SDA���ֵ͵�ƽ��
 *         ����������һ���ֽ����ݺ���������ACK֪ͨ�ӻ�һ���ֽ���������ȷ����
*****************************************************************************/
static void ackYes(void)
{
    SCL_L;    delayUs(1);
    SDA_L;    delayUs(1);

    SCL_H;    delayUs(1);   // ʹSDA����һ��ʱ�ӵĵ͵�ƽ
    SCL_L;    delayUs(1);

    SDA_H ;   delayUs(1);   // ����Ҫ: �������ͷ�SDA��,�ӻ����ܻ�ȡ����Ȩ
}



/*****************************************************************************
 * ��  ����ackNo
 * ��  �ܣ�����������Ӧ���ź� ���ڵ�9��ʱ������SAL�ߵ�ƽ�ڼ�, SDA���ָߵ�ƽ��
 *         ����������һ���ֽ����ݺ���������NACK֪ͨ�ӻ������������Ա���������ֹͣ�ź�
*****************************************************************************/
static void ackNo(void)
{
    SCL_L;    delayUs(1);
    SDA_H;    delayUs(1);

    SCL_H;    delayUs(1);   // ʹSDA����һ��ʱ�ӵĸߵ�ƽ
    SCL_L;    delayUs(1);

    SDA_H;    delayUs(1);   // ����Ҫ: �������ͷ�SDA��,�ӻ����ܻ�ȡ����Ȩ
}


/*****************************************************************************
 * ��  ����waitForAck
 * ��  �ܣ���ȡӦ���źŻ��߷�Ӧ���ź�
 *         ��ЧӦ���źţ��ӻ���9��SCL=0ʱ��SDA���ӻ����ͣ�����SCL=1ʱ��SDA��ȻΪ��
 *
 * ����ֵ�� 0=�յ�Ӧ���ź�,   1=�յ���Ӧ���ź�
 * ��  ע��
*****************************************************************************/
static uint8_t waitForAck(void)
{
    uint8_t  d=0;

    SCL_L;    delayUs(1);
    SDA_H;    delayUs(1);        // �����ͷ�SDA�ߣ�ʹ���߿��У��Ա�ӻ��ܹ���Ӧ��Ϣ

    SCL_H;    delayUs(1);        // �ȴ�10us; ����׼ģʽ100kbit/s
    d=SDA_READ;

    SCL_L;    delayUs(1);
    SDA_H;    delayUs(1);        // �����ͷ�SDA�ߣ�ʹ���߿��У��Ա�ӻ��ܹ���Ӧ��Ϣ

    if(d)
        return 1;                 // ���ط�Ӧ���ź�
    else
        return 0;                 // ����Ӧ���ź�
}



/*****************************************************************************
 * ��  ���� sendByte
 * ��  �ܣ� ���һ���ֽ�
 * ��  ����
 * ����ֵ�� 0=�յ�Ӧ���ź�,   1=�յ���Ӧ���ź�
 * ��  ע��
*****************************************************************************/
static void sendByte(uint8_t data)
{
    for(uint8_t i=0; i<8; i++)
    {
        SCL_L;     delayUs(1);

        (data&0x80)? SDA_H : SDA_L;
        data<<=1;  delayUs(1);

        SCL_H;     delayUs(1);
    }

    SCL_L;    delayUs(1);
    SDA_H;    delayUs(1);      // �����ͷ�SDA�ߣ�ʹ�����߿��У��Ա�ӻ��ܹ�������Ӧ��Ϣ����ǯ��SCL��
}

/*****************************************************************************
 * ��  ���� readByte
 * ��  �ܣ� ��ȡһ���ֽ�
 * ��  ���� ack=0��������û�����꣬ ack=1:����������ȫ���������
 * ����ֵ�� ��ȡ����Byteֵ
 * ��  ע�� ��ȡ�ӻ����͵����ݺ󣬲���������Ӧ���źŻ��Ƿ�Ӧ���ź�
*****************************************************************************/
static uint8_t readByte(uint8_t ack)
{
    uint8_t data=0;

    for(uint8_t i=0; i<8; i++)
    {
        SCL_H;    delayUs(1);
        data<<=1;
        if(SDA_READ)  data|=0x01;
        SCL_L;    delayUs(1);
    }

    if(ack) ackNo ();               // 1, ��Ӧ��
    else    ackYes();               // 0, Ӧ��

    return  data;
}



/*****************************************************************************
 * ��  ���� IICSoft_ReadByte
 * ��  �ܣ� ��ָ���ӻ��豸����ȡָ����ַ��һ��ֵ�� ��λ���ֽ�
 * ��  ���� slave: �ӻ���ַ
 *          addr�� ���ݵ�ַ
 *          *buf�� ����Ҫ�洢�ĵ�ַ
 * ����ֵ�� 0=�ɹ��� 1=ʧ��
 * ��  ע�� ע�⣬ʱ���е��ر�
*****************************************************************************/
uint8_t IICSoft_ReadByte(uint8_t slave, uint8_t addr, uint8_t *buf)
{
    start ();                     // ��ʼ�ź�
    sendByte (slave<<1 | 0);      // �ӻ���ַ,��д���� , 0д1��
    if(waitForAck())
    {
        stop();
        return 1;
    }

    sendByte(addr);               // ���ݵ�ַ
    if(waitForAck())
    {
        stop();
        return 1;
    }

    // д���ݺͶ���������ʱ������ д�Ƚϼ򵥣������ݣ��ٷ�һ����ʼ�źš��ж�����Ĵӻ���ַ
    start();                      // ��ʼ�ź�
    sendByte(slave<<1 | 1);       // �ӻ���ַ,�������� ��  0д1��
    if(waitForAck())
    {
        stop();
        return 1;
    }

    *buf=readByte(1);             // ��ֵ, ������ackNo;
    stop();

    return 0;
}



/*****************************************************************************
 * ��  ���� IICSoft_ReadBueffer
 * ��  �ܣ� ��ָ���ӻ��豸����ȡָ����ַ�Ķ��ֵ�� ��λ���ֽ�
 * ��  ���� uint8_t slave   �ӻ���ַ
 *          uint8_t addr    ���ݵ�ַ
 *          uint8_t data    Ҫд�������(1�ֽ�)
 * ����ֵ�� 0=�ɹ��� 1=ʧ��
 * ��  ע�� ע�⣬ʱ���е��ر�
*****************************************************************************/
uint8_t IICSoft_ReadBueffer(uint8_t slave, uint8_t addr, uint8_t *buf, uint8_t len)
{
    start ();                     // ��ʼ�ź�
    sendByte (slave<<1 | 0);      // �ӻ���ַ,��д���� , 0д1��
    if(waitForAck())              // �ȴ�ACK
    {
        stop();
        return 1;
    }

    sendByte(addr);               // ���ݵ�ַ
    if(waitForAck())              // �ȴ�ACK
    {
        stop();
        return 1;
    }

    // д����ʱ������ �����ݣ��ٷ�һ����ʼ�źš��ж�����Ĵӻ���ַ
    start();                      // ��ʼ�ź�
    sendByte(slave<<1 | 1);       // �ӻ���ַ,�������� ��  0д1��
    if(waitForAck())              // �ȴ�ACK
    {
        stop();
        return 1;
    }


    while(len)
    {
        if(len==1)  *buf=readByte(1);   // ���һ���ֽڣ������ݺ����NACK
        else        *buf=readByte(0);   // �����ݺ����ACK

        len--;
        buf++;
    }

    stop ();                      // ����һ��ֹͣ�ź�
    return 0;
}


/*****************************************************************************
 * ��  ���� IICSoft_WriteByte
 * ��  �ܣ� ���ӻ�ĳ��ַд��һ���ֽ�
 * ��  ���� uint8_t slave   �ӻ���ַ
 *          uint8_t addr    ���ݵ�ַ
 *          uint8_t data    Ҫд�������(1�ֽ�)
 * ����ֵ�� 0=�ɹ��� 1=ʧ��
 * ��  ע�� ʱ������ǲ�ͬ��
*****************************************************************************/
uint8_t IICSoft_WriteByte(uint8_t slave, uint8_t addr, uint8_t data)
{
    start ();                     // ��ʼ�ź�
    sendByte (slave<<1 | 0);      // �ӻ���ַ,��д���� , 0д1��
    if(waitForAck())
    {
        stop();
        return 1;                 // ���ӻ���ַ����ʧ�ܣ��ͷ���
    }

    sendByte(addr);               // ���ݵ�ַ
    if(waitForAck())
    {
        stop();
        return 1;                 // ������ʧ�ܣ��ͷ���
    }

    sendByte(data);               // �������ݣ� д���ݺͶ���������ʱ����������һ��ǰ
    if(waitForAck())
    {
        stop ();
        return 1;                 // ����д��ʧ��
    }

    stop();                       // д����ɣ�����ֹͣ�ź�
    return 0;
}

// ���ӻ�д����ֽ�����
uint8_t IICSoft_WriteBuffer(uint8_t slave, uint8_t addr, uint8_t *buf, uint8_t len)
{
    start ();                     // ��ʼ�ź�
    sendByte (slave<<1 | 0);      // �ӻ���ַ,��д���� , 0д1��
    if(waitForAck())
    {
        stop();
        return 1;                 // ������ʧ�ܣ��ͷ���
    }

    sendByte(addr);               // ���ݵ�ַ
    if(waitForAck())
    {
        stop();
        return 1;                 // ������ʧ�ܣ��ͷ���
    }

    for(uint8_t i=0; i<len; i++)
    {
        sendByte(buf[i]);         // ����
        if(waitForAck())          // ÿһ���ֽڶ�Ҫ�ȴӻ�Ӧ��
        {
            stop ();
            return 1;             // ����д��ʧ��
        }
    }

    stop();                       // д����ɣ�����ֹͣ�ź�
    return 0;
}

/*******************************************************
 Method: detectMagnet
 In: none
 Out: 1 if magnet is detected, 0 if not
 Description: reads status register and examines the
 MH bit
******************************************************/
int detectMag1=0;
uint8_t detectMagnet1(void)
{
    uint8_t magStatus;
    uint8_t retVal = 0;
    /*0 0 MD ML MH 0 0 0*/
    /* MD high = AGC minimum overflow, Magnet to strong */
    /* ML high = AGC Maximum overflow, magnet to weak*/
    /* MH high = magnet detected*/
    IICSoft_ReadByte(_ams5600_Address,_stat,&magStatus);
    detectMag1++;

    if(magStatus & 0x20)
        retVal = 1;

    return retVal;
}

/*******************************************************
 Method: getRawAngle
 In: none
 Out: value of raw angle register
 Description: gets raw value of magnet position.
 start, end, and max angle settings do not apply
******************************************************/

int16_t getRawAngle1(void)
{
    int getRaw1=0;
    uint8_t Raw1[2]={0,0};
    IICSoft_ReadBueffer(_ams5600_Address, _raw_ang_hi, (uint8_t *) Raw1, 2);
    getRaw1 = (Raw1[0] << 8 | Raw1[1]);
    return getRaw1;

}

/*******************************************************
 Function: convertRawAngleToDegrees
 In: angle data from AMS_5600::getRawAngle
 Out: human readable degrees as float
 Description: takes the raw angle and calculates
 float value in degrees.
******************************************************/
float convertRawAngleToDegrees1(int16_t newAngle)
{
    /* Raw data reports 0 - 4095 segments, which is 0.087 of a degree */
    float retVal = newAngle * 0.087890625;
    return retVal;
}

/**
 * @brief �����к���
 * @retval �˲���ĽǶ�ֵ
 */
float Programe_Run1(void)
{
    float degree1=0;
    float rawdata1=0;

    rawdata1 = getRawAngle1();
    degree1 = convertRawAngleToDegrees1(rawdata1);


    return degree1;
}





