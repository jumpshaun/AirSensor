#include "SHT3X.h"

#define POLYNOMIAL  0x31 // P(x) = x^8 + x^5 + x^4 + 1 = 00110001

//==============================================================================
unsigned char SHT3X_CalcCrc(unsigned char *crcdata, unsigned char nbrOfBytes)
{
//==============================================================================
  unsigned char Bit;        // bit mask
  unsigned char crc = 0xFF; // calculated checksum
  unsigned char byteCtr;    // byte counter
  
  // calculates 8-Bit checksum with given polynomial 
  for(byteCtr = 0; byteCtr < nbrOfBytes; byteCtr++)
  {
    crc ^= (crcdata[byteCtr]);
    for(Bit = 8; Bit > 0; --Bit)
    {
      if(crc & 0x80) crc = (crc << 1) ^ POLYNOMIAL;
      else           crc = (crc << 1);
    }
  }
	return crc;
}
etError SHT3X_WriteCommand(etCommands cmd)
{
  etError error; // error code  
  error  = I2C_Write_Byte(cmd >> 8);// write the upper 8 bits of the command to the sensor  
  error |= I2C_Write_Byte(cmd & 0xFF);// write the lower 8 bits of the command to the sensor	
  return error;
}
/*================================================================
���� �ơ�void SHT3XInit(void)
���� �ܡ�SHT3X��ʼ���������������е���
���� ע��
���� �ߡ�
��ʱ �䡿
================================================================*/
void SHT3XInit(void)
{
  I2CInit();//I2C��ʼ��	
  I2CStart();
  I2C_Write_Byte(SHT3XWriteHeader);
  SHT3X_WriteCommand(CMD_MEAS_PERI_1_H); //1��߾���ѭ������ģʽ
  I2CStop();
}
//==============================================================================ѭ����ȡģʽ
etError SHT3X_XHGetTempAndHumi(int        *temp,int        *humi)
{
//==============================================================================
  etError error;           // error code
  unsigned long int    rawValueTemp;    // temperature raw value from sensor
  unsigned long int    rawValueHumi;    // humidity raw value from sensor
	unsigned char Rdata[6]={0};
  unsigned char i;																			 
  I2CStart();
  error  = I2C_Write_Byte(SHT3XWriteHeader);
  // if no error ...
  if(error == NO_ERROR)
  {
    // start measurement in polling mode
    // use depending on the required repeatability, the corresponding command
     error = SHT3X_WriteCommand(CMD_FETCH_DATA);
  }
  // if no error, wait until measurement ready
  if(error == NO_ERROR)
  {
	 	I2CStart();
     error = I2C_Write_Byte(SHT3XReadHeader);
      // if measurement has finished -> exit loop
  }
	// if no error, read temperature and humidity raw values
  if(error == NO_ERROR)
  {
		for(i=0;i<5;i++)
		{
			Rdata[i] = I2C_Read_Byte(ACK);
		}
    Rdata[i] = I2C_Read_Byte(NACK);
		I2CStop();
		if(Rdata[2]!=SHT3X_CalcCrc(Rdata,2))     error = CHECKSUM_ERROR;
	  if(Rdata[5]!=SHT3X_CalcCrc(&Rdata[3],2)) error = CHECKSUM_ERROR;	
  }
  // if no error, calculate temperature in  and humidity in %RH
  if(error == NO_ERROR)
  {
		rawValueTemp =(Rdata[0] << 8) | Rdata[1];
		rawValueHumi =(Rdata[3] << 8) | Rdata[4];
    *temp =(int)(1750 *rawValueTemp / 65535 - 450);        //  --�¶���ʵֵ * 10
    *humi =(int)(1000 *rawValueHumi / 65535);              //  --ʪ����ʵֵ * 10
  }
  return error;
}
