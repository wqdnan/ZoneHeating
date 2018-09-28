//-------------------------------------------------------------------------------//
//                            LIXUE ���ӹ�����                                   //
//                       http://lixuediy.taobao.com                              //
//                                ��Ȩ����                                       //
//                       EMAIL:lixue51@126.com                                   //
//                       Mobile:13109884800    QQ:83637020                       //
//                       Develop: MPLAB IDE V8.92 + MCC18 V3.46                  //
//                       PIC MCU: PIC18F26K80                                    //
//                       File: LX-28PIN-UART.c                                   //
//                       DATE: 2016-04-21    Version:  5.0                       //
//-------------------------------------------------------------------------------//
//
// �� �� λ���˵��� Help->Topics-> PIC18 Config Settings ���ѡ���ӦоƬ�ͺ�
//
// ͷ �� ����C:\Program Files\Microchip\mplabc18\v3.46\h
//
// ʵ��������ʹ�ô������ַ�������,�����ѭ����ʾ���ջ���������
//
// ע������ⲿ8MHz  9600������ N 8 1 ��ʽ
//           
//-------------------------------------------------------------------------------

#include "p18cxxx.h"              //ͷ�ļ�
#include "delays.h"
#include "SEG.h"
#include "IIC.h"
#include "ADC.h"

//for modbus
#include "\modbus\TIM.h"
#include "\modbus\UART.h"
#include "\modbus\MODBUS.h"

//end for modbus


//#pragma config FOSC = HS1         //�ⲿ 8MHz
#pragma config WDTEN  = OFF       //�ر� WDT
#pragma config PLLCFG = OFF       //�ر� PLL
#pragma config XINST  = OFF       //�ر� Extended 
#pragma config SOSCSEL= DIG       //���� I/O

#define LED11  LATCbits.LATC4      //LED�궨��
#define LED22  LATCbits.LATC5
#define LED2  LATCbits.LATC0
#define LED3  LATAbits.LATA5
#define LED4  LATAbits.LATA3
#define LED5  LATAbits.LATA2

#define LED0_ON() LED11 = 0
#define LED0_OFF() LED11 = 1
#define LED1_ON() LED22 = 0
#define LED1_OFF() LED22 = 1

unsigned char fixedTimeFlag  = 0;

//#define pin_en1485 LATBbits.LATB1
//#define RX_4851() pin_en1485 = 1
//#define TX_4851() pin_en1485 = 0


//unsigned char RXBuffer[16] = {0};                                            //���ջ���

//unsigned char rxFlag = 0;
//unsigned char txLen = 0;
/*
//-------------------------------------------------------------------------------
//	TMR1��ʱ����ʼ��
//-------------------------------------------------------------------------------
void TMR1_Init(void)
{	   
	TMR1H = 0xF0;                //8MHz  4mS 
	TMR1L = 0x98;        
	T1CONbits.T1CKPS = 1;        //Ԥ��Ƶ1:2
	T1CONbits.RD16 = 1;          //16λTIMR
	T1CONbits.TMR1CS = 0;        //FOSC/4
	PIE1bits.TMR1IE	= 1;         //TMR1�ж�
}
*/
/*
//-------------------------------------------------------------------------------
//	���ڳ�ʼ��
//-------------------------------------------------------------------------------
void UART_Init(void)
{	
	TRISBbits.TRISB1 = 0;       //�趨RB1 �շ�ʹ�� �����Ϊ���� ��λ����
	TRISCbits.TRISC7 = 1;       // ���ô���
	TRISCbits.TRISC6 = 0;
	
	SPBRG = 51;                 // ������ 9600 N 8 1 
	RCSTAbits.SPEN = 1;         // ����ʹ��
	TXSTAbits.BRGH = 1;         // ����ģʽ
	TXSTAbits.SYNC = 0;         // �첽ģʽ
	TXSTAbits.TXEN = 1;         // ��������
	RCSTAbits.CREN = 1;         // �������
		
	PIE1bits.RCIE  = 1;         // �����ж�
	PIE1bits.TXIE  = 0;         // �����ж�

	RX_4851();
}
*/
//-------------------------------------------------------------------------------
//	�����ȼ��ж�����
//-------------------------------------------------------------------------------
#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh(void)
{
	_asm
	goto      Interrupt_High     // �����жϳ�
	_endasm
}

//-------------------------------------------------------------------------------
//	�����ȼ��жϷ������
//-------------------------------------------------------------------------------
#pragma interrupt Interrupt_High
void Interrupt_High(void)
{
	static unsigned char temp;
	if(PIR1bits.RCIF)            // �����ж�
	{
		PIR1bits.RCIF = 0;
		if(RCSTAbits.FERR||RCSTAbits.OERR){
                RCSTAbits.SPEN=0;                   //reboot EUSART clear FERR & OERR
                RCSTAbits.SPEN=1;
                PIR1bits.RCIF=0;
                LATCbits.LATC3=0;
            }
            else{
            receTimeOut = 5; //20ms��û�н��ܵ����ݳ�ʱ ���ռ�����0
            receBuf[receCount] = RCREG;
            receCount ++;
            receCount &= 0x0f;		// ���ֻ����16���ֽ�����
           
        }
	}

	if(PIR1bits.TMR1IF)          //T1�ж�
	{
		PIR1bits.TMR1IF = 0;     //�����־λ
		TMR1H = TIM1H_CNT;            //��ֵ
		TMR1L = TIM1L_CNT;
		//��ʼ���ܺ���
		dwIntTick++;
        bt1ms = 1;
        c10ms++;
        if(c10ms >= 10)
        {
            c10ms = 0;      //10ms��ʱ������
            bt10ms = 1;
			fixedTimeFlag = 0x35;
        }
		
	}
	
}

//-------------------------------------------------------------------------------
//	������
//-------------------------------------------------------------------------------
void main(void)
{
	unsigned char temp = 0;      //����
	unsigned char cnt = 0;      //����
	unsigned char str[3] = {0};
	unsigned int iic_data = 0;
	float tempF = 0;
	
	TIM1_Init();                 //TMR1��ʼ�� 	
	UART_Init();                 //���ڳ�ʼ��
	//ADC_Init();
	//I2C_Master_Init();

	TRISCbits.TRISC4 = 0;       //�趨RC4��RC5Ϊ���
	TRISCbits.TRISC5 = 0;

	INTCONbits.PEIE = 1;         //�����ж�
	INTCONbits.GIE  = 1;         //ϵͳ�ж�
	T1CONbits.TMR1ON= 1;         //ʹ��TMR1

//	LED0 = 1;                    //LED0-LED5 ��
//	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
	LED4 = 1;
	LED5 = 1;
	Delay10KTCYx(160);           //��ʱ
//	LED0 = 0;                    //LED0-LED5 ��
//	LED1 = 0;
	LED2 = 0;
	LED3 = 0;
	LED4 = 0;
	LED5 = 0;
	Delay10KTCYx(30);            //��ʱ

	//TX_4851();


	//EE_Write_Byte(00,REG_IIC);
	while(1)
	{

		//modbus
		timerProc();
		checkComm0Modbus();
		//end modbus

		//iic_data = EE_Read_Byte(00);

		//tempF = ((float)iic_data)/32768.0*2.048;
		if(fixedTimeFlag == 0x35)
		{
			fixedTimeFlag = 0;
	//		iic_data = (unsigned int)GET_ADValue();
	//		tempF = (iic_data/4096*5);
		}
//			LED0_OFF();
//			LED1_OFF();
/*
		if(tempF<1)
		{
			LED0_OFF();
			LED1_OFF();
		}
		else if(tempF < 2)
		{
			LED0_ON();
			LED1_OFF();
		}
		else if(tempF < 3)
		{
			LED0_OFF();
			LED1_ON();
		}
		else
		{
			LED0_ON();
			LED1_ON();
		}
*/		
	//	txLen = 0;
/*
		TX_4851();
		
		while(TXSTA1bits.TRMT==0);
		TXREG = (unsigned int)(tempF/10)%10+'0';
		while(TXSTA1bits.TRMT==0);
		TXREG = (unsigned int)(tempF)%10+'0';
		while(TXSTA1bits.TRMT==0);
		TXREG = '.';
		while(TXSTA1bits.TRMT==0);
		TXREG = (unsigned int)(tempF*10)%10+'0';
		while(TXSTA1bits.TRMT==0);
		TXREG = (unsigned int)(tempF*100)%10+'0';
		while(TXSTA1bits.TRMT==0);
		TXREG = (unsigned int)(tempF*1000)%10+'0';
		while(TXSTA1bits.TRMT==0);
		TXREG = (unsigned int)(tempF*10000)%10+'0';
		while(TXSTA1bits.TRMT==0);
		TXREG = 'V';
		while(TXSTA1bits.TRMT==0);
		TXREG = 0x0a;
		while(TXSTA1bits.TRMT==0);
		RX_4851();
*/
//-----------------------------------------------------
/*
		if(rxFlag == 0x35)
		{
			rxFlag = 0;
			txLen = 0;
			TX_4851();

			while(txLen < 10)
			{
				if(TXSTA1bits.TRMT)
				{
					TXREG = RXBuffer[txLen];  // ���յ������ݷ���
					txLen ++;
				}
			}
			RX_4851();	
		}
*/
//----------------------------------------------------------
		//Delay10KTCYx(500);

	}
}

//-------------------------------------------------------------------------------
