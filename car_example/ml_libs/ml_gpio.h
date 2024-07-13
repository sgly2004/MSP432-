#ifndef _gpio_h
#define _gpio_h
#include "headfile.h"

typedef enum
{
	P_1 = 0x01,
	P_2 = 0x02,
	P_3 = 0x03,
	P_4 = 0x04,
	P_5 = 0x05,
	P_6 = 0x06,
	P_7 = 0x07,
	P_8 = 0x08,
	P_9 = 0x09,
	P_10 = 0x0A,
}GPIOn_enum;

typedef enum
{
	Pin_0 = 0x00,
	Pin_1 = 0x01,
	Pin_2 = 0x02,
	Pin_3 = 0x03,
	Pin_4 = 0x04,
	Pin_5 = 0x05,
	Pin_6 = 0x06,
	Pin_7 = 0x07,
}Pinx_enum;

typedef enum
{
	OUT,
	IN_UP,
	IN_DOWN,
}GPIO_Mode_enum;

void gpio_init(GPIOn_enum gpiox,Pinx_enum pinx,GPIO_Mode_enum mode);
void gpio_set(GPIOn_enum gpiox,Pinx_enum pinx,uint8_t state);
uint8_t gpio_get(GPIOn_enum gpiox,Pinx_enum pinx);

extern DIO_PORT_Odd_Interruptable_Type *gpio_index1[5];
extern DIO_PORT_Even_Interruptable_Type *gpio_index2[5];
#endif
