//-------------------------------------------------------------------------------//
//                            LIXUE 电子工作室                                   //
//                       http://lixuediy.taobao.com                              //
//                                版权所有                                       //
//                       EMAIL:lixue51@126.com                                   //
//                       Mobile:13109884800    QQ:83637020                       //
//                       Develop: MPLAB IDE V8.92 + MCC18 V3.46                  //
//                       PIC MCU: PIC18Fxxxx                                     //
//                       File: SEG.h                                             //
//                       DATE: 2016-04-21    Version:  5.0                       //
//-------------------------------------------------------------------------------//
#ifndef _SEG_H
#define _SEG_H

#define Smg_a    0x01
#define Smg_b    0x02
#define Smg_c    0x04
#define Smg_d    0x08
#define Smg_e    0x10
#define Smg_f    0x20
#define Smg_g    0x40
#define Smg_dp   0x80

#define Bmp0Map          Smg_a | Smg_b | Smg_c | Smg_d | Smg_e | Smg_f 
#define Bmp1Map          Smg_b | Smg_c
#define Bmp2Map          Smg_a | Smg_b | Smg_d | Smg_e | Smg_g
#define Bmp3Map          Smg_a | Smg_b | Smg_c | Smg_d | Smg_g
#define Bmp4Map          Smg_b | Smg_c | Smg_f | Smg_g
#define Bmp5Map          Smg_a | Smg_c | Smg_d | Smg_f | Smg_g
#define Bmp6Map          Smg_a | Smg_c | Smg_d | Smg_e | Smg_f | Smg_g
#define Bmp7Map          Smg_a | Smg_b | Smg_c 
#define Bmp8Map          Smg_a | Smg_b | Smg_c | Smg_d | Smg_e | Smg_f | Smg_g
#define Bmp9Map          Smg_a | Smg_b | Smg_c | Smg_d | Smg_f | Smg_g
#define BmpAMap          Smg_a | Smg_b | Smg_c | Smg_e | Smg_f | Smg_g
#define BmpBMap          Smg_c | Smg_d | Smg_e | Smg_f | Smg_g
#define BmpCMap          Smg_a | Smg_d | Smg_e | Smg_f 
#define BmpDMap          Smg_b | Smg_c | Smg_d | Smg_e | Smg_g
#define BmpEMap          Smg_a | Smg_d | Smg_e | Smg_f | Smg_g
#define BmpFMap          Smg_a | Smg_e | Smg_f | Smg_g
#define BmpPMap          Smg_a | Smg_b | Smg_e | Smg_f | Smg_g
#define BmpEmtyMap       0x00

void Interrupt_High(void);      //中断函数 
void SegDisplay(void);          //数码管显示


#endif
