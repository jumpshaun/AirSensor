//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STC89C52RC,����12M  ��Ƭ��������ѹ3.3V��5V
//QDtech-OLEDҺ������ for C51
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/9/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================��Դ����================================================//
// OLEDģ��                C51��Ƭ��
//   VCC         ��       DC 5V/3.3V      //OLED����Դ��
//   GND         ��          GND          //OLED����Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪIIC
// OLEDģ��                C51��Ƭ��
//   SDA        ��           P15          //OLED��SPIд�ź�
//=======================================Һ���������߽���==========================================//
// OLEDģ��                C51��Ƭ��
//   SCL        ��           P17          //OLED��SPIʱ���ź�
//=========================================����������=========================================//
//��ģ�鲻���������ܣ����Բ���Ҫ����������
****************************************************************************************************/	
/***************************************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
****************************************************************************************************/		
//#include "stdlib.h"
#include "stdio.h"
#include "oled.h"
#include "gui.h"
#include "test.h"
//#include "bmp.h"


/*****************************************************************************
 * @name       :void TEST_MainPage(void)
 * @date       :2018-08-27 
 * @function   :Drawing the main Interface of the Comprehensive Test Program
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
/*void TEST_MainPage(void)
{	
	GUI_ShowString(37,0,"OLED TEST",8,1);
	GUI_ShowString(25,1,"0.91\" SSD1306",8,1);
	GUI_ShowString(46,2,"32X128",8,1);
	GUI_ShowString(19,3,"www.lcdwiki.com",8,1);
	delay_ms(1500);		
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void Test_Color(void)
 * @date       :2018-08-27 
 * @function   :Color fill test(white,black)
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
/*void Test_Color(void)
{
	 GUI_Fill(0,0,WIDTH-1,7,0);
	 GUI_ShowString(10,1,"BLACK",16,1);
	 delay_ms(1000);	
	 GUI_Fill(0,0,WIDTH-1,7,1);
	 GUI_ShowString(10,1,"WHITE",16,0);
	 delay_ms(1500);
}

/*****************************************************************************
 * @name       :void TEST_English(void)
 * @date       :2018-08-27 
 * @function   :English display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
/*void TEST_English(void)
{
	GUI_ShowString(0,1,"6x8:abcdefghijklmnopqrstuvwxyz",8,1);
	delay_ms(1000);
	GUI_ShowString(0,0,"8x16:abcdefghijklmnopqrstuvwxyz",16,1);
	delay_ms(1000);
	OLED_Clear(0); 
	GUI_ShowString(0,1,"6x8:ABCDEFGHIJKLMNOPQRSTUVWXYZ",8,1);
	delay_ms(1000);
	GUI_ShowString(0,0,"8x16:ABCDEFGHIJKLMNOPQRSTUVWXYZ",16,1);
	delay_ms(1500);
}

/*****************************************************************************
 * @name       :void TEST_Number_Character(void) 
 * @date       :2018-08-27 
 * @function   :number and character display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
/*void TEST_Number_Character(void) 
{
	GUI_Fill(0,0,WIDTH-1,1,0);
	GUI_ShowString(0,0,"6x8:!\"#$%&'()*+,-./:;<=>?@[]\\^_`~{}|",8,1);
	GUI_ShowNum(68,1,1234567890,10,8,1);
	GUI_Fill(0,2,WIDTH-1,3,1);
	GUI_ShowString(0,2,"6x8:!\"#$%&'()*+,-./:;<=>?@[]\\^_`~{}|",8,0);
	GUI_ShowNum(68,3,1234567890,10,8,0);
	delay_ms(1000);
	OLED_Clear(0); 
  GUI_ShowString(0,0,"8x16:!\"#$%&'()*+,-./:;<=>?@[]\\^_`~{}|",16,1);
	GUI_ShowNum(48,2,1234567890,10,16,1);
	delay_ms(1500);
	OLED_Clear(0);
}

/*****************************************************************************
 * @name       :void TEST_Chinese(void)
 * @date       :2018-08-27
 * @function   :chinese display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
/*void TEST_Chinese(void)
{	
	GUI_ShowString(45,0,"16x16",8,1);
	GUI_ShowCHinese(16,2,16,"ȫ�����Ӽ���",1);
	delay_ms(1000);
	GUI_Fill(0,0,WIDTH-1,3,1);
	GUI_ShowString(45,0,"16x16",8,0);
	GUI_ShowCHinese(16,2,16,"ȫ�����Ӽ���",0);
	delay_ms(1000);
	OLED_Clear(0);
	GUI_ShowString(45,0,"24x24",8,1);
	GUI_ShowCHinese(16,1,24,"ȫ������",1);
	delay_ms(1000);
	OLED_Clear(0);
	GUI_ShowCHinese(0,0,32,"ȫ������",1);	
  delay_ms(1000);
	OLED_Clear(0);
}*/

/*****************************************************************************
 * @name       :void TEST_BMP(void)
 * @date       :2018-08-27 
 * @function   :BMP monochromatic picture display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
//void TEST_BMP(void)
//{



//	GUI_DrawBMP(0,0,128,16, BMP2, 1);
//	delay_ms(1000);
//}
void TEST_Co2_Tvoc(void)
{
	GUI_ShowString(12,1,"TVOC/Ppb",8,1);//8+6*8+8	
	GUI_ShowString(71,1,"CO2/Ppm",8,1);//64+11+6*7+11
}
void TEST_Temp_Himi(void)
{
	GUI_ShowString(15,1,"TEMP/*C",8,1);//11+6*7+11	(*���Ÿ���Ϊ��)
	GUI_ShowString(74,1,"HIMI/%",8,1);//64+14+6*6+14
}

//void TEST_CO2TVOC(void)
//{
//	GUI_DrawBMP(0,9,128,11, BMP7, 1);
//	delay_ms(1000);
//}
//void TEST_TEMPHIMI(void)
//{
//	GUI_DrawBMP(0,9,128,11, BMP8, 1);
//	delay_ms(1000);
//}
