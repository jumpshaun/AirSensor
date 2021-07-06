
#include "stc8.h" 
#include "intrins.h"
#include "delay.h"

#ifndef __IIC_H
#define __IIC_H

#define uchar unsigned char         
#define uint  unsigned int
#define ulong unsigned long
#define IIC_SLAVE_ADDR 0x78	

#define ACK         0             //应答信号
#define NACK        1             //非应答信号

sbit SCL = P5^4;
sbit SDA = P5^5;

void I2CInit(void);
void I2CDelay (uchar t);
void I2CStart(void);
void I2CStop(void);
uchar I2C_Write_Byte(uchar Write_Byte);
uchar I2C_Read_Byte(uchar AckValue);



void IIC_Wait_Ack(void);
void Write_IIC_Byte(u8 IIC_Byte);
void Write_IIC_Command(u8 IIC_Command);
void Write_IIC_Data(u8 IIC_Data);

#endif