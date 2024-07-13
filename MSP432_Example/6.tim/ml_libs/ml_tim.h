#ifndef _ml_tim_h
#define _ml_tim_h
#include "headfile.h"

typedef enum
{
	TIMA_0  =  0x00,
	TIMA_1  =  0x01,
	TIMA_2  =  0x02,
	TIMA_3  =  0x03,
	
}TIMAn_enum;

extern Timer_A_Type *tim_index[4];

void tim_interrupt_ms_init(TIMAn_enum timn,int timer);

#endif
