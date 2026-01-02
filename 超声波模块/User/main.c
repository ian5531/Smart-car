#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "US.h"

float Length;

int main()
{
	OLED_Init();
	US_Init();
	
	OLED_ShowString(3,1,"Length:");
	
	while(1)
	{
		Length = US_GetDistance();
		
		OLED_ShowNum(3,8,(uint16_t)Length,3);
		Delay_ms(100);
	}
}
