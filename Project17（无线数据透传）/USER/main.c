#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "lcd.h"
#include "gizwits_product.h" 

void Gizwits_Init(void);
void userHandle(void);

//发送数据缓冲区
u8 send_buff[10]="6666666666";
//接收数据缓冲区
u8 read_buff[11]={0};
//透传数据接收标志位
//1：接收到数据  0：无
u8 read_sta=0;
//WIFI设备连接标志位 
//1：已连接  0：断开
u8 wifi_sta=0;
/* 用户区当前设备状态结构体*/
dataPoint_t currentDataPoint;

//主函数
int main(void)
{		
	u8 i;
  u8 key;
	u8 wifi_con;            //临时记录wifi连接状态 1:已连接 0:断开
	delay_init();	    	    //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	    //串口初始化为115200
 	LED_Init();			        //LED端口初始化
	KEY_Init();             //按键初始化 
  LCD_Init();	            //液晶初始化
	POINT_COLOR=RED;		    //设置字体为红色 
	LCD_ShowString(30,50,200,16,16,"        STM32");	
	LCD_ShowString(30,70,200,16,16,"   Data Passthrough");
	LCD_ShowString(30,90,200,16,16,"      2017/11/22");
	LCD_ShowString(30,130+10,200,16,16,"Wifi: Close   "); 
	LCD_ShowString(30,150+30,200,16,16,"KEY0:Send");				//显示提示信息
	POINT_COLOR=BLUE; 																			//设置字体为蓝色
	LCD_ShowString(30,170+20+20,200,16,16,"Send Data:");		//提示发送的数据	
	LCD_ShowString(30,220+20+20,200,16,16,"Receive Data:");	//提示接收到的数据	  
	Gizwits_Init();         //协议初始化
	printf("--------Data Passthroug---------\r\n");
	printf("KEY1:AirLink连接模式\t KEY_UP:复位\t KEY0:发送数据\r\n\r\n");
  while(1)
	{
		userHandle();//用户采集
    gizwitsHandle((dataPoint_t *)&currentDataPoint);//协议处理
	  key = KEY_Scan(0);
		if(key==KEY1_PRES)//KEY1按键
		{
			printf("WIFI进入AirLink连接模式\r\n");
			gizwitsSetMode(WIFI_AIRLINK_MODE);//Air-link模式接入
		}			
		if(key==WKUP_PRES)//KEY_UP按键
		{  
			printf("WIFI复位，请重新配置连接\r\n");
			gizwitsSetMode(WIFI_RESET_MODE);//WIFI复位
			wifi_sta=0;//标志wifi已断开
		}	
		if(key==KEY0_PRES)//发送数据
		{
			if(wifi_sta)
			{ 
				if(read_sta==0)
				{
					//将需发送的数据存到数据点数组上
					memcpy((u8*)&currentDataPoint.valuedata,(u8*)send_buff,sizeof(currentDataPoint.valuedata));
					printf("send data:");
					for(i=0;i<sizeof(currentDataPoint.valuedata);i++)
					  printf("%c",send_buff[i]);
					printf("\r\n");
					LCD_ShowString(30+42,170+60,200,16,16,send_buff);
				}
			}
		}
		if(wifi_con!=wifi_sta)
	  {
		  wifi_con=wifi_sta;
		  POINT_COLOR=RED;		//设置字体为红色
		  wifi_con?LCD_ShowString(78,130+10,200,16,16,"Connect"):LCD_ShowString(78,130+10,200,16,16,"Close   ");
		  POINT_COLOR=BLUE;	//设置字体为蓝色
	  }
	  LED1=0;	
		LED0=0;		
	}	 
} 
 
//协议初始化
void Gizwits_Init(void)
{	
	TIM3_Int_Init(9,7199);//1MS系统定时
    usart3_init(9600);//WIFI初始化
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//设备状态结构体初始化
	gizwitsInit();//缓冲区初始化
}
//数据采集
void userHandle(void)
{ 
	u8 i;
	if(wifi_sta)
	{
		if(read_sta==1) //接收到一次数据
		{
			printf("receive data:");
			for(i=0;i<sizeof(currentDataPoint.valuedata);i++)
				 printf("%c",read_buff[i]);//串口打印	 				 
			printf("\r\n");
			//将十六进制的数据转化为字符串打印在lcd_buff数组
			LCD_ShowString(30+42,210+70,200,16,16,read_buff);//液晶显示
			read_sta=0;//清除标志位
		}
	}
}
