#ifndef __ADC_H
#define __ADC_H

#define ADCTIM      (*(unsigned char volatile xdata *)0xfea8)
	
void ADCInit(void);
void ADCInitInside(void);
int ADCRead(void); 

extern int *BGV; //�ڲ��ο���ѹֵ�����idata�� 
          //idata��EFH��ַ��Ÿ��ֽ�
		  //idata��F0H��ַ��ŵ��ֽ�
          //��ѹ��λΪ����(mV)
					
#endif