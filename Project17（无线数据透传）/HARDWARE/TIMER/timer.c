#include "timer.h"
#include "led.h"
#include "gizwits_product.h" 

void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
//	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	TIM_Cmd(TIM3,ENABLE);
}
void TIM3_IRQHandler(void)   
{     
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
	{   
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update );   
			gizTimerMs();
	} 
}

void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	//PB、PC、定时器3时钟配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
 	 
	//速度大小控制引脚:PB0、PB1配置输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用(PWM)推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                                                   	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//定时器3—2路PWM输出（CH3、CH4）
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高

	TIM_OC3Init(TIM4, &TIM_OCInitStructure);               //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);      //CH3、4预装载使能	
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //使能TIMx在ARR上的预装载寄存器
	TIM_Cmd(TIM4, ENABLE);  //使能TIM3
}
				





