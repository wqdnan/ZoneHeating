#ifndef __TIM_H
#define __TIM_H

#include "p18cxxx.h"


#define TIM1H_CNT 0xFC//0xD8//    //用于设定1ms的定时周期   
#define TIM1L_CNT 0x18//0xF0//    //公式为：中断周期 =（65536-<TIM1H_CNT:TIM1L_CNT>）* 1us

#define TIM2_CYCLE 399          //公式为：PWM周期 = (TIM2_CYCLE+1)*4/FOSC*(TMR2预分频)  TMR2预分频=1
                                //TIM2_CYCLE=399 为5KHz
extern unsigned int b1ms;
extern unsigned int bt1ms,b10ms,bt10ms,b100ms,bt100ms;

void TIM1_Init();
void timerProc(void);

void TIM2_PWM_Init(void);
void setDutyCycle_CCP2(unsigned int Duty);         //PWM 占空比转换

#endif