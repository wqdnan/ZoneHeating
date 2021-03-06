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
//#include "SEG.h"
#include "\hardware\IIC.h"
#include "\hardware\ADC.h"
#include "\hardware\EEPROM.h"

//for modbus
#include "\modbus\TIM.h"
#include "\modbus\UART.h"
#include "\modbus\MODBUS.h"

//end for modbus


//#define _DEBUG 1
#define _ID_WRITE 1
#define _ID_NUM 4


//#pragma config FOSC = HS1         //外部 8MHz
#pragma config WDTEN  = OFF       //关闭 WDT
#pragma config PLLCFG = OFF       //关闭 PLL
#pragma config XINST  = OFF       //关闭 Extended 
#pragma config SOSCSEL= DIG       //数字 I/O

unsigned char fixedTimeFlag  = 0;

void Interrupt_High(void);      //中断函数 

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
	static unsigned int c10ms = 0,c1s = 0;
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
            //receCount &= 0x0f;		// 最多只接收16个字节数据
           
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
		c1s ++;
        if(c10ms >= 10)
        {
            c10ms = 0;      //10ms计时器清零
            bt10ms = 1;

        }
		if(c1s >= 1000)
		{
			c1s = 0;
			fixedTimeFlag = 0x35;
		}
		
	}
	
}

//unsigned char EE_RD_Buffer[16] = {0x00};   //读缓冲

float tmpADC = 0;
unsigned char tempNum = 0;
//-------------------------------------------------------------------------------
//	主程序
//-------------------------------------------------------------------------------
void main(void)
{
	unsigned char cnt = 0;      //变量
	unsigned char str[3] = {0};
	unsigned int iic_data = 0;
	unsigned int displayTmp = 0;
	unsigned int tmpU16 = 0;
	float tempF = 0;
	float Ip = 0;
	unsigned char i =0;
	unsigned char temp = 0;      //变量
	flash_array[0] = 0x10;
	flash_array[1] = 0x11;

	

	Delay10KTCYx(10);           //延时
	TIM2_PWM_Init();             //TMR2 PWM 输出初始化
	
	TIM1_Init();                 //TMR1初始化 	
	setDutyCycle_CCP2(100);
	UART_Init();                 //串口初始化
	ADC_Init();//
#ifndef _DEBUG
	I2C_Master_Init();	
#endif	
	
	//flash_writebyte(ADDRESS,&flash_array[0]);
	tempNum = flash_readbyte(ADDRESS,0);

	INTCONbits.PEIE = 1;         //外设中断
	INTCONbits.GIE  = 1;         //系统中断
	T1CONbits.TMR1ON= 1;         //使能TMR1


	Delay10KTCYx(160);           //延时
	
    
/*
//感觉没有效果 重新下载后则失效了
#ifdef _ID_WRITE
	temp = (unsigned char)_ID_NUM;
	EE_writebyte(1,temp);
#else
	slaveNum = EE_readbyte(1);
#endif
*/
	//--------------------------------------------------------------------------
	Delay10KTCYx(30);            //延时

//#ifndef _DEBUG
//	EE_Write_Byte(00,REG_IIC);
//#endif

	while(1)
	{

		//modbus
		timerProc();
		checkComm0Modbus();//读标志位,提取相关参数存入commData,但并未使用
		//end modbus


		if(fctn16Flag == 0x35)//接收到modbus的写寄存器操作
		{
			fctn16Flag = 0;
			switch(commData.commType)
			{
			case DUTY_CYCLE:
				//tempF = registerCtntRcv[0]&0xFF;
				tempF = commData.setDutyCycle;
				if(tempF>100)
					tempF = 100;
                else if(tempF<0)
                    tempF = 0;
				tempF = 100-tempF;
				setDutyCycle_CCP2(tempF);
				break;
			case SET_TEMPTURE:
				VOL_SET_TEMPTURE = commData.setTempture;
				break;
			case SET_VAR_A:
				VOL_TO_TMPTURE_A = commData.setVarA;
                VOL_TO_TMPTURE_B = commData.setVarB;
				break;
			case SET_VAR_B:
                VOL_TO_TMPTURE_A = commData.setVarA;
				VOL_TO_TMPTURE_B = commData.setVarB;
				break;
			}

		}

#ifndef _DEBUG		
		if(fixedTimeFlag == 0x35)//定时采样中
		{
			fixedTimeFlag = 0;
			iic_data = EE_Read_Byte(00);
			//tempF = ((iic_data/32768.0*2.048)*VOL_TO_TMPTURE_A+VOL_TO_TMPTURE_B);//*10+4000;//扩大1000倍
            tmpADC = ((iic_data/32768.0*2.048)*VOL_TO_TMPTURE_A+VOL_TO_TMPTURE_B);//iic_data;
//			registerCtntSnd[0] = (unsigned short )tempF;
		
			displayTmp = tmpADC*100;

			PID_Control(VOL_SET_TEMPTURE*100,tmpADC*100);//测试PWM通信结构时需要注解掉
			//0~65536
			sendBuf[0] = '0' + (unsigned int)displayTmp/10000%10;
			sendBuf[1] = '0' + (unsigned int)displayTmp/1000%10;
			sendBuf[2] = '0' + (unsigned int)displayTmp/100%10;
			sendBuf[3] = '0' + (unsigned int)displayTmp/10%10;
			sendBuf[4] = '0' + (unsigned int)displayTmp/1%10;
			sendBuf[5] = ',';
			sendBuf[6] = 0x0D;
			//UartSendBytes(sendBuf,7);

			tmpU16 = (tmpADC + 40.0)*100;
			registerCtntSnd[0] = tmpU16;//(tmpU16 & 0xff00) >> 8;
			VOL_REAL_TEMPTURE = tmpU16;
			//ADC-LOAD
			tmpU16 = (unsigned int)GET_ADValue();
			tempF = (tmpU16/4096*5);//ADC电压值
			//Vout = (2/30)Ip + 2.5
			//Ip = (Vout - 2.5)*15
			Ip = (tempF - 2.5)*15;
			tmpU16 = (Ip + 40.0)*100;
			registerCtntSnd[1] = tmpU16;//(tmpU16 & 0x00ff);
		}
#endif

	}
}

//-------------------------------------------------------------------------------
