#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main()
{
	OLED_Init();
	Serial_Init();
	
	OLED_ShowString(1,1,"RxData:");
	
	while(1)
	{
		if(Serial_GetRxFlag())
		{
			RxData = Serial_GetRxData();
			OLED_ShowHexNum(1,8,RxData,2);
		}
	}
}

