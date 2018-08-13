#include "sys.h"
#include "usart.h"		
#include "delay.h"	  
#include "wifi.h"
#include "timer.h"
#include "pwm.h"
#include "io.h"
u8 f=0,m=0;
int speed1=0,speed2=0,speed3=0,speed4=0,speed5=0,speed6=0,speed7=0;
int main(void)
{			
	delay_init();
	uart_init(9600);	 //串口初始化为9600
	delay_ms(500); 
	TIM3_PWM_Init(899,0);//不分频。PWM频率=72000/(899+1)=80Khz
	WIFI_Init();
	while(1)
	{	
		if(USART_RX_STA==1)
		{
			m=USART_ReceiveData(USART1);
			USART_RX_STA=0;
			USART_SendData(USART1,m);
			switch(m)
			{
				case '0':speed1=390;speed2=450;speed3=-400;speed4=520;speed5=-470;speed6=600;speed7=-550;f=1;m=0;break;
//				case '1':speed1=430;speed2=550;speed3=-500;speed4=650;speed5=-600;speed6=750;speed7=-700;f=1;m=0;break;
//				case '2':speed1=460;speed2=650;speed3=300;speed4=750;speed5=300;speed6=850;speed7=300;f=1;m=0;break;
				case '1':move(-450,450);delay_ms(600);move(450,450);delay_ms(1000);move(0,0);f=0;m=0;break;
				case '2':move(450,450);delay_ms(1000);move(0,0);f=0;m=0;break;
				case '3':move(450,-450);delay_ms(600);move(450,450);delay_ms(1000);move(0,0);f=0;m=0;break;
				case 'S':move(0,0);f=0;m=0;break;
				default :f=0;m=0;          break;
			}
		}
		if(f==1)
		{
			switch(v&0x00F0)
			{
					case 0x0000:move(speed1,speed1);	break;
					case 0x0020:move(0,0);delay_ms(2);move(speed2,speed3);delay_ms(25);break;
					case 0x0010:move(0,0);delay_ms(2);move(speed6,speed7);delay_ms(40);break;
					case 0x0030:move(0,0);delay_ms(2);move(speed4,speed5);delay_ms(30);break;
					case 0x0040:move(0,0);delay_ms(2);move(speed3,speed2);delay_ms(25);break;
					case 0x0080:move(0,0);delay_ms(2);move(speed7,speed6);delay_ms(40);break;
					case 0x00C0:move(0,0);delay_ms(2);move(speed5,speed4);delay_ms(30);break;
					default:	move(400,-400); break;
			}
		}
	}
}
