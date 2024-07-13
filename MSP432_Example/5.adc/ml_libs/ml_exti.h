#ifndef _ml_exti_h
#define _ml_exti_h
#include "headfile.h"


typedef enum
{
	RISING,       //�����ش���
	FALLING,      //�½��ش���
}EXTI_MODE_enum;

void exti_init(GPIOn_enum gpiox,Pinx_enum pinx,EXTI_MODE_enum mode);
	

#endif

