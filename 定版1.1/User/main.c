#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Motor.h"
#include "US.h"
#include "TCRT.h"
#include "Alarm.h"

uint8_t RxData,StateFlag,AlarmFlag;
float Distance;

int main()
{
	OLED_Init();
	Motor_Init();
	Serial_Init();
	US_Init();
	Alarm_Init();
	Motor_SetSpeed1(0);
	Motor_SetSpeed2(0);
	
	OLED_ShowString(1,1,"RxData:");
	OLED_ShowString(2,1,"Length:");
	OLED_ShowString(3,1,"TCRTFL:");
	
	
	while(1)
	{
		Distance = US_GetDistance();
		OLED_ShowNum(2,8,Distance,4);
		Delay_ms(100);
		
		if(Serial_GetRxFlag())
		{
			RxData = Serial_GetRxData();
			OLED_ShowHexNum(1,8,RxData,2);
			
			if(RxData == 0xDD)
			{
				AlarmFlag = !(AlarmFlag);
				if(AlarmFlag == 1)
				{
					Alarm_Run();
				}
				if(AlarmFlag == 0)
				{
					Alarm_Stop();
				}
			}
			
			switch(RxData)
			{
				case 0xAA:StateFlag=1;break;
				case 0xBB:StateFlag=2;break;
				case 0xCC:StateFlag=3;break;
				case 0xFF:StateFlag=4;break;
				default:break;
			}
			
			if((RxData == 0x11)&&(StateFlag == 1))
			{
				Car_Ahead();
			}
			if((RxData == 0x22)&&(StateFlag == 1))
			{
				Car_Back();
			}
			if((RxData == 0x33)&&(StateFlag == 1))
			{
				Car_Left();
			}
			if((RxData == 0x44)&&(StateFlag == 1))
			{
				Car_Right();
			}
			if((RxData == 0x55)&&(StateFlag == 1))
			{
				Car_Stop();
			}
		}
		if(StateFlag == 2)
		{
			if(Distance >= 2 && Distance <= 20)
			{
				Car_Stop();
				Delay_ms(500);
				Car_Right();
				Delay_ms(2500);
			}
			else
			{
				Car_Ahead();
			}
		}
		if(StateFlag == 3)
		{
			uint8_t Flag1 = TCRT_GetFlag1();
			uint8_t Flag2 = TCRT_GetFlag2();
			uint8_t Flag3 = TCRT_GetFlag3();
			uint8_t Flag4 = TCRT_GetFlag4();

			if((Flag1==SET)&&(Flag2==SET)&&(Flag3==RESET)&&(Flag4==RESET))
			{
				Car_Ahead();
			}
			if((Flag3==SET)&&(Flag4==RESET))
			{
				Motor_SetSpeed1(-25);
				Motor_SetSpeed2(50);
			}
			if((Flag3==RESET)&&(Flag4==SET))
			{
				Motor_SetSpeed1(50);
				Motor_SetSpeed2(-25);
			}
			if((Flag1&&Flag2&&Flag3&&Flag4)||((Flag1||Flag2||Flag3||Flag4)==RESET))
			{
				Car_Stop();
			}
			OLED_ShowNum(3,8,Flag1,1);
			OLED_ShowNum(3,10,Flag2,1);
			OLED_ShowNum(3,12,Flag3,1);
			OLED_ShowNum(3,14,Flag4,1);
		}
		if(StateFlag == 4)
		{
			Car_Stop();
			StateFlag = 0;
		}
	}
}

