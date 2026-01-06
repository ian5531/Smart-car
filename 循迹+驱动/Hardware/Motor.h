#ifndef __Motor_H__
#define __Motor_H__

void Motor_Init(void);
void Motor_SetSpeed1(int16_t Speed);
void Motor_SetSpeed2(int16_t Speed);
void Car_Ahead(void);
void Car_Back(void);
void Car_Left(void);
void Car_Right(void);
void Car_Stop(void);

#endif
