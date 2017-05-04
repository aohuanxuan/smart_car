

/* Including needed modules to compile this module/procedure */

/*********************************************************
                       ccd.c
                     CCD��غ���
********************************************************/

#include "includes.h"

#define MIN_AD 20                    //����ѹ��CCD��ͬ��Ҫ����)
#define MIN_AD2 20                    //����ѹ��CCD��ͬ��Ҫ���ģ�
#define MIN_VALUE 45                 //��������ֵ�����߲�ͬ��Ҫ�ʵ����ģ�
#define MIN_VALUE2 30                 //��������ֵ�����߲�ͬ��Ҫ�ʵ����ģ�
#define POINT1 4                      //�ж�������ʹ�õ��ĵ��� 


signed int Middle = 64;
unsigned char wide_real = WIDE;

signed int M_error_now = 0;           //ƫ��
signed int M_error_error = 0;         //ƫ��֮��
signed int Left_Line = 0;             //����
signed int Right_Line = 127;          //����

unsigned char Lren_Flag = 0;           //���ֱ�־
unsigned char Rren_Flag = 0;
unsigned char Renzi_Time = 0;          //����ʱ��

unsigned char Lloss_Flag = 0;          //��߁G�߱�־
unsigned char Rloss_Flag = 0;          //�ұ߁G�߱�־

unsigned char Flag_Zhangai = 0;        //�ϰ�
unsigned char Flag_Shizi = 0;          //ʮ��
unsigned char Flag_Zhi = 0;            //ֱ��
unsigned char Flag_S = 0;              //СS

unsigned char wide_now = 0;            //���ڵĿ��

unsigned char Left_Max = 18;           //ɨ������
unsigned char Right_Max = 110;         //ɨ���Ҽ���

unsigned char Zhi_Count = 0;           //ֱ������
unsigned char S_Count = 0;             //СS����

unsigned char Left_Count = 18;          //���ɨ���
unsigned char Right_Count = 110;        //�ұ�ɨ���

unsigned char average = 0;              //�ܵ�����ƽ��ֵ

unsigned char Fall_Count = 0;           //CCD2�½���

unsigned char PG_Time;                  //��̬�ع�ʱ��

unsigned char Rzhi_Count = 18;          //����ǰֱ������
unsigned char Ren_Delay = 0;
unsigned char RenD_Count = 0;


unsigned char PixelAverage() {          //�����ܵ�����ƽ��ֵ
  unsigned char i;
  unsigned int sum = 0;
  
  for(i=(Left_Count+1); i<Right_Count; i++) {
    sum = sum + Pixel[i];
  }
  return ((unsigned char)(sum/(Right_Count-Left_Count-1)));
}

void Array_Init(void)                   //�����ʼ����������飩
{
  unsigned char *pixel_pt, *pixel2_pt;
  unsigned char i;

  pixel_pt = Pixel;
  for(i=0; i<128+10; i++) {
      *pixel_pt++ = 0;
  }
  
  pixel2_pt = Pixel2;
  for(i=0; i<128+10; i++) {
      *pixel2_pt++ = 0;
  }
}

void StartIntegration(void) {           //��ʼ�ع�

    unsigned char i;

    TSL1401_SI = 1;         /* SI  = 1 */
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    TSL1401_SI = 0;         /* SI  = 0 */
    SamplingDelay();
    TSL1401_CLK = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        TSL1401_CLK = 1;    /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        TSL1401_CLK = 0;    /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 0;        /* CLK = 0 */
}

void StartIntegration2(void) {

    unsigned char i;

    TSL14012_SI = 1;         /* SI  = 1 */
    SamplingDelay();
    TSL14012_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    TSL14012_SI = 0;         /* SI  = 0 */
    SamplingDelay();
    TSL14012_CLK = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        TSL14012_CLK = 1;    /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        TSL14012_CLK = 0;    /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    TSL14012_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    TSL14012_CLK = 0;        /* CLK = 0 */
}

void ImageCapture(unsigned char * ImageData) {    //�ɼ�ͼ��

    unsigned char i;
    unsigned int  temp_int;

    TSL1401_SI = 1;         /* SI  = 1 */
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    TSL1401_SI = 0;         /* SI  = 0 */
    SamplingDelay();

    //Delay 20us for sample the first pixel
    
    for(i = 0; i < 25; i++) {                //����25����CCD��ͼ����ȥ�Ƚ�ƽ����
        Cpu_Delay1us();                      //�Ѹ�ֵ�Ĵ���߸�С�ﵽ�Լ�����Ľ����
    }  
      /*  SamplingDelay();
        SamplingDelay();*/

    //Sampling Pixel 1
    temp_int = AD_Measure12(0);
    *ImageData++ = (byte)(temp_int>>4);
    TSL1401_CLK = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        TSL1401_CLK = 1;    /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128
        temp_int = AD_Measure12(0);
        *ImageData++ = (byte)(temp_int>>4);
        TSL1401_CLK = 0;    /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 0;        /* CLK = 0 */
}

void ImageCapture2(unsigned char * ImageData) {

    unsigned char i;
    unsigned int  temp_int;

    TSL14012_SI = 1;         /* SI  = 1 */
    SamplingDelay();
    TSL14012_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    TSL14012_SI = 0;         /* SI  = 0 */
    SamplingDelay();

    //Delay 20us for sample the first pixel
    
    for(i = 0; i < 25; i++) {                //����25����CCD��ͼ����ȥ�Ƚ�ƽ����
        Cpu_Delay1us();                      //�Ѹ�ֵ�Ĵ���߸�С�ﵽ�Լ�����Ľ����
    }  
      /*  SamplingDelay();
        SamplingDelay();*/

    //Sampling Pixel 1
    temp_int = AD_Measure12(1);
    *ImageData++ = (byte)(temp_int>>4);
    TSL14012_CLK = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        TSL14012_CLK = 1;    /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128
        temp_int = AD_Measure12(1);
        *ImageData++ = (byte)(temp_int>>4);
        TSL14012_CLK = 0;    /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    TSL14012_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    TSL14012_CLK = 0;        /* CLK = 0 */
}


void CCD_IO_Init(void) {              //CCD��ʼ��
    TSL1401_CLK_DDR = 1;
    TSL1401_SI_DDR  = 1;
    TSL1401_CLK = 0;
    TSL1401_SI  = 0;
}

void CCD2_IO_Init(void) {
    TSL14012_CLK_DDR = 1;
    TSL14012_SI_DDR  = 1;
    TSL14012_CLK = 0;
    TSL14012_SI  = 0;
}

void Image_Process(void)              //ͼ����
{
  unsigned char i = 0;

  
  for (i = 0;i < 128;i ++){
    
    Pixel[i] = Pixel[i] - MIN_AD;                           //��ȥ����ѹ 
    Pixel2[i] = Pixel2[i] - MIN_AD2;                           //��ȥ����
  }
  
  for (i = 1;i < 127;i ++){
   
    Pixel[i] = (Pixel[i-1]+Pixel[i]+Pixel[i+1])/3;         //��ֵ�˲�  
    Pixel2[i] = (Pixel2[i-1]+Pixel2[i]+Pixel2[i+1])/3;
  } 
}

#define ZHANGAI_VALUE WIDE/2+24      //�ϰ�ʶ������ֵ     ���54   �ϰ�43

void CCD_Process(void)             //CCD���ߺ���
{
  signed int M_error_last = 0;
  signed int Last_Middle = 0;

  Last_Middle = Middle;
  M_error_last = M_error_now; 
  
  Right_Count = Middle;
  
  while(Pixel[Right_Count] - Pixel[Right_Count+POINT1] <  MIN_VALUE && Right_Count < Right_Max){Right_Count++;}
  
  
  Left_Count = Middle;
  
  while(Pixel[Left_Count] - Pixel[Left_Count-POINT1] < MIN_VALUE && Left_Count > Left_Max){Left_Count--;}
  
  
  wide_now = Right_Count - Left_Count + 12;
    
  
  if (Right_Count >= Right_Max && Left_Count > Left_Max)     //����                             //�ұ߁G���ж�
  {  
    Left_Line = Left_Count - 6;
      
    
    Right_Line = Left_Line + wide_real;
    
    if (Lren_Flag && (Renzi_Mode==0)) {                                      //�������ж�������ģʽ0��
      if (Lloss_Flag && Rloss_Flag) {
        Lren_Flag = 0;
      }
    }
    
    Rloss_Flag = 1;
    Lloss_Flag = 0;

    Left_Max = 18;
    Right_Max = 110;     
    
    Middle = Left_Count + WIDE/2;
  }
    
  else if (Left_Count <= Left_Max && Right_Count < Right_Max)                                     //��߁G���ж�
  {     
    Right_Line = Right_Count + 6;
    
      
    Left_Line = Right_Line - wide_real;
    
    if (Rren_Flag && (Renzi_Mode==0)) {                                        //�������ж�������ģʽ0��
      if (Lloss_Flag && Rloss_Flag) {
        Rren_Flag = 0;
      }
    }
    
    Lloss_Flag = 1;
    Rloss_Flag = 0;
           
    Middle = Right_Count - WIDE/2;
  }
  
  else if (Left_Count <= Left_Max && Right_Count >= Right_Max)         //������ȫ��
  {
    if ((M_error_now<40) && (M_error_now>-40)) {              //ʮ���ж�
      wide_real = WIDE + 12;                   //ʮ��ֱ��
      Right_Line = WIDE/2 + 70;
      Left_Line = 58 - WIDE/2;
      Flag_Shizi = 1;
    }

    Left_Max = 18;
    Right_Max = 110;
    Rloss_Flag = 1;
    Lloss_Flag = 1;  
  }
 
  else                                              //û�G��
  {
    Right_Line = Right_Count + 6;
    Left_Line = Left_Count - 6;
    
    Rloss_Flag = 0;
    Lloss_Flag = 0;
    wide_real = wide_now;               //�����������
    
    Left_Max = 18;
    Right_Max = 110;

    Flag_Shizi = 0;
    
    Middle = (Right_Count + Left_Count) / 2;  
  }
   
  M_error_now = Right_Line + Left_Line - 128;               //����ƫ����
  M_error_error = M_error_now - M_error_last;
  
  if ((M_error_now<25) && (M_error_now>-25)){           //ֱ������
    Zhi_Count ++;
    if (Zhi_Count>25) {
      Zhi_Count = 26;
    }
  }else{
    Zhi_Count = 0;
  }
  
  if (Middle>110) {                                 //��Ұ���ƣ���ֹ����
    Left_Max = 64;
    Middle = 110;   
  }
  if (Middle<18) {
    Right_Max = 64;
    Middle = 18;
  }
                                                                         //�µ�����ʶ��
  if (Flag_Podao && (Podao_Count<2)) {
    if ((Rloss_Flag||Lloss_Flag) || (M_error_now>16) || (M_error_now<-16)) {
      Middle = Last_Middle;
      M_error_now = M_error_last;
      M_error_error = 0;
    }
  }
  
  Pixel[Right_Count] = 0;
  Pixel[Left_Count] = 0;
  Pixel[Middle] = 0;
  
  if (!Flag_Shizi && !Flag_Podao && !Lren_Flag && !Rren_Flag){  //����ʮ�֡��µ������������  
    if ((Rloss_Flag==0) && (Lloss_Flag==0) && (wide_real<ZHANGAI_VALUE) && (M_error_now<30) && (M_error_now>-30)){         //�ϰ�ʶ��
      Flag_Zhangai = 1;
    } else{
      Flag_Zhangai = 0;
    }
  }
}

#define REN_MIN 36            //���ֵ�һ���½��س��ַ�Χ
#define REN_MAX 64
#define REN_WIDE WIDE+18    //�����������������ֵ
#define BLACK_WIDE 10          //�������������ֵ
#define REN_TIME   51         //������ʱʱ�䣨����ģʽ1��
#define ZHI_VALUE 22       //ֱ����СS�ж���ֵ

void CCD2_Process(void)                           //����ʶ����
{
  unsigned char Rise_Count = 0, Fall_Count2 = 0;
                                                                                                  
  Fall_Count = 127;
  while(Pixel2[Fall_Count] - Pixel2[Fall_Count-3] <  MIN_VALUE2 && Fall_Count > 20){Fall_Count--;} //Ѱ���½���
       
  if ((Fall_Count<ZHI_VALUE) && (M_error_now<25) && (M_error_now>-25) && (wide_real<(WIDE+18))) {   //ֱ���ж�
    Flag_Zhi = 1;  
  } else { 
    Flag_Zhi = 0;
  }            
                                                  
  if ((Fall_Count<ZHI_VALUE) && (M_error_now<60) && (M_error_now>-60)){     //СS�ж�
    Flag_S = 1;
    S_Count = Rzhi_Count + 3;
  }
  if (S_Count>0) {
    S_Count --;
    if (S_Count == 0) {
      Flag_S = 0;
    } 
  }
  
  if ((!Flag_Shizi) && (!Flag_Podao) && (Rren_Flag==0) && (Lren_Flag==0) && (Fall_Count>REN_MIN) && (Fall_Count<REN_MAX)) {       
    //����ʮ�ֲ����µ�������������£��½��ط�Χ����   
      Rise_Count = Fall_Count;
      while(Pixel2[Rise_Count-3] - Pixel2[Rise_Count] <  MIN_VALUE2 && Rise_Count > 20){Rise_Count--;}//Ѱ��������
      
      if (Rise_Count > 20)  //����������� 
      {
        Fall_Count2 = Rise_Count;
        while(Pixel2[Fall_Count2] - Pixel2[Fall_Count2-3] <  MIN_VALUE2 && Fall_Count2 > 20){Fall_Count2--;} //Ѱ���½���
        
        if (((Fall_Count-Rise_Count)<BLACK_WIDE) && ((Rise_Count-Fall_Count2)<=(Fall_Count-Rise_Count)))//������½����ҿ�Ⱥ��� 
        {     
          if ((Lloss_Flag==1) && (wide_now>REN_WIDE) && (Rloss_Flag==0) && (M_error_now<20) && (M_error_now>-20) && (Zhi_Count>Rzhi_Count)) {          //���СCCD�G��,�ҁG�߿�ȹ���
            Rren_Flag = 1;
          } else if ((Lloss_Flag==0) && (wide_now>REN_WIDE) && (Rloss_Flag==1) && (M_error_now<20) && (M_error_now>-20) && (Zhi_Count>Rzhi_Count)){
            Lren_Flag = 1;
          }
      }
      
    }
}

  if (Rren_Flag || Lren_Flag) {             //����������ƶ��е�
    if (Rren_Flag) {
      Middle = 18;
    } else if (Lren_Flag) {
      Middle = 110;
    }
    wide_real = WIDE + 12;                  //���ƿ��
    Renzi_Time ++;
    
    if (Renzi_Time == REN_TIME) {                 //��ʱ�����֣�����ģʽ1��
      Renzi_Time = 0;
      if (Renzi_Mode){  
        Rren_Flag = 0;
        Lren_Flag = 0;
      }
    }
  }
  
  if (Ren_Delay == 0){
    if (Rren_Flag || Lren_Flag){
      Ren_Delay = 1;
    }
  }
  if (Ren_Delay == 1){
    RenD_Count ++;
    if (RenD_Count > 150){
      Ren_Delay = 0;
      RenD_Count = 0;
    }
  }
  
  Pixel2[Fall_Count] = 0;
  Pixel2[Fall_Count2] = 0;
  Pixel2[Rise_Count] = 0;
}

void Change_CCDTIME(void){                       //��̬�ع�ʱ�䣨��Ǳ��BUG�����ã���
  
  average = PixelAverage();
  
  if (((!Lloss_Flag)||(!Rloss_Flag)) && (!Flag_Podao) && (!Rren_Flag) && (!Lren_Flag) ) {
    if (average > 250) {
      PG_Time--;  
    } else if (average < 210) {
      PG_Time++;
    }
  }
  
  if (PG_Time >= (CCDTIME+1)) {
    PG_Time = CCDTIME+1;
  }else if (PG_Time <= (CCDTIME-1)) {
    PG_Time = CCDTIME-1;
  }
  
  if (PG_Time > 8) {
    PG_Time = 8;
  }else if (PG_Time < 1) {
    PG_Time = 1;
  }
}