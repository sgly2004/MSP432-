#ifndef _ml_uart_h
#define _ml_uart_h
#include "headfile.h"

typedef enum
{
	UART_0,   //rx:1.2 tx:1.3
	UART_1,   //rx:2.2 tx:2.3
	UART_2,   //rx:3.2 tx:3.3
	UART_3,   //rx:9.6 tx:9.7
}UART_enum;

void uart_pin_init(UART_enum uart);
void baud_set(UART_enum uart,int baud);
void uart_init(UART_enum uart,int baud);
void uart_sendbyte(UART_enum uart,uint8_t byte);
void uart_sendstr(UART_enum uart, char* str);
uint8_t uart_getbyte(UART_enum uart);

#endif
