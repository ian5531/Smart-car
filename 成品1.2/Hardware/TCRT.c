#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "OLED.h"

#define	GPIO_TCRT_1		GPIO_Pin_14
#define GPIO_TCRT_2		GPIO_Pin_12
#define	GPIO_TCRT_3		GPIO_Pin_13
#define GPIO_TCRT_4		GPIO_Pin_15

void TCRT_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_TCRT_1 |GPIO_TCRT_2 |GPIO_TCRT_3 |GPIO_TCRT_4;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t TCRT_GetFlag1(void)
{
	uint8_t TCRT_Flag;
	TCRT_Flag = GPIO_ReadInputDataBit(GPIOB, GPIO_TCRT_1);
	return TCRT_Flag;
}

uint8_t TCRT_GetFlag2(void)
{
	uint8_t TCRT_Flag;
	TCRT_Flag = GPIO_ReadInputDataBit(GPIOB, GPIO_TCRT_2);
	return TCRT_Flag;
}
uint8_t TCRT_GetFlag3(void)
{
	uint8_t TCRT_Flag;
	TCRT_Flag = GPIO_ReadInputDataBit(GPIOB, GPIO_TCRT_3);
	return TCRT_Flag;
}
uint8_t TCRT_GetFlag4(void)
{
	uint8_t TCRT_Flag;
	TCRT_Flag = GPIO_ReadInputDataBit(GPIOB, GPIO_TCRT_4);
	return TCRT_Flag;
}

void TCRT_Task(void)
{
	uint8_t Flag1 = TCRT_GetFlag1();
	uint8_t Flag2 = TCRT_GetFlag2();
	uint8_t Flag3 = TCRT_GetFlag3();
	uint8_t Flag4 = TCRT_GetFlag4();

	if((Flag2==SET)&&(Flag3==SET)&&(Flag1==RESET)&&(Flag4==RESET))
	{
		Car_Ahead();
	}
	if((Flag1==SET)&&(Flag4==RESET))
	{
		Motor_SetSpeed1(50);
		Motor_SetSpeed2(-25);
	}
	if((Flag1==RESET)&&(Flag4==SET))
	{
		Motor_SetSpeed1(-25);
		Motor_SetSpeed2(50);
	}
	if((Flag1&&Flag2&&Flag3&&Flag4)||((Flag1||Flag2||Flag3||Flag4)==RESET))
	{
		Car_Stop();
	}
	
	OLED_ShowNum(4,8,Flag1,1);
	OLED_ShowNum(4,10,Flag2,1);
	OLED_ShowNum(4,12,Flag3,1);
	OLED_ShowNum(4,14,Flag4,1);
}
