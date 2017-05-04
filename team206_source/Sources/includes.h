

#ifndef   INCLUDES_H
#define   INCLUDES_H


/* Aditional standard ANSI C types */
#ifndef int8_t
typedef signed char         int8_t;
#endif
#ifndef int16_t
typedef signed int          int16_t;
#endif
#ifndef int32_t
typedef signed long int     int32_t;
#endif

#ifndef uint8_t
typedef unsigned char       uint8_t;
#endif
#ifndef uint16_t
typedef unsigned int        uint16_t;
#endif
#ifndef uint32_t
typedef unsigned long int   uint32_t;
#endif
/*#ifndef TPE_Float
typedef float               TPE_Float;
#endif*/
#ifndef char_t
typedef char                char_t;
#endif

#define WIDE 54                      //赛道宽度（跑道不同需要更改）
/*
*********************************************************************************************************
* Description: No
*********************************************************************************************************
*/
#include  <hidef.h>
#include  <MC9S12XS128.h>
#pragma   LINK_INFO DERIVATIVE "MC9S12XS128"


/*
*********************************************************************************************************
* Description: No
*********************************************************************************************************
*/
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <ctype.h>


/*
*********************************************************************************************************
* Description: Includes
*********************************************************************************************************
*/
#include  "CPU.h"
#include  "SCI.h"
#include  "ADC.h"
#include  "PIT.h"
#include  "Vector.h"
#include  "PWM.h"
#include  "PT7.h"

#include  "events.h"
#include  "ccd.h"
#include  "ctrol.h"
#include  "send.h"
#include  "others.h"


/*
*********************************************************************************************************
* Global variable
*********************************************************************************************************
*/
extern unsigned char Pixel[128];
extern unsigned char Pixel2[128];
extern signed int M_error_now;                     //本次偏差量
extern signed int M_error_error;                       //偏差之差
extern int speed_now;                                 //速度
extern unsigned char CCDTIME;                           //曝光时间

extern int SPEED_MIN;                                 //速度
extern int SPEED    ;
extern int SPEED_MAX;

extern int M_D;

extern unsigned char Flag_SImg;
extern unsigned char Flag_SImg2;
extern unsigned char Flag_SMsg;                       //发送内容标志

extern unsigned char Flag_Podao;       
extern unsigned char Lren_Flag;
extern unsigned char Rren_Flag;

extern unsigned char Podao_Time;
extern unsigned char Flag_Stop;

extern unsigned char Flag_Zhangai;
extern unsigned char Flag_Shizi;
extern unsigned char Flag_Zhi;

extern unsigned char Renzi_Mode;    //人字模式选择
extern unsigned char Flag_Tiaoshi;

extern unsigned char wide_now;

extern unsigned char Flag_S;
extern unsigned char S_Mode;

extern unsigned char Renzi_Time;

extern unsigned char Podao_Count;
extern unsigned char average;
extern signed int Middle;
extern unsigned int TLY_I;

extern unsigned char Fall_Count;
extern unsigned char speed_cut;
extern unsigned char sppeed_m;

extern unsigned char Lloss_Flag;
extern unsigned char Rloss_Flag;
extern unsigned char PG_Time;
extern unsigned char podao_t;
extern unsigned char Ren_Delay;

extern unsigned char Stop_Count;
extern unsigned char Rzhi_Count;
extern unsigned char Flag_Jing;
extern unsigned char Po_Swich;
extern unsigned int T_VALUE_Max;
#endif