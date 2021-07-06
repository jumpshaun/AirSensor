
#include "stc8.h"
#include "ADC.h"
#include "intrins.h"


void ADCInit() 
{
	P_SW2 |= 0x80;//�������⹦�ܼĴ���
	 ADCTIM = 0x3f;//����ADC�ڲ�ʱ��
	P_SW2 &= 0x7f;//�ر�
	ADCCFG = 0x2f;//�����Ҷ��룬���ù���Ƶ��
	ADC_CONTR = 0x83;//����������P3.3Ϊͨ��,
 }
 void ADCInitInside() 
{
	P_SW2 |= 0x80;//�������⹦�ܼĴ���
	 ADCTIM = 0x3f;//����ADC�ڲ�ʱ��
	P_SW2 &= 0x7f;//�ر�
	ADCCFG = 0x2f;//�����Ҷ��룬���ù���Ƶ��
	ADC_CONTR = 0x8f;//������0x8fΪ�ڲ��ο���ѹ
 }
int ADCRead() 
{
 int res; 
 ADC_CONTR |= 0x40;//����ADת��
 _nop_();
 _nop_(); 
 while (!(ADC_CONTR & 0x20)); //��⵽ת������
 ADC_CONTR &= ~0x20;//���־λ
 res = (ADC_RES << 8) | ADC_RESL; //������
 return res; 
}