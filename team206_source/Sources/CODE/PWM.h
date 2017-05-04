#ifndef PWM_H_
#define PWM_H_

void PWM_Init(void);
void Steer_Change(uint16_t pwm);
void Motor_Change(uint8_t pwm1, uint8_t pwm2);



#endif