
/*********************************************************
                       events.c
                     定时器中断函数
********************************************************/

#include "includes.h"


/*
*********************************************************************************************************
* Description: Global variable
*********************************************************************************************************
*/
unsigned char TimerFlag10ms = 0;
unsigned char CCDTIME = 4;


/*
*********************************************************************************************************
* Description: PITCh0IntISR
* Note: 1ms at 40M
*********************************************************************************************************
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED

__interrupt void PITCh0IntISR(void) {

    static unsigned char TimerCnt10ms = 0;
    static unsigned char Delay_Count = 0;
    unsigned char baoguang_time = 0;
    
    if (Flag_Jing) {
      baoguang_time = CCDTIME;
    }else{
      baoguang_time = CCDTIME;       //修改本句话修改动静态曝光模式
    }

    PITTF_PTF0 = 1;

    TimerCnt10ms++;

    if (TimerCnt10ms == 1) 
    {
      Image_Process();     
    }
    if (TimerCnt10ms == 2) 
    {
      CCD_Process();   
    }
    if (TimerCnt10ms == 3) 
    {
      CCD2_Process();   
      TimerFlag10ms = 1;
    }    
    if (TimerCnt10ms == 4) 
    {
                                          
        if (Delay_Count < 100){       //起跑不检测坡道
          Delay_Count ++;
        }
        if (Delay_Count > 99){
          if ((!Lren_Flag) && (!Rren_Flag) && (!Ren_Delay) && Po_Swich){
               Podao();
          }
        }
    }
    if (TimerCnt10ms == 5) 
    {
      Direction_Control();      
    }
    if (TimerCnt10ms == 6)
    {
      Speed_Control();
    }
    
    if(CCDTIME > 2){
      if (TimerCnt10ms == 7)
      {
        ImageCapture2(Pixel2);
      }
      if(TimerCnt10ms == 8) 
      {
        ImageCapture(Pixel);
        Change_CCDTIME();//动态修改曝光时间      
        TimerCnt10ms = 0;
      }
        
      if (TimerCnt10ms == (8-baoguang_time))
      {
        StartIntegration2();
        StartIntegration();
      }
    }else{
      if (TimerCnt10ms == (8-baoguang_time))
      {
        StartIntegration2();
        StartIntegration();
      }
      
      if (TimerCnt10ms == 8)
      {
        ImageCapture2(Pixel2);
      }
      if(TimerCnt10ms == 8) 
      {
        ImageCapture(Pixel);
        Change_CCDTIME();//动态修改曝光时间      
        TimerCnt10ms = 0;
      }
    }

}

#pragma CODE_SEG DEFAULT