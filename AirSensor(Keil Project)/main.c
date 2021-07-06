#include "stc8.h" 
#include "intrins.h"
#include "delay.h"
#include "uart.h"
#include "iic.h"
#include "SGP30.h" 
#include "SHT3X.H"
#include "bmp.h"
#include "oled.h"
#include "gui.h"
#include "test.h"
#include "ADC.h"
#include "8266.h"

int Temp,Tempshi,Tempge;   //�¶�
int Himi,Himishi,Himige;   //ʪ��
sbit EN_SGP30 = P3^2;

int *BGV; //�ڲ��ο���ѹֵ�����idata�� 
          //idata��EFH��ַ��Ÿ��ֽ�
		  //idata��F0H��ַ��ŵ��ֽ�
          //��ѹ��λΪ����(mV)

void main() 
{

		ulong dat;
		uchar flag = 0;
 		uint co2Data,TVOCData;
		int res,reference; 
		uint vcc; 
		char Buffer[20]={0};
		int i;
		P3M0 = 0x00; //P3 ����ģʽ
		P3M1 = 0x00; 
		P5M0 = 0x00; 
		P5M1 = 0x00;
		P33=1;
		delay_ms(5000);
		InitSerialPort();
		SGP30_Init(); 
//		printf("SGP30 init!\r\n");
		OLED_Clear(0); 			//������ȫ�ڣ�
		OLED_Init();			  //��ʼ��OLED             
//		printf("OLED init!\r\n");
		GUI_DrawBMP(0,0,128,32, BMP7, 1);
		BGV = (int idata *)0xef;
		ADCInitInside() ;	// ��ȡ�ο���ѹ
		for (i=0; i<32; i++)//��8������
		{
			res += ADCRead();
		}
		res >>= 5;//ȡƽ��ֵ
		reference =11900/res;//50000
		ADCInit(); 		
//		printf("ADC init!\r\n");
//		printf("SerialPort init!\r\n");
		EN_SGP30 = 0;				
		SHT3XInit();   // ��ʼ�� SHT3XоƬ
//		printf("SHT3X init!\r\n");		
		init_8266();
//		printf("Start!\r\n");
		
		while(1) 
		{ 
				// SGP30��ȡco2,TVOC����	
				SGP30_ad_write(0x20,0x08);//Measure_air_quality
				dat = SGP30_ad_read();
				co2Data = (dat & 0xffff0000) >> 16;
				TVOCData = dat & 0x0000ffff;		
				if(co2Data == 400 && TVOCData == 0 && flag == 0)
				{
//					SendString("SGP sensor probing!\r\n");
				}
				else
				{
//					printf("TVOC:%d Ppb , co2:%d Ppm\r\n",TVOCData,co2Data);
					flag = 1;
				}
									
				SHT3X_XHGetTempAndHumi(&Temp,&Himi);   //�����ʪ����Ϣ
				Tempshi=Temp/10;
				Tempge=Temp%10;
				Himishi=Himi/10;
				Himige=Himi%10;
//				printf("Temperature:%d 'C Humidity:%d % \r\n",Temp,Himi);


				// ��ȡ��Դ��ѹ
				res = 0; 
				for (i=0; i<8; i++)//��8������
				{
					res += ADCRead();
				}
				res >>= 3;//ȡƽ��ֵ
				vcc=res*reference;
								
//				printf("Vin:%d mV,ref %d/10mV, res %d\r\n",vcc/10,reference,res);
				

				Buffer[0]= (Temp & 0xff00) >> 8;
				Buffer[1]=  Temp & 0x00ff;
				Buffer[2]= (Himi & 0xff00) >> 8;
				Buffer[3]=  Himi & 0x00ff;
				Buffer[4]= (co2Data & 0xff00) >> 8;
				Buffer[5]=  co2Data & 0x00ff;
				Buffer[6]= (TVOCData & 0xff00) >> 8;
				Buffer[7]=  TVOCData & 0x00ff;
				Buffer[8]= (vcc & 0xff00) >> 8;
				Buffer[9]=  vcc & 0x00ff;
				printf("AT+CIPSEND=0,20\r\n"); //TCP����
				delay_ms(20);
				for (i=0; i < 20; i++)  
						printf("%c", Buffer[i]); 
						delay_ms(20);
				printf("   \r\n");
				delay_ms(1700);
				//OLED��ʾ
				vcc = 42000; //
				OLED_Clear(0);
				OLED_Init();			  //��ʼ��OLED
				GUI_DrawBMP(0,0,11,8, BMP1, 1);/*����wifi*/
				if(vcc>41000)
					GUI_DrawBMP(114,0,14,8, BMP3, 1);/*������14*/
				else if(vcc>39000)
					GUI_DrawBMP(114,0,14,8, BMP4, 1);/*2/3����14*/
				else if(vcc>37000)
					GUI_DrawBMP(114,0,14,8, BMP5, 1);/*1/3����14*/
				else
					GUI_DrawBMP(114,0,14,8, BMP6, 1);/*0/3����14*/
				TEST_Co2_Tvoc();        //CO2,����������ʶ��ʾ
				if(co2Data == 400 && TVOCData == 0 && flag == 0)
				{
					GUI_ShowChar(18,2,('W'-26),16,1);//ɾ��δ�õ�ASCII���˳�򲹳�
					GUI_ShowChar(26,2,('A'-7),16,1);
					GUI_ShowChar(34,2,('I'-14),16,1);
					GUI_ShowChar(42,2,('T'-24),16,1);
					GUI_ShowChar(78,2,('W'-26),16,1);
					GUI_ShowChar(86,2,('A'-7),16,1);
					GUI_ShowChar(94,2,('I'-14),16,1);
					GUI_ShowChar(102,2,('T'-24),16,1);
				}
				else
				{
					GUI_ShowNum(22,2,TVOCData,3,16,1);
					GUI_ShowNum(78,2,co2Data,3,16,1);
				}			
				delay_ms(2000);
				
				OLED_Clear(0);
				GUI_DrawBMP(0,0,11,8, BMP1, 1);/*����wifi*/
				if(vcc>41000)
					GUI_DrawBMP(114,0,14,8, BMP3, 1);/*������14*/
				else if(vcc>39000)
					GUI_DrawBMP(114,0,14,8, BMP4, 1);/*2/3����14*/
				else if(vcc>37000)
					GUI_DrawBMP(114,0,14,8, BMP5, 1);/*1/3����14*/
				else
					GUI_DrawBMP(114,0,14,8, BMP6, 1);/*0/3����14*/
				TEST_Temp_Himi();        //�¶�,ʪ�ȱ�ʶ��ʾ
				GUI_ShowNum(20,2,Tempshi,2,16,1);
				GUI_ShowChar(36,2,'.',16,1);
				GUI_ShowNum(44,2,Tempge,1,16,1);
				GUI_ShowNum(78,2,Himishi,2,16,1);
				GUI_ShowChar(94,2,'.',16,1);
				GUI_ShowNum(102,2,Himige,1,16,1);
		 }
		
}



		