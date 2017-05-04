/*********************************************************
                       others.c
                       ��������
********************************************************/

#include "includes.h"

#define T_VALUE_Min 6200            //�µ��ж���ֵ
unsigned int T_VALUE_Max = 10000;            //�µ��ж���ֵ
#define T_VALUE_Mid 8400

#define HONGWAI_TIME 20000        //�����������ж�ʱ������ʱ��Ҫ��С��

unsigned char Flag_SImg = 0;     //����CCD1ͼ��
unsigned char Flag_SImg2 = 0;    //����CCD2ͼ��
unsigned char Flag_SMsg = 0;     //���͵�����Ϣ

unsigned char Podao_Time = 0;
unsigned char Flag_Qipao = 0;
unsigned int Hongwai_Time = 0;
unsigned char Flag_Qipao1 = 0;
unsigned char Flag_Qipao2 = 0;
unsigned char Flag_Stop = 0;
unsigned char Podao_Count = 0;
unsigned char Flag_Podao = 0;
unsigned char podao_t = 0;

unsigned char Renzi_Mode = 0;    //����ģʽѡ��
unsigned char S_Mode = 0;
unsigned char Flag_Tiaoshi = 0;    //����ģʽѡ��
unsigned char Flag_Jing = 0;
unsigned char Po_Swich = 0;

unsigned int TLY_I = 0;         //�µ�����ֵ
unsigned int t_value[5] = {0,0,0,0,0};  //��������

void LED_Init(void)          //LED��ʼ��
{
    LED_DDR = 0XFF;
    HONGWAI1_DDR = 0;
    HONGWAI2_DDR = 0;
    LED = 0XFF;
}

void Switchs_Init(void)      //���뿪�س�ʼ��
{
  DDRA = 0x00;
}

void FMQ_Init(void)          //��������ʼ��
{
  FMQ_DDR = 1;
  FMQ = 0; 
}
void Choose(void) {
  
  Choose_CCDTIME();   //ѡ���ع�ʱ��
  
  Choose_Po();      //ѡ���µ�ģʽ
  
  if (PORTA_PA7 == 1) {  //���뿪��8ѡ��СSģʽ
    S_Mode = 1;    
  } else{
    S_Mode = 0;
  }
  
  if (PORTA_PA5==0) { //���뿪��6ѡ�����ģʽ
    Tiaoshi_Speed();    //ѡ������ٶ�
    Choose_Send();      //ѡ���͵�����
    Flag_Tiaoshi = 1;
  }
  else{
    Choose_Speed();     //ѡ������ٶ�
    Flag_Tiaoshi = 0;
  }
  
  if (PORTA_PA6==0) {    //���뿪��7ѡ������ģʽ
    Renzi_Mode = 1;
  }else{
    Renzi_Mode = 0;
  }
  
  
}
void Choose_CCDTIME(void)    //���뿪��4.5ѡ���ع�ʱ��
{
   if (PORTA_PA3 && PORTA_PA4)    //�����뿪��4.5��ʾ���ع�ʱ��
   {
      CCDTIME = 2;  
   } else if ((PORTA_PA3==0) && PORTA_PA4)    
   {
      CCDTIME = 3;  
   } else if (PORTA_PA3 && (PORTA_PA4==0))   
   {
      CCDTIME = 4;  
   } else if ((PORTA_PA3==0) && (PORTA_PA4==0))   
   {
      CCDTIME = 5;  
   }
}

void  Choose_Speed(void)              //���뿪��1.2.3ѡ���ٶ�
{
  unsigned char speed_num = 0;
  
  speed_num = (~PORTA) & 0x07;
  
  switch(speed_num) { 
    case 0:
      SPEED_MIN = 132; 
      SPEED     = 132;
      SPEED_MAX = 132;
      sppeed_m = 0;
      speed_cut = 10;
      M_D = 70;
      Rzhi_Count = 22;
      break;
     
    case 1:
      SPEED_MIN = 132; 
      SPEED     = 154;
      SPEED_MAX = 182;
      sppeed_m = 220;
      speed_cut = 10;
      M_D = 80;
      Rzhi_Count = 19;
      break;    
    
    case 2:
      SPEED_MIN = 144; 
      SPEED     = 168;
      SPEED_MAX = 196;
      M_D = 90;
      sppeed_m = 240;
      speed_cut = 10;
      Rzhi_Count = 17;
      break;
      
    case 3:
      SPEED_MIN = 156; 
      SPEED     = 182;
      SPEED_MAX = 210;
      M_D = 100;
      sppeed_m = 260;
      speed_cut = 10;
      Rzhi_Count = 15;
      break;
    case 4:
      SPEED_MIN = 162; 
      SPEED     = 189;
      SPEED_MAX = 217;
      M_D = 105;
      sppeed_m = 270;
      speed_cut = 10;
      Rzhi_Count = 14;
      break;    
    case 5:
      SPEED_MIN = 168; 
      SPEED     = 196;
      SPEED_MAX = 224;
      M_D = 110;
      sppeed_m = 280;
      speed_cut = 10;
      Rzhi_Count = 13;
      break; 
   
    case 6:
      SPEED_MIN = 174; 
      SPEED     = 203;
      SPEED_MAX = 231;
      sppeed_m = 290;
      speed_cut = 10;
      M_D = 115;
      Rzhi_Count = 12;
      break;
    case 7:
      SPEED_MIN = 180; 
      SPEED     = 210;
      SPEED_MAX = 238;
      M_D = 120;
      speed_cut = 10;
      sppeed_m = 290;
      Rzhi_Count = 11;
      break;               
  }
}
void Tiaoshi_Speed(void) {        //���뿪��3ѡ������ٶ�
  if (PORTA_PA0 == 0) {  //����
     SPEED_MIN = 132; 
     SPEED     = 132;
     SPEED_MAX = 132;
     sppeed_m = 0;
     speed_cut = 10;
     M_D = 70;
     Rzhi_Count = 22;
  } else{               //��ֹ
    SPEED_MIN = 0; 
    SPEED     = 0;
    SPEED_MAX = 0;
    sppeed_m = 0;
    speed_cut = 10;
    Rzhi_Count = 22;
    M_D = 70;
    Flag_Jing = 1;
  }
}

void  Choose_Send(void)               //ѡ�����ݷ���ģʽ
{
  if ((PORTA_PA1==0) && (PORTA_PA2==0)) { //���뿪��4.5ѡ��������ģʽ
     Flag_SMsg = 1;
  } else if (PORTA_PA1 == 0) {
    Flag_SImg = 1;
  } else if(PORTA_PA2 == 0){
    Flag_SImg2 = 1;
  }
}

unsigned int  TLY_Out(void)          //��ȡ�����ǵ�ADֵ
{
  return AD_Measure12(2);
}

void Podao()                                //�µ��жϺ���
{
  static unsigned char i = 0; 
   
  t_value[i] = TLY_Out();
  
  i++;
  if (i == 5) {
    i = 0;
  }
  
  TLY_I = t_value[0]+t_value[1]+t_value[2]+t_value[3]+t_value[4];
  
  if (Podao_Count == 0) 
  {     
     if (TLY_I > T_VALUE_Max) {        
       Flag_Podao = 1;
       Podao_Count = 1;
     }
  }else if (Podao_Count == 1){
     Podao_Time ++;
    if (Podao_Time == podao_t) {
      Podao_Count = 2;
      Podao_Time = 0;
    }
  } 
  else if (Podao_Count == 2) {
    if ((wide_now>(WIDE+10)) && (Lloss_Flag==0) && (Rloss_Flag==0)) {        
       Podao_Count = 3;
       Flag_Podao = 0;
     }
  }
  if (Podao_Count == 3){
    LED |= 0XFE;  
    Podao_Time ++;
   
    if (Podao_Time > 160) {
      Podao_Time = 0;
      Podao_Count = 0;
    }
 }else{
    LED &= 0X01;
 }
}

void Qipaoxian()                            //�����߼�⺯��
{
  if (Flag_Qipao == 0){    
    if (HONGWAI1) {
      Flag_Qipao1 = 1;
      Flag_Qipao = 1;
    } else if (HONGWAI2){
      Flag_Qipao2 = 1;
      Flag_Qipao = 1;
    }
  }
  if (Flag_Qipao==1 && Flag_Qipao1==1) {
    
    Hongwai_Time ++;
    
    
    if (Hongwai_Time<HONGWAI_TIME && HONGWAI2) {
      Flag_Qipao = 2;
      Hongwai_Time = 0;
    }
    
    if (Hongwai_Time >= HONGWAI_TIME) {
      Flag_Qipao = 0;
      Hongwai_Time = 0;
      Flag_Qipao1 = 0;
    }
  } else if (Flag_Qipao==1 && Flag_Qipao2==1) {
    
    Hongwai_Time ++;
    
    if (Hongwai_Time<HONGWAI_TIME && HONGWAI1) {
      Flag_Qipao = 2;
      Hongwai_Time = 0;
    }
    
    if (Hongwai_Time >= HONGWAI_TIME) {
      Flag_Qipao = 0;
      Hongwai_Time = 0;
      Flag_Qipao2 = 0;
    }
  }
  
  if (Flag_Qipao == 2) {
    if ((!HONGWAI1) && (!HONGWAI2)){
      Flag_Qipao = 3;
    }
  }
  if (Flag_Qipao == 3) {
    if (HONGWAI1) {
      Flag_Qipao1 = 2;
      Flag_Qipao = 4;
    } else if (HONGWAI2){
      Flag_Qipao2 = 2;
      Flag_Qipao = 4;
    }
  }
  if (Flag_Qipao==4 && Flag_Qipao1==2) {
    
    Hongwai_Time ++;
    
    if (Hongwai_Time<HONGWAI_TIME && HONGWAI2) {
      Flag_Qipao = 5;
      Hongwai_Time = 0;
    }
    
    if (Hongwai_Time >= HONGWAI_TIME) {
      Flag_Qipao = 3;
      Hongwai_Time = 0;
      Flag_Qipao1 = 1;
    }
  } else if (Flag_Qipao==4 && Flag_Qipao2==2) {
    
    Hongwai_Time ++;
    
    if (Hongwai_Time<HONGWAI_TIME && HONGWAI1) {
      Flag_Qipao = 5;
      Hongwai_Time = 0;
    }
    
    if (Hongwai_Time >= HONGWAI_TIME) {
      Flag_Qipao = 3;
      Hongwai_Time = 0;
      Flag_Qipao2 = 1;
    }
  }
  
  if (Flag_Qipao == 5) {
  
    Flag_Stop = 1;
  }
}

void Choose_Po() {
  POKG_DDR = 0;
  POKG_DDR2 = 0;
  
  if (POKG && POKG2) {
    Po_Swich = 1;
    T_VALUE_Max = 11000;
  }else if(POKG2 && (POKG == 0)){
    Po_Swich = 1;
    T_VALUE_Max = 12000;
  }else if(POKG && (POKG2 == 0)){
    Po_Swich = 1;
    T_VALUE_Max = 10000;
  }else{
    Po_Swich = 0;
    T_VALUE_Max = 11000;
  }
}