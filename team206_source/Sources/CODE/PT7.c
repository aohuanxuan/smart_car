/*
  ����������ײ�����������PT7�ڣ�
*/

#include "includes.h"


void PT7_Init(void) 
{
  PACTL = 0x50;                         //ʼ�������ۼ������ۼ�������
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