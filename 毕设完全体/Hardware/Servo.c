#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_SetAngle(float Angle);

void Servo_Init(void)
{
	PWM_Servo_Init();
	Servo_SetAngle(0);
}

void Servo_SetAngle(float Angle)
{
	PWM_Servo_SetCompare((Angle / 180) * 2000 + 1500);
}
