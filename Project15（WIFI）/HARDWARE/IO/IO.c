#include "IO.h"
void IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //ʹ��PB�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD; 		     					//��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 					//IO���ٶ�Ϊ50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	//��·ѭ���������˿�:PB4��5��6��7
	GPIO_Init(GPIOA, &GPIO_InitStructure);		

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	//��·ѭ���������˿�:PB4��5��6��7
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	//��·ѭ���������˿�:PB4��5��6��7
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	//��·ѭ���������˿�:PB4��5��6��7
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
}
