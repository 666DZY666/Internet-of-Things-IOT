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

//�������ݻ�����
u8 send_buff[10]="6666666666";
//�������ݻ�����
u8 read_buff[11]={0};
//͸�����ݽ��ձ�־λ
//1�����յ�����  0����
u8 read_sta=0;
//WIFI�豸���ӱ�־λ 
//1��������  0���Ͽ�
u8 wifi_sta=0;
/* �û�����ǰ�豸״̬�ṹ��*/
dataPoint_t currentDataPoint;

//������
int main(void)
{		
	u8 i;
  u8 key;
	u8 wifi_con;            //��ʱ��¼wifi����״̬ 1:������ 0:�Ͽ�
	delay_init();	    	    //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	    //���ڳ�ʼ��Ϊ115200
 	LED_Init();			        //LED�˿ڳ�ʼ��
	KEY_Init();             //������ʼ�� 
  LCD_Init();	            //Һ����ʼ��
	POINT_COLOR=RED;		    //��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"        STM32");	
	LCD_ShowString(30,70,200,16,16,"   Data Passthrough");
	LCD_ShowString(30,90,200,16,16,"      2017/11/22");
	LCD_ShowString(30,130+10,200,16,16,"Wifi: Close   "); 
	LCD_ShowString(30,150+30,200,16,16,"KEY0:Send");				//��ʾ��ʾ��Ϣ
	POINT_COLOR=BLUE; 																			//��������Ϊ��ɫ
	LCD_ShowString(30,170+20+20,200,16,16,"Send Data:");		//��ʾ���͵�����	
	LCD_ShowString(30,220+20+20,200,16,16,"Receive Data:");	//��ʾ���յ�������	  
	Gizwits_Init();         //Э���ʼ��
	printf("--------Data Passthroug---------\r\n");
	printf("KEY1:AirLink����ģʽ\t KEY_UP:��λ\t KEY0:��������\r\n\r\n");
  while(1)
	{
		userHandle();//�û��ɼ�
    gizwitsHandle((dataPoint_t *)&currentDataPoint);//Э�鴦��
	  key = KEY_Scan(0);
		if(key==KEY1_PRES)//KEY1����
		{
			printf("WIFI����AirLink����ģʽ\r\n");
			gizwitsSetMode(WIFI_AIRLINK_MODE);//Air-linkģʽ����
		}			
		if(key==WKUP_PRES)//KEY_UP����
		{  
			printf("WIFI��λ����������������\r\n");
			gizwitsSetMode(WIFI_RESET_MODE);//WIFI��λ
			wifi_sta=0;//��־wifi�ѶϿ�
		}	
		if(key==KEY0_PRES)//��������
		{
			if(wifi_sta)
			{ 
				if(read_sta==0)
				{
					//���跢�͵����ݴ浽���ݵ�������
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
		  POINT_COLOR=RED;		//��������Ϊ��ɫ
		  wifi_con?LCD_ShowString(78,130+10,200,16,16,"Connect"):LCD_ShowString(78,130+10,200,16,16,"Close   ");
		  POINT_COLOR=BLUE;	//��������Ϊ��ɫ
	  }
	  LED1=0;	
		LED0=0;		
	}	 
} 
 
//Э���ʼ��
void Gizwits_Init(void)
{	
	TIM3_Int_Init(9,7199);//1MSϵͳ��ʱ
    usart3_init(9600);//WIFI��ʼ��
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//�豸״̬�ṹ���ʼ��
	gizwitsInit();//��������ʼ��
}
//���ݲɼ�
void userHandle(void)
{ 
	u8 i;
	if(wifi_sta)
	{
		if(read_sta==1) //���յ�һ������
		{
			printf("receive data:");
			for(i=0;i<sizeof(currentDataPoint.valuedata);i++)
				 printf("%c",read_buff[i]);//���ڴ�ӡ	 				 
			printf("\r\n");
			//��ʮ�����Ƶ�����ת��Ϊ�ַ�����ӡ��lcd_buff����
			LCD_ShowString(30+42,210+70,200,16,16,read_buff);//Һ����ʾ
			read_sta=0;//�����־λ
		}
	}
}
