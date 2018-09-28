
#include "TYPE.h"
#include "UART.h"



int	dwTickCount,dwIntTick;//ʱ��
unsigned char sendBuf[16], receBuf[16];//���ͽ��ջ�����
unsigned char checkoutError;// ==2 żУ���
unsigned char receTimeOut;//���ճ�ʱ

unsigned char sendCount;
unsigned char receCount;

void UART_Init()
{
/*
     SPBRG=1;

    TXSTAbits.CSRC=1;
    TXSTAbits.BRGH=1;       // select low speed Baud Rate (see baud rate calcs below)
    BAUDCONbits.BRG16=1;
    TXSTAbits.TX9=0;        // select 8 data bits
    TXSTAbits.SYNC=0;
    TXSTAbits.SENDB=0;

    RCSTAbits.SPEN=1; //ʹ�ܴ��� ����RX/DT��TX/CK��������Ϊ�������ţ�
    TXSTAbits.TXEN = 1;

   RCSTAbits.RX9=0;        // select 8 data bits
//   RCSTAbits.CREN=1;       // receive enabled

    PIR1bits.RCIF=0;        // make sure receive interrupt flag is clear
    PIE1bits.RCIE=1;        // enable UART Receive interrupt
    INTCONbits.PEIE = 1;    // Enable peripheral interrupt
    INTCONbits.GIE = 1;     // enable global interrupt
*/
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

//*************************************************************************************
// Send one byte via UART
//*************************************************************************************
void UartSendByte(unsigned char mydata_byte) {

    TXREG = mydata_byte;       // transmit data
    while(!TXSTAbits.TRMT);    // make sure buffer full bit is high before transmitting

    
}

void UartSendBytes (unsigned char*buf,unsigned int nLen)
{
	UINT i;
	TX_4851();
	for(i=0;i<100;i++);//��ʱ
	for (i = 0;i < nLen;i ++)
		UartSendByte (buf[i]);
	RX_4851();
}