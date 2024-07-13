#include "headfile.h"

EUSCI_A_Type *uart_index[4] = {EUSCI_A0,EUSCI_A1,EUSCI_A2,EUSCI_A3};

//-------------------------------------------------------------------------------------------------------------------
//以下代码添加后 可以使用printf函数 需要初始化串口UART_0
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定向fputc函数
//printf的输出，指向fputc，由fputc输出到串口
//这里使用串口1(USART1)输出printf信息
int fputc(int ch, FILE *f)
{
	while((EUSCI_A0->IFG & (1<<1)) == 0);  // 等待串口发送结束
	EUSCI_A0->TXBUF = (uint8_t) ch;  
	return ch;
}
#endif 
//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
// @brief		串口引脚初始化
// @param	  uart	  选择串口	
// @return		void  
// Sample usage:		uart_pin_init(UART_0);  该函数为内部调用 无需关心
//-------------------------------------------------------------------------------------------------------------------
void uart_pin_init(UART_enum uart)
{
	switch(uart)
	{
		case UART_0:
		{
			gpio_init(P_1,Pin_2,IN_UP);
			gpio_init(P_1,Pin_3,OUT); 
			P1->SEL0 |= 1<<2;
			P1->SEL0 |= 1<<3;
			break;
		}
		case UART_1:
		{
			gpio_init(P_2,Pin_2,IN_UP);
			gpio_init(P_2,Pin_3,OUT); 
			P2->SEL0 |= 1<<2;
			P2->SEL0 |= 1<<3;
			break;
		}
		case UART_2:
		{
			gpio_init(P_3,Pin_2,IN_UP);
			gpio_init(P_3,Pin_3,OUT); 
			P3->SEL0 |= 1<<2;
			P3->SEL0 |= 1<<3;
			break;
		}
		case UART_3:
		{
			gpio_init(P_9,Pin_6,IN_UP);
			gpio_init(P_9,Pin_7,OUT); 
			P9->SEL0 |= 1<<6;
			P9->SEL0 |= 1<<7;
			break;
		}
	}

}

//-------------------------------------------------------------------------------------------------------------------
// @brief		串口波特率设置
// @param	  uart	  选择串口	
// @param	  baud	  选择波特率
// @return		void  
// Sample usage:		baud_set(UART_0,115200);  该函数为内部调用 无需关心
//-------------------------------------------------------------------------------------------------------------------
void baud_set(UART_enum uart,int baud)
{
	switch(baud)
	{
		case 4800:
		{
			uart_index[uart]->BRW = 625;
			uart_index[uart]->MCTLW = 0x0001;
			break;			
		}
		case 9600:
		{
			uart_index[uart]->BRW = 312;
			uart_index[uart]->MCTLW = 0x0081;
			break;
		}
		case 115200:
		{
			uart_index[uart]->BRW = 26;
			uart_index[uart]->MCTLW = 0xD601;
			break;
		}
		case 256000:
		{
			uart_index[uart]->BRW = 11;
			uart_index[uart]->MCTLW = 0xAAB1;
			break;			
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		串口初始化
// @param	  uart	  选择串口	
// @param	  baud	  选择波特率 (可选波特率:4800/9600/115200/256000)
// @return		void  
// Sample usage:		uart_init(UART_0,115200);  
//-------------------------------------------------------------------------------------------------------------------
void uart_init(UART_enum uart,int baud)
{

	uart_pin_init(uart);   //UART引脚初始化
	
	uart_index[uart]->CTLW0 |= 1<<0; //串口复位
	uart_index[uart]->CTLW0 |= 1<<7; //选择SMCLK为时钟源
	
	baud_set(uart,baud);     //设置波特率

	uart_index[uart]->CTLW0 &= ~1;   //串口使能
	uart_index[uart]->IE |= 1<<0;    //接收中断使能
	
	Interrupt_enableInterrupt(32+uart);  //使能中断
	Interrupt_enableMaster();      //使能总中断
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		串口发送字节
// @param	  uart	  选择串口	
// @param	  byte	  发送字节
// @return		void  
// Sample usage:		uart_sendbyte(UART_0,0x01);  
//-------------------------------------------------------------------------------------------------------------------
void uart_sendbyte(UART_enum uart,uint8_t byte)
{
	while((uart_index[uart]->IFG & (1<<1)) == 0);  // 等待串口发送结束
	uart_index[uart]->TXBUF = byte;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		串口发送字符串
// @param	  uart	  选择串口	
// @param	  byte	  发送字符串
// @return		void  
// Sample usage:		uart_sendstr(UART_0,"1234\r\n");  
//-------------------------------------------------------------------------------------------------------------------
void uart_sendstr(UART_enum uart, char* str)
{
	while(*str)
	{
		uart_sendbyte(uart, *str++);
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		串口接收字节
// @param	  uart	  选择串口	
// @return		uint8_t  
// Sample usage:		uint8_t data = uart_getbyte(UART_0);  
//-------------------------------------------------------------------------------------------------------------------
uint8_t uart_getbyte(UART_enum uart)
{
	return uart_index[uart]->RXBUF;
}
