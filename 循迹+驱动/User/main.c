#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "Motor.h"
#include "TCRT.h"

int16_t Speed=0,KeyNum;

int main()
{
	OLED_Init();
	Key_Init();
	Motor_Init();
	TCRT_Init();

	Motor_SetSpeed1(0);
	Motor_SetSpeed2(0);
	OLED_ShowString(1,1,"Flag1:");
	OLED_ShowString(2,1,"Flag2:");
	OLED_ShowString(3,1,"Flag3:");
	OLED_ShowString(4,1,"Flag4:");

	while(1)
	{
		uint8_t Flag1 = TCRT_GetFlag1();
		uint8_t Flag2 = TCRT_GetFlag2();
		uint8_t Flag3 = TCRT_GetFlag3();
		uint8_t Flag4 = TCRT_GetFlag4();

		if((Flag1&&Flag2)&&(Flag3==RESET)&&(Flag4==RESET))
		{
			Car_Ahead();
		}
		if(Flag3)
		{
			Car_Left();
		}
		if(Flag4)
		{
			Car_Right();
		}
		if((Flag1&&Flag2&&Flag3&&Flag4)||((Flag1||Flag2||Flag3||Flag4)==RESET))
		{
			Car_Stop();
		}
		
		OLED_ShowNum(1,7,Flag1,2);
		OLED_ShowNum(2,7,Flag2,2);
		OLED_ShowNum(3,7,Flag3,2);
		OLED_ShowNum(4,7,Flag4,2);

	}
}
