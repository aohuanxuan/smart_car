

#include "includes.h"

/*
*********************************************************************************************************
* Description: Data
*********************************************************************************************************
*/
unsigned char Pixel[128];
unsigned char Pixel2[128];


/*
*********************************************************************************************************
* Description: main
*********************************************************************************************************
*/

void Delay_Start(unsigned int t) 
{
  unsigned int i,j;
  for (i=0; i<t; i++) {
    for (j=0; j<5000; j++);
  }
}

void Init_All() 
{
    SCI0_Init();

    PIT_Init();

    AD_Init();

    CCD_IO_Init();
    CCD2_IO_Init();
    
    LED_Init();
    
    PWM_Init();
    
    PT7_Init();
    
    Array_Init();
    
    Switchs_Init();                       //拨码开关初始化
    
    Choose(); 
    
    FMQ_Init();
    
    LED = 0X01;                             //打开LED
    
    podao_t = Rzhi_Count*5 - 10;
    if (podao_t > 90) {
      podao_t = 90;
    }else if(podao_t < 50){
      podao_t = 50;
    }

}

void main(void) {

    unsigned char send_data_cnt = 0;
    unsigned char i = 0;
    unsigned char Image[128];
    unsigned int Time_Run = 0;    //调试状态下车跑的时间
    int message = 0;              //发送的数据
    
    Init_All();                   //初始化
    FMQ = 1;                      //开机延时
    Delay_Start(500);
    FMQ = 0;
    Delay_Start(1666);
    
    PG_Time = CCDTIME;
    if (CCDTIME == 8) {        //曝光时间为8,最开始先曝光一次
      StartIntegration();
      StartIntegration2();
    }
    
    EnableInterrupts;             //开中断

    for(;;) {

        if(TimerFlag10ms == 1) {     
            TimerFlag10ms = 0;
            
            if (Flag_Tiaoshi){          //定时停车，调试的时候用
              Time_Run ++; 
              if (Time_Run >= 350) {
                 Time_Run = 0;
                 Flag_Stop = 1;
              }
            }
            
            if (Flag_SImg){  
              if(++send_data_cnt >= 10) {
                  send_data_cnt = 0;     
                  for (i=0; i<128; i++){
                    Image[i] = Pixel[i];
                  }   
                  SendImageData(Image);
              } 
            }
            
            if (Flag_SImg2){  
              if(++send_data_cnt >= 10) {
                  send_data_cnt = 0;     
                  for (i=0; i<128; i++){
                    Image[i] = Pixel2[i];
                  }   
                  SendImageData(Image);
              } 
            }
            
            if (Flag_SMsg){   
                  message = TLY_I/100;
                  SendMessage(message);   
            }
            
            LED1 = ~LED1;   
        }
        
        if ((!Flag_Podao) && (!Lren_Flag) && (!Rren_Flag) && (Podao_Count==0)){         //不是坡道、人字状态下检测起跑线
          Qipaoxian();   //起跑线检测
        }
        
        if (!Flag_Tiaoshi){
          
          if (Lren_Flag || Rren_Flag || Flag_Zhangai || Flag_Podao){ //所有特殊元素报警
                FMQ = 1;
              } else{
                FMQ = 0;
              }
        }
            
        if (Flag_Jing && Renzi_Mode)
        {
           if (average < 210) { //光线太暗报警
              FMQ = 1;
           }else{
              FMQ = 0;
           }
         }
         if (Flag_Jing && (!S_Mode)){
           if (average > 250) { //光线太亮报警
               FMQ = 1;
           }else{
               FMQ = 0;
           }
         }
    }

}