#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "Motor.h"
#include "US.h"
#include "TCRT.h"

int16_t Speed;
uint8_t KeyNum, TCRTFlag;
float Distance;

int main()
{
	OLED_Init();
	Key_Init();
	Motor_Init();
	US_Init();
//	TCRT_Init();
	
	Motor_SetSpeed1(0);
	Motor_SetSpeed2(0);
	
	OLED_ShowString(1,1,"Speed_L :");
	OLED_ShowString(2,1,"Speed_R :");
	OLED_ShowString(3,1,"Distance:");
	
	while(1)
	{
		Distance = US_GetDistance();
		KeyNum = Key_GetNum();
//		TCRTFlag = TCRT_GetFlag();
	
		if(Distance <= 15 && Distance >= 2)
		{
			Motor_SetSpeed1(0);
			Motor_SetSpeed2(0);
		}
		else //if(Distance > 10 && Distance < 40)
		{
			Motor_SetSpeed1(Speed);
			Motor_SetSpeed2(Speed);
		}
		
		if(KeyNum == 1)
		{
			Delay_ms(50);
			Speed += 40;
			if(Speed > 100)
			{
				Speed = 0;
			}
			Motor_SetSpeed1(Speed);
			Motor_SetSpeed2(Speed);
		}
		OLED_ShowNum(1,10,Speed,3);
		OLED_ShowNum(2,10,Speed,3);
		OLED_ShowNum(3,10,Distance,3);
		Delay_ms(100);
//		OLED_ShowNum(4,1,TCRTFlag,3);
	}
}
