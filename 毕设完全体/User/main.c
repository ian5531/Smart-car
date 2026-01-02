#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Motor.h"
#include "Remote.h"
#include "US.h"
#include "TCRT.h"
#include "Buzzer.h"
#include "Servo.h"

uint8_t RxData,StatusFlag;
float Distance;

int main()
{
	OLED_Init();
	Serial_Init();
	Servo_Init();
	US_Init();
	Motor_Init();
	Buzzer_Init();

	OLED_ShowString(1,1,"MyCar_22");
	OLED_ShowString(2,1,"RxData:");
	OLED_ShowString(2,8,"Readying");
	OLED_ShowString(3,1,"Length:");
	OLED_ShowString(4,1,"TCRTFL:");
	OLED_ShowString(4,8,"0 0 0 0");
	
	while(1)
	{
		Distance = US_GetDistance();
		OLED_ShowNum(3,8,Distance,4);
		Delay_ms(100);
		
		if(Serial_GetRxFlag())
		{
			RxData = Serial_GetRxData();	//获取蓝牙发送值
			
			if(RxData == 0xDD)	//蜂鸣器的开启或关闭
			{
				Buzzer_Task();
			}
			
			switch(RxData)	//根据接收值设定标志位
			{
				case 0xAA:StatusFlag=1;break;
				case 0xBB:StatusFlag=2;break;
				case 0xCC:StatusFlag=3;break;
				case 0xFF:StatusFlag=4;break;
				default:break;	//错误信息直接退出
			}
		}
		
		if(StatusFlag == 1)	//蓝牙控制状态
		{
			OLED_ShowString(2,8,"Remote  ");
			Remote_Status(RxData);
		}
		
		if(StatusFlag == 2)	//自动避障状态
		{
			OLED_ShowString(2,8,"Avoid   ");
			US_Task(Distance);
		}
		
		if(StatusFlag == 3)	//自动循迹状态
		{
			OLED_ShowString(2,8,"Find    ");
			TCRT_Task();
		}
		
		if(StatusFlag == 4)	//停止小车并退出模式
		{
			OLED_ShowString(2,8,"Readying");
			Car_Stop();
			StatusFlag = 0;
		}
	}
}

