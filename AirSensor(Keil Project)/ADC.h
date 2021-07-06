#ifndef __ADC_H
#define __ADC_H

#define ADCTIM      (*(unsigned char volatile xdata *)0xfea8)
	
void ADCInit(void);
void ADCInitInside(void);
int ADCRead(void); 

extern int *BGV; //内部参考电压值存放在idata中 
          //idata的EFH地址存放高字节
		  //idata的F0H地址存放低字节
          //电压单位为毫伏(mV)
					
#endif