

#ifndef __UART_H
#define __UART_H
#define FOSC 11059200UL 
#define BRT (65536 - FOSC / 9600 / 4) //波特率 9600


extern unsigned char *pchar;

void InitSerialPort(void);					//串口初始化设置
//unsigned char ReceiveByte(void);			//串口查询法接收一个字节
void SendByte(unsigned char sbyte);			//串口发送一个字节
void SendString(unsigned char *pstr);		//串口发送一个字符串


#endif