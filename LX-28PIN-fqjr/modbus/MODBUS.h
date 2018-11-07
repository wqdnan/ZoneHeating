#ifndef __MODBUS_H
#define __MODBUS_H

typedef char CHAR,INT8,int8,S8,s8,*PCHAR,*pchar,*PINT8,*pint8,*PS8,*ps8;
typedef unsigned char uchar,UCHAR,U8,u8,UINT8,uint8,BYTE,*puchar,*PUCHAR,*PU8,*pu8,*PUINT8,*puint8,*PBYTE;

// short,ushort

// int,uint
typedef int SHORT,INT,INT16,int16,/*S16,s16,*/WCHAR,wchar,WORD,word,*PSHORT,*pshort,*PINT16,*pint16,*PWCHAR,*S16,*s16,*pwchar,*PWORD,*pword;
typedef unsigned int USHORT,ushort,UINT,UINT16,uint16,U16,u16,*PUSHORT,*pushort,*PUINT16,*puint16,*PU16,*pu16;

// long,ulong
typedef long LONG,*PLONG,*plong;
typedef unsigned long ULONG,ulong,UINT32, uint32, *PULONG,*pulong, *PUINT32, *puint32;
// void
typedef void VOID,*PVOID,*LPVOID;

// convenience
typedef int BOOLEAN,BOOL;
//
// Macros
typedef enum
{
	INIT,
	DUTY_CYCLE,
	SET_TEMPTURE,
	SET_VAR_A,
	SET_VAR_B,
	REAL_TEMPTURE,
	REAL_CURRENT
}enumComm;

typedef struct
{
	UINT8 rcvAddr;             //从当前串口数据帧中接收到的从机ID号
	enumComm commType;            //当前通信串口的数据类型
	float setTempture;         //记录上位机发送给本机的预设温度值
	float setDutyCycle;        //记录上位机发送给本机的占空比值
	float setVarA;             //记录上位机发送给本机的温度校准参数A
	float setVarB;             //记录上位机发送给本机的温度校准参数B
	float realTempture;        //本机待发送给上位机的实时温度值
	float realCurrent;         //本机待发送给上位机的实时电流值

}structComm;
//
#define TRUE                        1
#define FALSE                       0

//写参数：占空比、预设温度、校准参数（A、B）、PID预调参数（P、I、D）
//读参数：实时温度、实时电流
#define MDBS_LEN 16  //预留长度，按照每个参数16个从机数量来设置，每个从机使用自身对应位置的参数
extern unsigned short registerCtntSnd[MDBS_LEN];
extern unsigned short registerCtntRcv[MDBS_LEN];
extern structComm commData;
extern unsigned char fctn16Flag;
extern unsigned char slaveNum;
//
// Exported functions declare
//
unsigned short crc16(const unsigned char *puchMsg, unsigned int usDataLen);
void beginSend(void);
void checkComm0Modbus(void);
void readCoil(void);
void readRegisters(void);
void forceSingleCoil(void);
void presetSingleRegister(void);
void presetMultipleRegisters(void);
void forceMultipleCoils(void);
UINT16 getRegisterVal(UINT16 addr,UINT16 *tempData);
UINT16 setRegisterVal(UINT16 addr,UINT16 tempData);
UINT16 getCoilVal(UINT16 addr,UINT16 *tempData);
UINT16 setCoilVal(UINT16 addr,UINT16 tempData);



//
// External variables declare
//
extern UINT8   localAddr;


#endif
