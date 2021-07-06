

#include "SGP30.h" 

//��ʼ��IIC�ӿ�
void SGP30_Init(void)
{
	SGP30_ad_write(0x20,0x03);
//	SGP30_ad_write(0x20,0x61);
//	SGP30_ad_write(0x01,0x00);
}

void SGP30_ad_write(uchar a, uchar b)
{
  	I2CStart();
  	I2C_Write_Byte(SGP30_write); //����������ַ+дָ��
  	I2C_Write_Byte(a);		//���Ϳ����ֽ�
		I2C_Write_Byte(b);
		I2CStop();
		delay_ms(100);
}

unsigned long SGP30_ad_read(void)
{
  	unsigned long dat;
		int crc;
  	I2CStart();
  	I2C_Write_Byte(SGP30_read); //����������ַ+��ָ��
  	dat = I2C_Read_Byte(ACK);
		dat <<= 8;
		dat += I2C_Read_Byte(ACK);
		crc = I2C_Read_Byte(ACK); //check���ݣ���ȥ
		crc = crc;             //�������������棬�����п���
		dat <<= 8;
		dat += I2C_Read_Byte(ACK);
		dat <<= 8;
		dat += I2C_Read_Byte(NACK);
  	I2CStop();
  	return(dat);
}