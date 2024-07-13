#include "headfile.h"

EUSCI_A_Type *uart_index[4] = {EUSCI_A0,EUSCI_A1,EUSCI_A2,EUSCI_A3};

//-------------------------------------------------------------------------------------------------------------------
//���´�����Ӻ� ����ʹ��printf���� ��Ҫ��ʼ������UART_0
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc����
//printf�������ָ��fputc����fputc���������
//����ʹ�ô���1(USART1)���printf��Ϣ
int fputc(int ch, FILE *f)
{
	while((EUSCI_A0->IFG & (1<<1)) == 0);  // �ȴ����ڷ��ͽ���
	EUSCI_A0->TXBUF = (uint8_t) ch;  
	return ch;
}
#endif 
//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
// @brief		�������ų�ʼ��
// @param	  uart	  ѡ�񴮿�	
// @return		void  
// Sample usage:		uart_pin_init(UART_0);  �ú���Ϊ�ڲ����� �������
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
// @brief		���ڲ���������
// @param	  uart	  ѡ�񴮿�	
// @param	  baud	  ѡ������
// @return		void  
// Sample usage:		baud_set(UART_0,115200);  �ú���Ϊ�ڲ����� �������
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
// @brief		���ڳ�ʼ��
// @param	  uart	  ѡ�񴮿�	
// @param	  baud	  ѡ������ (��ѡ������:4800/9600/115200/256000)
// @return		void  
// Sample usage:		uart_init(UART_0,115200);  
//-------------------------------------------------------------------------------------------------------------------
void uart_init(UART_enum uart,int baud)
{

	uart_pin_init(uart);   //UART���ų�ʼ��
	
	uart_index[uart]->CTLW0 |= 1<<0; //���ڸ�λ
	uart_index[uart]->CTLW0 |= 1<<7; //ѡ��SMCLKΪʱ��Դ
	
	baud_set(uart,baud);     //���ò�����

	uart_index[uart]->CTLW0 &= ~1;   //����ʹ��
	uart_index[uart]->IE |= 1<<0;    //�����ж�ʹ��
	
	Interrupt_enableInterrupt(32+uart);  //ʹ���ж�
	Interrupt_enableMaster();      //ʹ�����ж�
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		���ڷ����ֽ�
// @param	  uart	  ѡ�񴮿�	
// @param	  byte	  �����ֽ�
// @return		void  
// Sample usage:		uart_sendbyte(UART_0,0x01);  
//-------------------------------------------------------------------------------------------------------------------
void uart_sendbyte(UART_enum uart,uint8_t byte)
{
	while((uart_index[uart]->IFG & (1<<1)) == 0);  // �ȴ����ڷ��ͽ���
	uart_index[uart]->TXBUF = byte;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		���ڷ����ַ���
// @param	  uart	  ѡ�񴮿�	
// @param	  byte	  �����ַ���
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
// @brief		���ڽ����ֽ�
// @param	  uart	  ѡ�񴮿�	
// @return		uint8_t  
// Sample usage:		uint8_t data = uart_getbyte(UART_0);  
//-------------------------------------------------------------------------------------------------------------------
uint8_t uart_getbyte(UART_enum uart)
{
	return uart_index[uart]->RXBUF;
}
