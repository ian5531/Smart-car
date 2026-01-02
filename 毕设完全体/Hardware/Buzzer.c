#include "stm32f10x.h"                  // Device header

#define GPIO_Buzzer_Ctrl		GPIO_Pin_0

void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Buzzer_Ctrl;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Buzzer_Ctrl);
}

uint8_t Buzzer_Flag;

void Buzzer_Task(void)
{
		Buzzer_Flag = !(Buzzer_Flag);
		if(Buzzer_Flag == 1)
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		}
		if(Buzzer_Flag == 0)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
		}
}
