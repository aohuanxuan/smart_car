
#ifndef CCD_H_
#define CCD_H_


/* TSL1401_CLK -- PORTA0 */
#define TSL1401_CLK_DDR     DDRE_DDRE3
#define TSL1401_CLK         PORTE_PE3

/* TSL1401_SI -- PORTA1 */
#define TSL1401_SI_DDR      DDRE_DDRE2
#define TSL1401_SI          PORTE_PE2

/* TSL1401_CLK -- PORTA0 */
#define TSL14012_CLK_DDR     DDRE_DDRE6
#define TSL14012_CLK         PORTE_PE6

/* TSL1401_SI -- PORTA1 */
#define TSL14012_SI_DDR      DDRE_DDRE5
#define TSL14012_SI          PORTE_PE5




/* CPU delay 1us at 40M bus clock */\
#define Cpu_Delay1us() \
    { __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
    }

/* CPU delay 200ns at 40M bus clock */\
#define Cpu_Delay200ns() \
    { __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
    }

#define SamplingDelay() \
    { Cpu_Delay200ns()\
    }


unsigned char PixelAverage(); //计算数组平均值
void StartIntegration(void);//开始曝光
void StartIntegration2(void);//开始曝光
void ImageCapture(unsigned char * ImageData);//采集图像
void ImageCapture2(unsigned char * ImageData);//采集图像
void CCD_IO_Init(void);//CCD IO口初始化
void CCD2_IO_Init(void);//CCD IO口初始化
void CCD_Process(void);//跑道识别
void CCD2_Process(void);
void Image_Process(void);//图像处理
void Array_Init(void);//清空数组
void Change_CCDTIME(void);




#endif /* #ifndef CCD_H_ */
