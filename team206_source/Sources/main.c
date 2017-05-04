

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
    
    Switchs_Init();                       //���뿪�س�ʼ��
    
    Choose(); 
    
    FMQ_Init();
    
    LED = 0X01;                             //��LED
    
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
    unsigned int Time_Run = 0;    //����״̬�³��ܵ�ʱ��
    int message = 0;              //���͵�����
    
    Init_All();                   //��ʼ��
    FMQ = 1;                      //������ʱ
    Delay_Start(500);
    FMQ = 0;
    Delay_Start(1666);
    
    PG_Time = CCDTIME;
    if (CCDTIME == 8) {        //�ع�ʱ��Ϊ8,�ʼ���ع�һ��
      StartIntegration();
      StartIntegration2();
    }
    
    EnableInterrupts;             //���ж�

    for(;;) {

        if(TimerFlag10ms == 1) {     
            TimerFlag10ms = 0;
            
            if (Flag_Tiaoshi){          //��ʱͣ�������Ե�ʱ����
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
        
        if ((!Flag_Podao) && (!Lren_Flag) && (!Rren_Flag) && (Podao_Count==0)){         //�����µ�������״̬�¼��������
          Qipaoxian();   //�����߼��
        }
        
        if (!Flag_Tiaoshi){
          
          if (Lren_Flag || Rren_Flag || Flag_Zhangai || Flag_Podao){ //��������Ԫ�ر���
                FMQ = 1;
              } else{
                FMQ = 0;
              }
        }
            
        if (Flag_Jing && Renzi_Mode)
        {
           if (average < 210) { //����̫������
              FMQ = 1;
           }else{
              FMQ = 0;
           }
         }
         if (Flag_Jing && (!S_Mode)){
           if (average > 250) { //����̫������
               FMQ = 1;
           }else{
               FMQ = 0;
           }
         }
    }

}