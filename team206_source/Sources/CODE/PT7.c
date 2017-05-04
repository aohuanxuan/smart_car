/*
  脉冲计数器底层驱动函数（PT7口）
*/

#include "includes.h"


void PT7_Init(void) 
{
  PACTL = 0x50;                         //始能脉冲累加器，累加上升沿
  DDRT_DDRT3 = 0;
}

int Read_Speed(void)
{
  int speed = 0;
  PITTF_PTF0 = 1;
  speed = PACNT;  
  PACNT = 0;                      
  
  
  return speed;                      
}