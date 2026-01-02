#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "Motor.h"

int16_t Speed=0,KeyNum;

int main()
{
	OLED_Init();
	Key_Init();
	Motor_Init();

	Motor_SetSpeed1(0);
	Motor_SetSpeed2(0);
	OLED_ShowString(1,1,"Speed_L:");
	OLED_ShowString(2,1,"Speed_R:");

	while(1)
	{
		KeyNum = Key_GetNum();
		
		if(KeyNum == 1)
		{
			Speed += 40;
			if(Speed > 100)
			{
				Speed = 0;
			}
			Motor_SetSpeed1(Speed);
			Motor_SetSpeed2(Speed);
		}
		
		OLED_ShowNum(1,9,Speed,3);
		OLED_ShowNum(2,9,Speed,3);
	}
}
