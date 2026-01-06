#ifndef __TCRT_H__
#define __TCRT_H__

void TCRT_Init(void);

uint8_t TCRT_GetFlag1(void);
uint8_t TCRT_GetFlag2(void);
uint8_t TCRT_GetFlag3(void);
uint8_t TCRT_GetFlag4(void);

void TCRT_Task(void);
	
#endif
