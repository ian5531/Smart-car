#include "stm32f10x.h"                  // Device header

void TCRT_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t TCRT_GetFlag1(void)
{
	uint8_t TCRT_Flag;
	TCRT_Flag = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
	return TCRT_Flag;
}

uint8_t TCRT_GetFlag2(void)
{
	uint8_t TCRT_Flag;
	TCRT_Flag = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
	return TCRT_Flag;
}
uint8_t TCRT_GetFlag3(void)
{
	uint8_t TCRT_Flag;
	TCRT_Flag = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
	return TCRT_Flag;
}
uint8_t TCRT_GetFlag4(void)
{
	uint8_t TCRT_Flag;
	TCRT_Flag = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15);
	return TCRT_Flag;
}
