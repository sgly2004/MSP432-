#ifndef _ml_exti_h
#define _ml_exti_h
#include "headfile.h"


typedef enum
{
	RISING,       //上升沿触发
	FALLING,      //下降沿触发
}EXTI_MODE_enum;

void exti_init(GPIOn_enum gpiox,Pinx_enum pinx,EXTI_MODE_enum mode);
	

#endif

