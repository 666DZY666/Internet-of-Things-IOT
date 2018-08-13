#include "IO.h"
void IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //使能PB端口时钟
	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPD; 		     					//下拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 					//IO口速度为50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	//四路循迹传感器端口:PB4、5、6、7
	GPIO_Init(GPIOA, &GPIO_InitStructure);		

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	//四路循迹传感器端口:PB4、5、6、7
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	//四路循迹传感器端口:PB4、5、6、7
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	//四路循迹传感器端口:PB4、5、6、7
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
}
