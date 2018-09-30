#include "TIM.h"

#include "UART.h"
unsigned int b1ms;
unsigned int bt1ms,b10ms,bt10ms,b100ms,bt100ms;

//定时一个1ms 的中断函数，用于modbus检测接收间隔
void TIM1_Init()
{
	TMR1H = TIM1H_CNT;                //8MHz  定一个1ms的定时中断
	TMR1L = TIM1L_CNT;        
	T1CONbits.T1CKPS = 1;        //预分频1:2
	T1CONbits.RD16 = 1;          //16位TIMR
	T1CONbits.TMR1CS = 0;        //FOSC/4
	PIE1bits.TMR1IE	= 1;         //TMR1中断
	
}

//定时处理 modbus
void timerProc(void)
{
	static unsigned int c200ms;

	b1ms = 0;
	b10ms = 0;
	b100ms = 0;

//	INTCONbits.TMR0IE=0;
	dwTickCount = dwIntTick;
//	INTCONbits.TMR0IE=1;

	if(bt1ms)
	{
		bt1ms = 0;
		b1ms = 1;

        if(receTimeOut>0)
        {
            receTimeOut--;
            if(receTimeOut==0 && receCount>0)   //判断通讯接收是否超时
            {
                receCount = 0;      //将接收地址偏移寄存器清零
				checkoutError = 0;
            }
        }
	}
	if(bt100ms)
	{
		bt100ms = 0;
		b100ms = 1;
	}
    if(bt10ms)      //判断中断10ms标志位是否1
    {
        bt10ms = 0;     //清中断10ms标志位
		b10ms = 1;
        c200ms++;                   //200ms计时器加1
        if(c200ms >= 20)            //判断是否计时到200ms
        {
            c200ms = 0;             //清200ms计时器
        }
    }
}

//-------------------------------------------------------------------------------
//	CCP2初始化 用于PWM输出 暂时设定频率周期为5KHz
//-------------------------------------------------------------------------------
void TIM2_PWM_Init(void)
{
	TRISCbits.TRISC2 = 0;       //设定RC2 输出低为发送 对应CCP2的PWM引脚
	CCP2CON = 0b00001100;         //CCP2 为PWM模式 
	CCPTMRS = 0b00000000;         //TMR2为时钟
	PIE3bits.CCP2IE = 0;          //CCP2中断禁止
	PIR3bits.CCP2IF = 0;          //CCP2 PWM模式不使用
	T2CON = 0b01001100;           //后分频比 1:10, T2ON 预分频比为1
	PR2 = TIM2_CYCLE;              //PWM周期 = (PR2+1)*4*TOSC*(TMR2预分频)
	                              //TOSC = 1/FOSC
	CCPR2L = 0x00;                //占空比 0
}
//--------------------------------------------------------
//修改CCP2 对应为 RC2 引脚的占空比 
//在预分频=1情况下，Duty=0 代表0%  Duty=1024 代表100%
//---------------------------------------------------------
void setDutyCycle_CCP2(unsigned int Duty)
{
	CCPR2L = (unsigned char)(Duty>>2);
	CCP2CON |= (unsigned char)((Duty&0x0003)<<4);
}