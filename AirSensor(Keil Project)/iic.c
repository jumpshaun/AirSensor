#include "iic.h"

void I2CInit(void)
{
	SDA = 1; 
	SCL = 1;
}
/*================================================================
【  Name  】void I2CDelay (uchar t)
【Function】模拟IIC用的短延时 us
【  Notes 】
================================================================*/
void I2CDelay (uchar t)          
{
        while(t--);
}

/*================================================================
【  Name  】void I2CStart(void)
【Function】I2C起始信号
【  Notes 】SCL、SDA同为高，SDA跳变成低之后，SCL跳变成低          
================================================================*/
void I2CStart(void)
{        
	  SDA = 1;                       //发送起始条件的数据信号--ZLG
	  SCL = 1;
	  I2CDelay(50);                    //起始条件建立时间大于4.7us,延时--ZLG
	  SDA = 0;                            //发送起始信号-ZLG
	  I2CDelay(50);                    //起始条件锁定时间大于4μs--ZLG
	  SCL = 0;                            //钳住I2C总线，准备发送或接收数据--ZLG
	  I2CDelay(50);         
}

/*================================================================
【  Name  】void I2CStop(void)
【Function】I2C停止信号
【  Notes 】SCL、SDA同为低，SCL跳变成高之后，SDA跳变成高           
================================================================*/
void I2CStop(void)
{        
	  SDA = 0;                        //发送结束条件的数据信号--ZLG
	  SCL = 0;
	  I2CDelay(50);
	  SCL = 1;                        //发送结束条件的时钟信号--ZLG
	  I2CDelay(50);                //结束条件建立时间大于4μs--ZLG
	  SDA = 1;                        //发送I2C总线结束信号--ZLG
	  I2CDelay(50); 
}

/*================================================================
【  Name  】uchar I2C_Write_Byte(uchar WRByte)
【Function】I2C写一个字节数据，返回ACK或者NACK
【  Notes 】从高到低，依次发送
================================================================*/
uchar I2C_Write_Byte(uchar Write_Byte)  //Sendbyte
{
        uchar i;   
		SCL=0;	
		I2CDelay(40); 
        for(i=0;i<8;i++)              //要传送的数据长度为8位--ZLG
        {         
			if(Write_Byte&0x80)   //判断发送位--ZLG
			{
				SDA = 1;        
			}
			else
			{
				SDA = 0;
			}
			I2CDelay(20);                
			SCL=1;                //输出SDA稳定后，拉高SCL给出上升沿，从机检测到后进行数据采样      
			I2CDelay(20);         //保证时钟高电平周期大于4μs--ZLG
			SCL=0;
			I2CDelay(20);
			Write_Byte <<= 1;
        } 
        I2CDelay(2);
        SDA = 1;                      //8位发送完后释放数据线，准备接收应答位-ZLG
		I2CDelay(100);
		SCL = 1;                      //MCU告知SHT2X数据发送完毕，等待从机的应答信号        
        I2CDelay(100);                   
        /*以下是判断I2C总线接收应到应答信号是ACK还是NACK*/
        if(SDA==1)                                   //SDA为高，收到NACK
		{
			  SCL=0;
			  return NACK;   
		}        
        else                                         //SDA为低，收到ACK 
		{
			  SCL=0;
			  return ACK;  
		}	 
}

/*================================================================
【  Name  】uchar I2C_Read_Byte(uchar AckValue)
【Function】I2C读一个字节数据，入口参数用于控制应答状态，ACK或者NACK
【  Notes 】从高到低，依次接收
================================================================*/
uchar I2C_Read_Byte(uchar AckValue)//receivebyte
{
        uchar i,RDByte=0;
        SCL=0;                                   //置时钟线为低，准备接收数据位--ZLG
				I2CDelay(80);  
        SDA = 1;                                 //释放总线,置数据线为输入方式--ZLG        
        for (i=0;i<8;i++) 
        {        
			SCL = 1;                          //SCL高电平期间，采集SDA信号，并作为有效数据 //置时钟线为高使数据线上数据有效--ZLG 
			I2CDelay(5);
			RDByte <<= 1;                  //移位
			if(SDA==1)                           //采样获取数据
			{
				RDByte |= 0x01;
			}
			else
			{
				RDByte &= 0xfe;
			}
			I2CDelay(20);
			SCL = 0;                             //下降沿，从机给出下一位值
			I2CDelay(60);
		}   
        /*以下是I2C总线发送应答信号ACK或者NACK*/
        SDA = AckValue;                      //应答状态        
        I2CDelay(60);
        SCL = 1;                         
        I2CDelay(100);                  //时钟低电平周期大于4μs--ZLG
        SCL = 0;                                  //清时钟线，钳住I2C总线以便继续接收--ZLG               
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
