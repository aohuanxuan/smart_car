
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


unsigned char PixelAverage(); //��������ƽ��ֵ
void StartIntegration(void);//��ʼ�ع�
void StartIntegration2(void);//��ʼ�ع�
void ImageCapture(unsigned char * ImageData);//�ɼ�ͼ��
void ImageCapture2(unsigned char * ImageData);//�ɼ�ͼ��
void CCD_IO_Init(void);//CCD IO�ڳ�ʼ��
void CCD2_IO_Init(void);//CCD IO�ڳ�ʼ��
void CCD_Process(void);//�ܵ�ʶ��
void CCD2_Process(void);
void Image_Process(void);//ͼ����
void Array_Init(void);//�������
void Change_CCDTIME(void);




#endif /* #ifndef CCD_H_ */
