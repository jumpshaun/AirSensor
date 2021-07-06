

#include "SGP30.h" 

//初始化IIC接口
void SGP30_Init(void)
{
	SGP30_ad_write(0x20,0x03);
//	SGP30_ad_write(0x20,0x61);
//	SGP30_ad_write(0x01,0x00);
}

void SGP30_ad_write(uchar a, uchar b)
{
  	I2CStart();
  	I2C_Write_Byte(SGP30_write); //发送器件地址+写指令
  	I2C_Write_Byte(a);		//发送控制字节
		I2C_Write_Byte(b);
		I2CStop();
		delay_ms(100);
}

unsigned long SGP30_ad_read(void)
{
  	unsigned long dat;
		int crc;
  	I2CStart();
  	I2C_Write_Byte(SGP30_read); //发送器件地址+读指令
  	dat = I2C_Read_Byte(ACK);
		dat <<= 8;
		dat += I2C_Read_Byte(ACK);
		crc = I2C_Read_Byte(ACK); //check数据，舍去
		crc = crc;             //避免编译产生警告，这句可有可无
		dat <<= 8;
		dat += I2C_Read_Byte(ACK);
		dat <<= 8;
		dat += I2C_Read_Byte(NACK);
  	I2CStop();
  	return(dat);
}