#include "stm32f10x.h"   
#include "time.h"
#include "key.h"
#include "sys.h"
#include "usart1.h"
#include "bsp_led.h"



int main(void)
{
	Key_TIM_Init();
	Key_GPIOF_Init();
	Usart1_Init();
	LED_GPIO_Config();
	
	
	while(1)
	{
		//�ж�USART1�Ƿ�����
		//printf("1");
		 KeyDriver();
		 
	}
}


