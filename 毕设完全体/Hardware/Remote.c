#include "stm32f10x.h"                  // Device header
#include "Motor.h"

void Remote_Status(uint8_t RxData)
{
	if(RxData == 0x11)
	{
		Car_Ahead();
	}
	if(RxData == 0x22)
	{
		Car_Back();
	}
	if(RxData == 0x33)
	{
		Car_Left();
	}
	if(RxData == 0x44)
	{
		Car_Right();
	}
	if(RxData == 0x55)
	{
		Car_Stop();
	}
}
