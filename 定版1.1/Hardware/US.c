#include "stm32f10x.h"                  // Device header
#include "delay.h"

void US_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_Cmd(TIM3, DISABLE);
}

float US_GetDistance(void)
{
	float Length;
	uint32_t Time;
	
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
	Delay_us(20);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == RESET);
	TIM_Cmd(TIM3, ENABLE);
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == SET);
	TIM_Cmd(TIM3, DISABLE);
	Time = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);
	Length = Time * 1.7; 			//	length = (Time / 10000 * 340 * 100) / 2;
	
	return Length;
}
