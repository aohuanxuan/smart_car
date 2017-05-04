/*
  PWM�ײ���������
*/

#include "includes.h"

void PWM_Init(void) 
{
  PWME &= 0xF0;      //�ر�ͨ��
  PWMCTL_CON01 = 1;    //01�������������
  PWMCAE &= 0XF0;    //�����
  PWMPOL |= 0X0F;    //������ߵ�ƽ
  PWMCLK = 0X03;    //01ѡ��SAʱ��,23ѡ��B
  PWMPRCLK = 0X44;  //��Aʱ�ӽ���16��Ƶ,Bʱ�ӽ���16��Ƶ A=2.5M B=2.5M
  PWMSCLA = 2;     //SA=2.5M/(2*2)=625K 
      
  PWMPER01 = 2084;  // ����Ϊ 625K/2084=300HZ  ���
  PWMDTY01 = 920; //����м�ֵС����ת������ת ���ɶ��840��
       
  PWMPER2 = 250;  //  ����Ϊ 2.5M/250=10KHZ  
  PWMPER3 = 250;   
  PWMDTY2 = 0;     
  PWMDTY3 = 0;   
      
  PWME |= 0X0F;   //ͨ��ʹ��

}

void Steer_Change(uint16_t pwm) //�޸Ķ��PWM
{
  PWMDTY01 = pwm;
}

void Motor_Change(uint8_t pwm1, uint8_t pwm2)  //�޸ĵ��PWM
{
  PWMDTY2 = pwm1;
  PWMDTY3 = pwm2;
}