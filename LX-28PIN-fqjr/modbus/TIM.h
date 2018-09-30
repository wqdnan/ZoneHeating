#ifndef __TIM_H
#define __TIM_H

#include "p18cxxx.h"


#define TIM1H_CNT 0xFC//0xD8//    //�����趨1ms�Ķ�ʱ����   
#define TIM1L_CNT 0x18//0xF0//    //��ʽΪ���ж����� =��65536-<TIM1H_CNT:TIM1L_CNT>��* 1us

#define TIM2_CYCLE 399          //��ʽΪ��PWM���� = (TIM2_CYCLE+1)*4/FOSC*(TMR2Ԥ��Ƶ)  TMR2Ԥ��Ƶ=1
                                //TIM2_CYCLE=399 Ϊ5KHz
extern unsigned int b1ms;
extern unsigned int bt1ms,b10ms,bt10ms,b100ms,bt100ms;

void TIM1_Init();
void timerProc(void);

void TIM2_PWM_Init(void);
void setDutyCycle_CCP2(unsigned int Duty);         //PWM ռ�ձ�ת��

#endif