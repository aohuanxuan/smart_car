
/*********************************************************
                       ctrol.c
                     小车控制函数
********************************************************/


#include "includes.h"

#define  S_I    60                      //速度PID
#define  S_D    0
#define  S_P    36
                                        //舵机中间值
#define MIDDLE_VALUE 920

int SPEED_MIN = 0;                    //速度
int SPEED     = 0;
int SPEED_MAX = 0;

signed long turn_value = 0;


int speed_set;                //设定的速度
int speed_now = 0;                        //编码器返回的速度  
signed int S_error_now = 0;          //与期望速度的偏差
int speed_value = 0; 

int M_P = 25;
int M_D = 100;                   //舵机PD

unsigned char speed_cut = 10;
unsigned char sppeed_m  = 0;
unsigned char Stop_Count = 0;


void Direction_Control(void)      //舵机控制函数
{
  int turn_pwm = 0;
  
  M_P = 25;               //普通P值
  if (Flag_S && S_Mode && (!Flag_Podao)){  //小S模式下的P值
    if ((M_error_now<20) && (M_error_now>-20)) {
      M_P = 15;
    }else{
      M_P = 12;
    }
  }
  if (Flag_Zhangai){      //障碍P值
    M_P = 30;
  }
    
  turn_value = (M_P*M_error_now) + (M_error_error*M_D);  
  turn_value = turn_value/10;
  
  if (Lren_Flag) {               //人字情况
    turn_value = 290;  
  }else if(Rren_Flag) {
    turn_value = -290;
  
}  
  if (turn_value > 290) {
    turn_value = 290;
  }
  if (turn_value < -290) {
    turn_value = -290;
  }
  
  turn_pwm = MIDDLE_VALUE + turn_value;
  Steer_Change(turn_pwm);
}
  void Speed_Control(void)          //速度控制函数
{
  signed int S_error_last = 0;
  signed int S_error_error = 0;
  signed int speed_pwm1 = 0; 
  signed int speed_pwm2 = 0;
  unsigned char jiansu = 0;       //需要反转减速标志
  
  
  if ((turn_value<sppeed_m)&&(turn_value>0))   //弯道速度
  {                          
    speed_set = SPEED - turn_value/speed_cut;
  }
  else if ((turn_value<=0)&&(turn_value>(0-sppeed_m)))
  {
    speed_set = SPEED + turn_value/speed_cut;
  } else 
  {
    speed_set = SPEED_MIN;                                                
  }
  if (Flag_Zhi) {                         //直道速度
    speed_set = SPEED_MAX;
  }
  
  if (Lren_Flag && (Renzi_Time<30)) {               //人字情况  
    speed_set = Rzhi_Count;
  }else if(Rren_Flag && (Renzi_Time<30)) {
    speed_set = Rzhi_Count;
  }
  
  if (Flag_Podao) {     //坡道情况
    speed_set = 115;
  }
  
  if (Flag_Stop){     //起跑线情况
    speed_set = 0;
  }
  
  S_error_last = S_error_now;
  
  speed_now = Read_Speed();          //读取当前速度                
  
  S_error_now = speed_set - speed_now;                   //P
  S_error_error = S_error_now - S_error_last;            //D
   
  speed_value += S_I * S_error_now + S_P * S_error_error; //PID算式                   
  
  if (speed_value > 8000)                                //最大、最小转速限制
  {
    speed_value = 8000;
    speed_pwm1 = speed_value/40;
    speed_pwm2 = 0;
    
    Stop_Count = 0;
  } else if (speed_value <= 0)
  {
    Stop_Count ++;
    if (Stop_Count>15) {
      Stop_Count = 16;
    }   
                                                                 //给反转减速的情况
    if (Lren_Flag || Rren_Flag){
      if ((SPEED_MAX>190) && (Renzi_Time<(38-Rzhi_Count))){
        jiansu = 1;
      }else{
        jiansu = 0;
      }  
    }else if ((Stop_Count>(Rzhi_Count-5)) && (SPEED_MAX>200)){
      jiansu = 1;
    }else{
      jiansu = 0;
    }
     
    if (speed_value < -6000) {
      speed_value = -6000;
    }
    
    if ((Flag_Stop&&(!Flag_Tiaoshi)) || jiansu){          //反转
      speed_pwm2 = (0-speed_value)/40;
      speed_pwm1 = 0;
    
    } else{
      speed_value = 0;
      speed_pwm1 = 0;
      speed_pwm2 = 0;  
    }
    
  } else {
    speed_pwm1 = speed_value/40;
    speed_pwm2 = 0;
    
    Stop_Count = 0;
  }
  
  if (speed_now<20 && Flag_Stop) {
    speed_pwm1 = 0;
    speed_pwm2 = 0;
    
  }
  if (S_DIRECTION && Flag_Stop){     //防止后退
    speed_pwm1 = 0;
    speed_pwm2 = 0;
  }
  
  Motor_Change(speed_pwm1,speed_pwm2);
  
}