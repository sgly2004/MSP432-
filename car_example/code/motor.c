#include "headfile.h"

uint8_t motorA_dir=1;   //1为正转 0为反转
uint8_t motorB_dir=1;

int Encoder_count1 = 0;
int Encoder_count2 = 0;

void motor_init()    //初始化
{
		pwm_init(TIMA_0,PWM_Channel_2,1000);	
		gpio_init(P_3,Pin_0,OUT);
		gpio_init(P_5,Pin_7,OUT);
	
		pwm_init(TIMA_0,PWM_Channel_3,1000);	
		gpio_init(P_6,Pin_1,OUT);
		gpio_init(P_4,Pin_0,OUT);
}

void motorA_duty(int duty)
{
		pwm_update(TIMA_0,PWM_Channel_2,duty);	
		gpio_set(P_3,Pin_0,motorA_dir);
		gpio_set(P_5,Pin_7,!motorA_dir);
}

void motorB_duty(int duty)
{
		pwm_update(TIMA_0,PWM_Channel_3,duty);	
		gpio_set(P_6,Pin_1,motorB_dir);
		gpio_set(P_4,Pin_0,!motorB_dir);
}

void encoder_init()
{
		exti_init(P_5,Pin_2,FALLING);
		gpio_init(P_3,Pin_6,IN_UP);
		exti_init(P_3,Pin_5,FALLING);
		gpio_init(P_3,Pin_7,IN_UP);
}
	
	
