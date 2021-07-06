#include "8266.h"
void init_8266(void)
{
	printf("AT+CWMODE_DEF=2\r\n");
	delay_ms(300);
	printf("AT+RST\r\n");
  delay_ms(1200);
	printf("AT+CIPMUX=1\r\n");
	delay_ms(300);
	printf("AT+CIPSERVER=1,6666\r\n");
	delay_ms(300);
}
