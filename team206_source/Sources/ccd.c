

/* Including needed modules to compile this module/procedure */

/*********************************************************
                       ccd.c
                     CCD相关函数
********************************************************/

#include "includes.h"

#define MIN_AD 20                    //暗电压（CCD不同需要更改)
#define MIN_AD2 20                    //暗电压（CCD不同需要更改）
#define MIN_VALUE 45                 //跳边沿阈值（光线不同需要适当更改）
#define MIN_VALUE2 30                 //跳边沿阈值（光线不同需要适当更改）
#define POINT1 4                      //判断跳变沿使用到的点数 


signed int Middle = 64;
unsigned char wide_real = WIDE;

signed int M_error_now = 0;           //偏差
signed int M_error_error = 0;         //偏差之差
signed int Left_Line = 0;             //左线
signed int Right_Line = 127;          //右线

unsigned char Lren_Flag = 0;           //人字标志
unsigned char Rren_Flag = 0;
unsigned char Renzi_Time = 0;          //人字时间

unsigned char Lloss_Flag = 0;          //左边丟线标志
unsigned char Rloss_Flag = 0;          //右边丟线标志

unsigned char Flag_Zhangai = 0;        //障碍
unsigned char Flag_Shizi = 0;          //十字
unsigned char Flag_Zhi = 0;            //直道
unsigned char Flag_S = 0;              //小S

unsigned char wide_now = 0;            //现在的宽度

unsigned char Left_Max = 18;           //扫描左极限
unsigned char Right_Max = 110;         //扫描右极限

unsigned char Zhi_Count = 0;           //直道计数
unsigned char S_Count = 0;             //小S计数

unsigned char Left_Count = 18;          //左边扫描点
unsigned char Right_Count = 110;        //右边扫描点

unsigned char average = 0;              //跑道亮度平均值

unsigned char Fall_Count = 0;           //CCD2下降沿

unsigned char PG_Time;                  //动态曝光时间

unsigned char Rzhi_Count = 18;          //人字前直道计数
unsigned char Ren_Delay = 0;
unsigned char RenD_Count = 0;


unsigned char PixelAverage() {          //计算跑道亮度平均值
  unsigned char i;
  unsigned int sum = 0;
  
  for(i=(Left_Count+1); i<Right_Count; i++) {
    sum = sum + Pixel[i];
  }
  return ((unsigned char)(sum/(Right_Count-Left_Count-1)));
}

void Array_Init(void)                   //数组初始化（清空数组）
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

void StartIntegration(void) {           //开始曝光

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

void ImageCapture(unsigned char * ImageData) {    //采集图像

    unsigned char i;
    unsigned int  temp_int;

    TSL1401_SI = 1;         /* SI  = 1 */
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    TSL1401_SI = 0;         /* SI  = 0 */
    SamplingDelay();

    //Delay 20us for sample the first pixel
    
    for(i = 0; i < 25; i++) {                //更改25，让CCD的图像看上去比较平滑，
        Cpu_Delay1us();                      //把该值改大或者改小达到自己满意的结果。
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
    
    for(i = 0; i < 25; i++) {                //更改25，让CCD的图像看上去比较平滑，
        Cpu_Delay1us();                      //把该值改大或者改小达到自己满意的结果。
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


void CCD_IO_Init(void) {              //CCD初始化
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

void Image_Process(void)              //图像处理
{
  unsigned char i = 0;

  
  for (i = 0;i < 128;i ++){
    
    Pixel[i] = Pixel[i] - MIN_AD;                           //减去暗电压 
    Pixel2[i] = Pixel2[i] - MIN_AD2;                           //减去暗电
  }
  
  for (i = 1;i < 127;i ++){
   
    Pixel[i] = (Pixel[i-1]+Pixel[i]+Pixel[i+1])/3;         //均值滤波  
    Pixel2[i] = (Pixel2[i-1]+Pixel2[i]+Pixel2[i+1])/3;
  } 
}

#define ZHANGAI_VALUE WIDE/2+24      //障碍识别宽度阈值     宽度54   障碍43

void CCD_Process(void)             //CCD找线函数
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
    
  
  if (Right_Count >= Right_Max && Left_Count > Left_Max)     //补线                             //右边丟线判定
  {  
    Left_Line = Left_Count - 6;
      
    
    Right_Line = Left_Line + wide_real;
    
    if (Lren_Flag && (Renzi_Mode==0)) {                                      //出人字判定（人字模式0）
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
    
  else if (Left_Count <= Left_Max && Right_Count < Right_Max)                                     //左边丟线判定
  {     
    Right_Line = Right_Count + 6;
    
      
    Left_Line = Right_Line - wide_real;
    
    if (Rren_Flag && (Renzi_Mode==0)) {                                        //出人字判定（人字模式0）
      if (Lloss_Flag && Rloss_Flag) {
        Rren_Flag = 0;
      }
    }
    
    Lloss_Flag = 1;
    Rloss_Flag = 0;
           
    Middle = Right_Count - WIDE/2;
  }
  
  else if (Left_Count <= Left_Max && Right_Count >= Right_Max)         //两条线全丢
  {
    if ((M_error_now<40) && (M_error_now>-40)) {              //十字判定
      wide_real = WIDE + 12;                   //十字直走
      Right_Line = WIDE/2 + 70;
      Left_Line = 58 - WIDE/2;
      Flag_Shizi = 1;
    }

    Left_Max = 18;
    Right_Max = 110;
    Rloss_Flag = 1;
    Lloss_Flag = 1;  
  }
 
  else                                              //没丟线
  {
    Right_Line = Right_Count + 6;
    Left_Line = Left_Count - 6;
    
    Rloss_Flag = 0;
    Lloss_Flag = 0;
    wide_real = wide_now;               //更新赛道宽度
    
    Left_Max = 18;
    Right_Max = 110;

    Flag_Shizi = 0;
    
    Middle = (Right_Count + Left_Count) / 2;  
  }
   
  M_error_now = Right_Line + Left_Line - 128;               //计算偏移量
  M_error_error = M_error_now - M_error_last;
  
  if ((M_error_now<25) && (M_error_now>-25)){           //直道计数
    Zhi_Count ++;
    if (Zhi_Count>25) {
      Zhi_Count = 26;
    }
  }else{
    Zhi_Count = 0;
  }
  
  if (Middle>110) {                                 //视野限制，防止串道
    Left_Max = 64;
    Middle = 110;   
  }
  if (Middle<18) {
    Right_Max = 64;
    Middle = 18;
  }
                                                                         //坡道误判识别
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
  
  if (!Flag_Shizi && !Flag_Podao && !Lren_Flag && !Rren_Flag){  //不在十字、坡道、人字情况下  
    if ((Rloss_Flag==0) && (Lloss_Flag==0) && (wide_real<ZHANGAI_VALUE) && (M_error_now<30) && (M_error_now>-30)){         //障碍识别
      Flag_Zhangai = 1;
    } else{
      Flag_Zhangai = 0;
    }
  }
}

#define REN_MIN 36            //人字第一个下降沿出现范围
#define REN_MAX 64
#define REN_WIDE WIDE+18    //人字赛道宽度限制阈值
#define BLACK_WIDE 10          //黑条宽度限制阈值
#define REN_TIME   51         //人字延时时间（人字模式1）
#define ZHI_VALUE 22       //直道和小S判定阈值

void CCD2_Process(void)                           //人字识别函数
{
  unsigned char Rise_Count = 0, Fall_Count2 = 0;
                                                                                                  
  Fall_Count = 127;
  while(Pixel2[Fall_Count] - Pixel2[Fall_Count-3] <  MIN_VALUE2 && Fall_Count > 20){Fall_Count--;} //寻找下降沿
       
  if ((Fall_Count<ZHI_VALUE) && (M_error_now<25) && (M_error_now>-25) && (wide_real<(WIDE+18))) {   //直道判定
    Flag_Zhi = 1;  
  } else { 
    Flag_Zhi = 0;
  }            
                                                  
  if ((Fall_Count<ZHI_VALUE) && (M_error_now<60) && (M_error_now>-60)){     //小S判定
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
    //不是十字不是坡道不是人字情况下，下降沿范围符合   
      Rise_Count = Fall_Count;
      while(Pixel2[Rise_Count-3] - Pixel2[Rise_Count] <  MIN_VALUE2 && Rise_Count > 20){Rise_Count--;}//寻找上升沿
      
      if (Rise_Count > 20)  //如果有上升沿 
      {
        Fall_Count2 = Rise_Count;
        while(Pixel2[Fall_Count2] - Pixel2[Fall_Count2-3] <  MIN_VALUE2 && Fall_Count2 > 20){Fall_Count2--;} //寻找下降沿
        
        if (((Fall_Count-Rise_Count)<BLACK_WIDE) && ((Rise_Count-Fall_Count2)<=(Fall_Count-Rise_Count)))//如果有下降沿且宽度合适 
        {     
          if ((Lloss_Flag==1) && (wide_now>REN_WIDE) && (Rloss_Flag==0) && (M_error_now<20) && (M_error_now>-20) && (Zhi_Count>Rzhi_Count)) {          //如果小CCD丟线,且丟线宽度过大
            Rren_Flag = 1;
          } else if ((Lloss_Flag==0) && (wide_now>REN_WIDE) && (Rloss_Flag==1) && (M_error_now<20) && (M_error_now>-20) && (Zhi_Count>Rzhi_Count)){
            Lren_Flag = 1;
          }
      }
      
    }
}

  if (Rren_Flag || Lren_Flag) {             //人字情况下移动中点
    if (Rren_Flag) {
      Middle = 18;
    } else if (Lren_Flag) {
      Middle = 110;
    }
    wide_real = WIDE + 12;                  //限制宽度
    Renzi_Time ++;
    
    if (Renzi_Time == REN_TIME) {                 //延时出人字（人字模式1）
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

void Change_CCDTIME(void){                       //动态曝光时间（有潜在BUG，慎用！）
  
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