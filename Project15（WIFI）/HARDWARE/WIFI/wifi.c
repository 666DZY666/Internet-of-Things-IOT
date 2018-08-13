#include "sys.h"
#include "usart.h"		
#include "delay.h"	

u8 a1[]="AT+CWMODE=3\r\n";
u8 a2[]="AT+RST\r\n";
//u8 a3[]="AT+CWJAP=\"QGN\",\"leitai1234\"\r\n";
u8 a4[]="AT+CIPSTART=\"TCP\",\"192.168.1.101\",666\r\n";
u8 a5[]="AT+CIPMODE=1\r\n";
u8 a6[]="AT+CIPSEND\r\n";
void WIFI_Init(void)
{
	Uart1SendData(a1);
	delay_ms(600);
	Uart1SendData(a2);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	Uart1SendData(a4);
	delay_ms(600);
	Uart1SendData(a5);
	delay_ms(600);
	Uart1SendData(a6);
	delay_ms(600);
}
