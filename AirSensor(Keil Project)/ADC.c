
#include "stc8.h"
#include "ADC.h"
#include "intrins.h"


void ADCInit() 
{
	P_SW2 |= 0x80;//访问特殊功能寄存器
	 ADCTIM = 0x3f;//设置ADC内部时序
	P_SW2 &= 0x7f;//关闭
	ADCCFG = 0x2f;//数据右对齐，设置工作频率
	ADC_CONTR = 0x83;//开启，设置P3.3为通道,
 }
 void ADCInitInside() 
{
	P_SW2 |= 0x80;//访问特殊功能寄存器
	 ADCTIM = 0x3f;//设置ADC内部时序
	P_SW2 &= 0x7f;//关闭
	ADCCFG = 0x2f;//数据右对齐，设置工作频率
	ADC_CONTR = 0x8f;//开启，0x8f为内部参考电压
 }
int ADCRead() 
{
 int res; 
 ADC_CONTR |= 0x40;//启动AD转换
 _nop_();
 _nop_(); 
 while (!(ADC_CONTR & 0x20)); //检测到转换结束
 ADC_CONTR &= ~0x20;//清标志位
 res = (ADC_RES << 8) | ADC_RESL; //送数据
 return res; 
}