#ifndef __TIM_H
#define __TIM_H

#include "p18cxxx.h"


#define TIM1H_CNT 0xD8
#define TIM1L_CNT 0xF0

extern unsigned int b1ms;
extern unsigned int bt1ms,b10ms,bt10ms,b100ms,bt100ms,c10ms;

void TIM1_Init();
void timerProc(void);

#endif