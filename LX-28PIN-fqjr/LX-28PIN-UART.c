//-------------------------------------------------------------------------------//
//                            LIXUE 电子工作室                                   //
//                       http://lixuediy.taobao.com                              //
//                                版权所有                                       //
//                       EMAIL:lixue51@126.com                                   //
//                       Mobile:13109884800    QQ:83637020                       //
//                       Develop: MPLAB IDE V8.92 + MCC18 V3.46                  //
//                       PIC MCU: PIC18F26K80                                    //
//                       File: LX-28PIN-UART.c                                   //
//                       DATE: 2016-04-21    Version:  5.0                       //
//-------------------------------------------------------------------------------//
//
// 配 置 位：菜单栏 Help->Topics-> PIC18 Config Settings 左侧选择对应芯片型号
//
// 头 文 件：C:\Program Files\Microchip\mplabc18\v3.46\h
//
// 实验描述：使用串口助手发送数据,数码管循环显示接收缓冲区数据
//
// 注意事项：外部8MHz  9600波特率 N 8 1 格式
//           
//-------------------------------------------------------------------------------

#include "p18cxxx.h"              //头文件
#include "delays.h"
#include "SEG.h"
#include "IIC.h"
#include "ADC.h"

//for modbus
#include "\modbus\TIM.h"
#include "\modbus\UART.h"
#include "\modbus\MODBUS.h"

//end for modbus


//#pragma config FOSC = HS1         //外部 8MHz
#pragma config WDTEN  = OFF       //关闭 WDT
#pragma config PLLCFG = OFF       //关闭 PLL
#pragma config XINST  = OFF       //关闭 Extended 
#pragma config SOSCSEL= DIG       //数字 I/O

#define LED11  LATCbits.LATC4      //LED宏定义
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


//unsigned char RXBuffer[16] = {0};                                            //接收缓冲

//unsigned char rxFlag = 0;
//unsigned char txLen = 0;
/*
//-------------------------------------------------------------------------------
//	TMR1定时器初始化
//-------------------------------------------------------------------------------
void TMR1_Init(void)
{	   
	TMR1H = 0xF0;                //8MHz  4mS 
	TMR1L = 0x98;        
	T1CONbits.T1CKPS = 1;        //预分频1:2
	T1CONbits.RD16 = 1;          //16位TIMR
	T1CONbits.TMR1CS = 0;        //FOSC/4
	PIE1bits.TMR1IE	= 1;         //TMR1中断
}
*/
/*
//-------------------------------------------------------------------------------
//	串口初始化
//-------------------------------------------------------------------------------
void UART_Init(void)
{	
	TRISBbits.TRISB1 = 0;       //设定RB1 收发使能 输出低为发送 高位接收
	TRISCbits.TRISC7 = 1;       // 设置串口
	TRISCbits.TRISC6 = 0;
	
	SPBRG = 51;                 // 波特率 9600 N 8 1 
	RCSTAbits.SPEN = 1;         // 串口使能
	TXSTAbits.BRGH = 1;         // 高速模式
	TXSTAbits.SYNC = 0;         // 异步模式
	TXSTAbits.TXEN = 1;         // 发送允许
	RCSTAbits.CREN = 1;         // 允许接受
		
	PIE1bits.RCIE  = 1;         // 接收中断
	PIE1bits.TXIE  = 0;         // 发送中断

	RX_4851();
}
*/
//-------------------------------------------------------------------------------
//	高优先级中断向量
//-------------------------------------------------------------------------------
#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh(void)
{
	_asm
	goto      Interrupt_High     // 跳到中断程
	_endasm
}

//-------------------------------------------------------------------------------
//	高优先级中断服务程序
//-------------------------------------------------------------------------------
#pragma interrupt Interrupt_High
void Interrupt_High(void)
{
	static unsigned char temp;
	if(PIR1bits.RCIF)            // 接收中断
	{
		PIR1bits.RCIF = 0;
		if(RCSTAbits.FERR||RCSTAbits.OERR){
                RCSTAbits.SPEN=0;                   //reboot EUSART clear FERR & OERR
                RCSTAbits.SPEN=1;
                PIR1bits.RCIF=0;
                LATCbits.LATC3=0;
            }
            else{
            receTimeOut = 5; //20ms内没有接受到数据超时 接收计数归0
            receBuf[receCount] = RCREG;
            receCount ++;
            receCount &= 0x0f;		// 最多只接收16个字节数据
           
        }
	}

	if(PIR1bits.TMR1IF)          //T1中断
	{
		PIR1bits.TMR1IF = 0;     //清除标志位
		TMR1H = TIM1H_CNT;            //初值
		TMR1L = TIM1L_CNT;
		//开始功能函数
		dwIntTick++;
        bt1ms = 1;
        c10ms++;
        if(c10ms >= 10)
        {
            c10ms = 0;      //10ms计时器清零
            bt10ms = 1;
			fixedTimeFlag = 0x35;
        }
		
	}
	
}

//-------------------------------------------------------------------------------
//	主程序
//-------------------------------------------------------------------------------
void main(void)
{
	unsigned char temp = 0;      //变量
	unsigned char cnt = 0;      //变量
	unsigned char str[3] = {0};
	unsigned int iic_data = 0;
	float tempF = 0;
	
	TIM1_Init();                 //TMR1初始化 	
	UART_Init();                 //串口初始化
	//ADC_Init();
	//I2C_Master_Init();

	TRISCbits.TRISC4 = 0;       //设定RC4、RC5为输出
	TRISCbits.TRISC5 = 0;

	INTCONbits.PEIE = 1;         //外设中断
	INTCONbits.GIE  = 1;         //系统中断
	T1CONbits.TMR1ON= 1;         //使能TMR1

//	LED0 = 1;                    //LED0-LED5 亮
//	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
	LED4 = 1;
	LED5 = 1;
	Delay10KTCYx(160);           //延时
//	LED0 = 0;                    //LED0-LED5 灭
//	LED1 = 0;
	LED2 = 0;
	LED3 = 0;
	LED4 = 0;
	LED5 = 0;
	Delay10KTCYx(30);            //延时

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
					TXREG = RXBuffer[txLen];  // 将收到的数据发出
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
