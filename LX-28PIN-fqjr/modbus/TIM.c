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
    OPTION_REGbits.PS=3; //ֻҪдTMR0 �ͻ����� �����ж�����Ҫ�ٴ�Ԥ���Ƶ 3=2ms�ж�һ�� 4Ϊ5ms
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
	TMR1H = TIM1H_CNT;                //8MHz  ��һ��1ms�Ķ�ʱ�ж�
	TMR1L = TIM1L_CNT;        
	T1CONbits.T1CKPS = 1;        //Ԥ��Ƶ1:2
	T1CONbits.RD16 = 1;          //16λTIMR
	T1CONbits.TMR1CS = 0;        //FOSC/4
	PIE1bits.TMR1IE	= 1;         //TMR1�ж�
	
}

//��ʱ����
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
            if(receTimeOut==0 && receCount>0)   //�ж�ͨѶ�����Ƿ�ʱ
            {
                receCount = 0;      //�����յ�ַƫ�ƼĴ�������
		checkoutError = 0;
            }
        }
	}
	if(bt100ms)
	{
		bt100ms = 0;
		b100ms = 1;
	}
    if(bt10ms)      //�ж��ж�10ms��־λ�Ƿ�1
    {
        bt10ms = 0;     //���ж�10ms��־λ
	b10ms = 1;
        c200ms++;                   //200ms��ʱ����1
        if(c200ms >= 20)            //�ж��Ƿ��ʱ��200ms
        {
            c200ms = 0;             //��200ms��ʱ��
        }
    }
}