#include "TIM.h"

#include "UART.h"
unsigned int b1ms;
unsigned int bt1ms,b10ms,bt10ms,b100ms,bt100ms,c10ms;

void TIM1_Init()
{
/*
    ADCON2bits.TRIGSEL=0b0011;
    OPTION_REGbits.TMR0CS=0;
    OPTION_REGbits.PSA=0;
    OPTION_REGbits.PS=3; //只要写TMR0 就会清零 所以中断里需要再次预设分频 3=2ms中断一次 4为5ms
    INTCONbits.TMR0IE=1;

    TMR0=0;


    INTCONbits.PEIE = 1;    // Enable peripheral interrupt
    INTCONbits.GIE = 1;     // enable global interrupt

    TMR1IF=0;
    T1CONbits.TMR1CS=0;
    T1CONbits.T1CKPS=0;
    TMR1H=0xfe;
    TMR1L=0x00;
    T1CONbits.TMR1ON=1;

    PIE1bits.TMR1IE=1;
    INTCONbits.PEIE = 1;    // Enable peripheral interrupt
    INTCONbits.GIE = 1;     // enable global interrupt
*/
	TMR1H = TIM1H_CNT;                //8MHz  定一个1ms的定时中断
	TMR1L = TIM1L_CNT;        
	T1CONbits.T1CKPS = 1;        //预分频1:2
	T1CONbits.RD16 = 1;          //16位TIMR
	T1CONbits.TMR1CS = 0;        //FOSC/4
	PIE1bits.TMR1IE	= 1;         //TMR1中断
	
}

//定时处理
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