#include "stm32f10x.h"                  // Device header
#include "PWM.h"

#define GPIO_Motor_LeftH		GPIO_Pin_2
#define GPIO_Motor_LeftL		GPIO_Pin_3
#define GPIO_Motor_RightH		GPIO_Pin_4
#define GPIO_Motor_RightL		GPIO_Pin_5

void Motor_SetSpeed1(int16_t Speed);
void Motor_SetSpeed2(int16_t Speed);

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Motor_LeftH | GPIO_Motor_LeftL | GPIO_Motor_RightH | GPIO_Motor_RightL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, GPIO_Motor_LeftH | GPIO_Motor_LeftL | GPIO_Motor_RightH | GPIO_Motor_RightL);
	
	PWM_Init();
	
	Motor_SetSpeed1(0);
	Motor_SetSpeed2(0);
}

void Motor_SetSpeed1(int16_t Speed)
{
	if(Speed>=0)
	{
		GPIO_SetBits(GPIOA, GPIO_Motor_LeftH);
		GPIO_ResetBits(GPIOA, GPIO_Motor_LeftL);
		PWM_SetCompare1(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOA, GPIO_Motor_LeftL);
		GPIO_ResetBits(GPIOA, GPIO_Motor_LeftH);
		PWM_SetCompare1(-Speed);
	}
}

void Motor_SetSpeed2(int16_t Speed)
{
	if(Speed>=0)
	{
		GPIO_SetBits(GPIOA, GPIO_Motor_RightH);
		GPIO_ResetBits(GPIOA, GPIO_Motor_RightL);
		PWM_SetCompare2(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOA, GPIO_Motor_RightL);
		GPIO_ResetBits(GPIOA, GPIO_Motor_RightH);
		PWM_SetCompare2(-Speed);
	}
}

void Car_Ahead(void)
{
	Motor_SetSpeed1(50);
	Motor_SetSpeed2(50);
}

void Car_Back(void)
{
	Motor_SetSpeed1(-50);
	Motor_SetSpeed2(-50);
}

void Car_Left(void)
{
	Motor_SetSpeed1(50);
	Motor_SetSpeed2(00);
}

void Car_Right(void)
{
	Motor_SetSpeed1(00);
	Motor_SetSpeed2(50);
}

void Car_Stop(void)
{
	Motor_SetSpeed1(00);
	Motor_SetSpeed2(00);
}
