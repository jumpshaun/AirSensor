
#include "stc8.h" 
#include "intrins.h"
#include "iic.h"
#include "delay.h"

#ifndef __SGP30_H
#define __SGP30_H

#define uchar unsigned char         
#define uint  unsigned int
#define ulong unsigned long
	
#define SGP30_read  0xb1           
#define SGP30_write 0xb0

void ReadShtc3(void);

void SGP30_Init(void);

void SGP30_ad_write(uchar, uchar);

unsigned long SGP30_ad_read(void);

#endif