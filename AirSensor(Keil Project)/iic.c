#include "iic.h"

void I2CInit(void)
{
	SDA = 1; 
	SCL = 1;
}
/*================================================================
��  Name  ��void I2CDelay (uchar t)
��Function��ģ��IIC�õĶ���ʱ us
��  Notes ��
================================================================*/
void I2CDelay (uchar t)          
{
        while(t--);
}

/*================================================================
��  Name  ��void I2CStart(void)
��Function��I2C��ʼ�ź�
��  Notes ��SCL��SDAͬΪ�ߣ�SDA����ɵ�֮��SCL����ɵ�          
================================================================*/
void I2CStart(void)
{        
	  SDA = 1;                       //������ʼ�����������ź�--ZLG
	  SCL = 1;
	  I2CDelay(50);                    //��ʼ��������ʱ�����4.7us,��ʱ--ZLG
	  SDA = 0;                            //������ʼ�ź�-ZLG
	  I2CDelay(50);                    //��ʼ��������ʱ�����4��s--ZLG
	  SCL = 0;                            //ǯסI2C���ߣ�׼�����ͻ��������--ZLG
	  I2CDelay(50);         
}

/*================================================================
��  Name  ��void I2CStop(void)
��Function��I2Cֹͣ�ź�
��  Notes ��SCL��SDAͬΪ�ͣ�SCL����ɸ�֮��SDA����ɸ�           
================================================================*/
void I2CStop(void)
{        
	  SDA = 0;                        //���ͽ��������������ź�--ZLG
	  SCL = 0;
	  I2CDelay(50);
	  SCL = 1;                        //���ͽ���������ʱ���ź�--ZLG
	  I2CDelay(50);                //������������ʱ�����4��s--ZLG
	  SDA = 1;                        //����I2C���߽����ź�--ZLG
	  I2CDelay(50); 
}

/*================================================================
��  Name  ��uchar I2C_Write_Byte(uchar WRByte)
��Function��I2Cдһ���ֽ����ݣ�����ACK����NACK
��  Notes ���Ӹߵ��ͣ����η���
================================================================*/
uchar I2C_Write_Byte(uchar Write_Byte)  //Sendbyte
{
        uchar i;   
		SCL=0;	
		I2CDelay(40); 
        for(i=0;i<8;i++)              //Ҫ���͵����ݳ���Ϊ8λ--ZLG
        {         
			if(Write_Byte&0x80)   //�жϷ���λ--ZLG
			{
				SDA = 1;        
			}
			else
			{
				SDA = 0;
			}
			I2CDelay(20);                
			SCL=1;                //���SDA�ȶ�������SCL���������أ��ӻ���⵽��������ݲ���      
			I2CDelay(20);         //��֤ʱ�Ӹߵ�ƽ���ڴ���4��s--ZLG
			SCL=0;
			I2CDelay(20);
			Write_Byte <<= 1;
        } 
        I2CDelay(2);
        SDA = 1;                      //8λ��������ͷ������ߣ�׼������Ӧ��λ-ZLG
		I2CDelay(100);
		SCL = 1;                      //MCU��֪SHT2X���ݷ�����ϣ��ȴ��ӻ���Ӧ���ź�        
        I2CDelay(100);                   
        /*�������ж�I2C���߽���Ӧ��Ӧ���ź���ACK����NACK*/
        if(SDA==1)                                   //SDAΪ�ߣ��յ�NACK
		{
			  SCL=0;
			  return NACK;   
		}        
        else                                         //SDAΪ�ͣ��յ�ACK 
		{
			  SCL=0;
			  return ACK;  
		}	 
}

/*================================================================
��  Name  ��uchar I2C_Read_Byte(uchar AckValue)
��Function��I2C��һ���ֽ����ݣ���ڲ������ڿ���Ӧ��״̬��ACK����NACK
��  Notes ���Ӹߵ��ͣ����ν���
================================================================*/
uchar I2C_Read_Byte(uchar AckValue)//receivebyte
{
        uchar i,RDByte=0;
        SCL=0;                                   //��ʱ����Ϊ�ͣ�׼����������λ--ZLG
				I2CDelay(80);  
        SDA = 1;                                 //�ͷ�����,��������Ϊ���뷽ʽ--ZLG        
        for (i=0;i<8;i++) 
        {        
			SCL = 1;                          //SCL�ߵ�ƽ�ڼ䣬�ɼ�SDA�źţ�����Ϊ��Ч���� //��ʱ����Ϊ��ʹ��������������Ч--ZLG 
			I2CDelay(5);
			RDByte <<= 1;                  //��λ
			if(SDA==1)                           //������ȡ����
			{
				RDByte |= 0x01;
			}
			else
			{
				RDByte &= 0xfe;
			}
			I2CDelay(20);
			SCL = 0;                             //�½��أ��ӻ�������һλֵ
			I2CDelay(60);
		}   
        /*������I2C���߷���Ӧ���ź�ACK����NACK*/
        SDA = AckValue;                      //Ӧ��״̬        
        I2CDelay(60);
        SCL = 1;                         
        I2CDelay(100);                  //ʱ�ӵ͵�ƽ���ڴ���4��s--ZLG
        SCL = 0;                                  //��ʱ���ߣ�ǯסI2C�����Ա��������--ZLG               
        I2CDelay(300);       
        return RDByte;
}

/*****************************************************************************
 * @name       :void IIC_Stop(void)
 * @date       :2018-09-13 
 * @function   :stop iic bus
 * @parameters :None
 * @retvalue   :None
******************************************************************************/

/*****************************************************************************
 * @name       :void IIC_Wait_Ack(void)
 * @date       :2018-09-13 
 * @function   :wait iic ack
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void IIC_Wait_Ack(void)
{
	SCL=1;
	SCL=0;
}

/*****************************************************************************
 * @name       :void Write_IIC_Byte(u8 IIC_Byte)
 * @date       :2018-09-13 
 * @function   :Write a byte of content with iic bus
 * @parameters :IIC_Byte
 * @retvalue   :None
******************************************************************************/
void Write_IIC_Byte(u8 IIC_Byte)
{
	u8 i;
	u8 m,da;
	da=IIC_Byte;
	SCL=0;
	for(i=0;i<8;i++)		
	{
		m=da;
		m=m&0x80;
		if(m==0x80)
		{
			SDA=1;
		}
		else
		{
			SDA=0;
		}
		da=da<<1;
		SCL=1;
		SCL=0;
	}
}

/*****************************************************************************
 * @name       :void Write_IIC_Command(u8 IIC_Command)
 * @date       :2018-09-13 
 * @function   :Write a byte of command to oled screen
 * @parameters :IIC_Command:command to be written
 * @retvalue   :None
******************************************************************************/
void Write_IIC_Command(u8 IIC_Command)
{
	I2CStart();
	Write_IIC_Byte(IIC_SLAVE_ADDR);            //Slave address,SA0=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
	I2CStop();
}

/*****************************************************************************
 * @name       :void Write_IIC_Data(u8 IIC_Data)
 * @date       :2018-09-13 
 * @function   :Write a byte of data to oled screen
 * @parameters :IIC_Data:data to be written
 * @retvalue   :None
******************************************************************************/
void Write_IIC_Data(u8 IIC_Data)
{
	I2CStart();
	Write_IIC_Byte(IIC_SLAVE_ADDR);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
	I2CStop();
}
