/*
  PWM底层驱动函数
*/

#include "includes.h"

void PWM_Init(void) 
{
  PWME &= 0xF0;      //关闭通道
  PWMCTL_CON01 = 1;    //01连起来供给舵机
  PWMCAE &= 0XF0;    //左对齐
  PWMPOL |= 0X0F;    //先输出高电平
  PWMCLK = 0X03;    //01选择SA时钟,23选择B
  PWMPRCLK = 0X44;  //对A时钟进行16分频,B时钟进行16分频 A=2.5M B=2.5M
  PWMSCLA = 2;     //SA=2.5M/(2*2)=625K 
      
  PWMPER01 = 2084;  // 周期为 625K/2084=300HZ  舵机
  PWMDTY01 = 920; //舵机中间值小是左转大是右转 （旧舵机840）
       
  PWMPER2 = 250;  //  周期为 2.5M/250=10KHZ  
  PWMPER3 = 250;   
  PWMDTY2 = 0;     
  PWMDTY3 = 0;   
      
  PWME |= 0X0F;   //通道使能

}

void Steer_Change(uint16_t pwm) //修改舵机PWM
{
  PWMDTY01 = pwm;
}

void Motor_Change(uint8_t pwm1, uint8_t pwm2)  //修改电机PWM
{
  PWMDTY2 = pwm1;
  PWMDTY3 = pwm2;
}