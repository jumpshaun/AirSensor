

#ifndef __UART_H
#define __UART_H
#define FOSC 11059200UL 
#define BRT (65536 - FOSC / 9600 / 4) //������ 9600


extern unsigned char *pchar;

void InitSerialPort(void);					//���ڳ�ʼ������
//unsigned char ReceiveByte(void);			//���ڲ�ѯ������һ���ֽ�
void SendByte(unsigned char sbyte);			//���ڷ���һ���ֽ�
void SendString(unsigned char *pstr);		//���ڷ���һ���ַ���


#endif