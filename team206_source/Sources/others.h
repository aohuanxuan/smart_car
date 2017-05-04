#ifndef OTHERS_H_
#define OTHERS_H_

#define LED_DDR             DDRB
#define LED                 PORTB

/* LED1 */
#define LED1                PORTB_PB0

/* LED2 */
#define LED2                PORTB_PB1

/* LED3 */
#define LED3                PORTB_PB2

/* LED4 */
#define LED4                PORTB_PB3

/* LED5 */
#define LED5                PORTB_PB4

/* LED6 */
#define LED6                PORTB_PB5

/* LED7 */
#define LED7                PORTB_PB6

/* LED8 */
#define LED8                PORTB_PB7

#define FMQ_DDR             DDRT_DDRT6
#define FMQ                 PTT_PTT6

#define HONGWAI1_DDR        DDRJ_DDRJ6
#define HONGWAI1            PTIJ_PTIJ6

#define HONGWAI2_DDR        DDRJ_DDRJ7
#define HONGWAI2            PTIJ_PTIJ7

#define SPEED1              PORTA_PA3
#define SPEED2              PORTA_PA4
#define SPEED3              PORTA_PA5

#define SEND1              PORTA_PA6
#define SEND2              PORTA_PA7

#define POKG_DDR           DDRS_DDRS2
#define POKG_DDR2          DDRS_DDRS3
#define POKG               PTS_PTS2
#define POKG2               PTS_PTS3    

void LED_Init(void);    //LED≥ı ºªØ
void Choose_CCDTIME(void);
void Switchs_Init(void);
void  Choose_Speed(void);
void  Choose_Send(void);
unsigned int  TLY_Out(void);
void FMQ_Init(void);
void Podao(void);
void Qipaoxian(void);
void Tiaoshi_Speed(void);
void Choose(void);
void Choose_Po(void);

#endif