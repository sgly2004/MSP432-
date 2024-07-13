#ifndef _ml_pwm_h
#define _ml_pwm_h
#include "headfile.h"

#define MAX_DUTY 50000

typedef enum
{
	PWM_Channel_1,
	PWM_Channel_2,
	PWM_Channel_3,
	PWM_Channel_4,
}CCRn_enum;
/*
	TIMA_0 PWM_Channel_1 -> P2.4
	TIMA_0 PWM_Channel_2 -> P2.5
	TIMA_0 PWM_Channel_3 -> P2.6
	TIMA_0 PWM_Channel_4 -> P2.7

	TIMA_1 PWM_Channel_1 -> P7.7
	TIMA_1 PWM_Channel_2 -> P7.6
	TIMA_1 PWM_Channel_3 -> P7.5
	TIMA_1 PWM_Channel_4 -> P7.4
*/

void pwm_pin_init(TIMAn_enum timn,CCRn_enum ccrn);
void pwm_init(TIMAn_enum timn,CCRn_enum ccrn,uint16_t fre);
void pwm_update(TIMAn_enum timn,CCRn_enum ccrn,uint16_t duty);
#endif
