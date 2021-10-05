#include "time.h"

void NVIC_TIM6(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStruct.NVIC_IRQChannel			= TIM6_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd  = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority	=	1;
	
	NVIC_Init(&NVIC_InitStruct);
}

void TIM6_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM6_TimeBaseStructure;
				/*基础定时器不需要配置这两个*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
//	TIM_TimeBaseInitStruct.TIM_ClockDivision =	TIM_CKD_DIV1;
//	TIM_TimeBaseInitStruct.TIM_CounterMode = 		TIM_CounterMode_Up;
	TIM6_TimeBaseStructure.TIM_Period		 = 			5000-1;				//5ms
	TIM6_TimeBaseStructure.TIM_Prescaler = 			72-1   ;				//
 	
	TIM_TimeBaseInit(TIM6,&TIM6_TimeBaseStructure);
		
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM6, ENABLE);
	
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
}

void Key_TIM_Init(void)
{
	TIM6_Init();
	NVIC_TIM6();
}
	
