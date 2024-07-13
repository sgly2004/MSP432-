#include "headfile.h"

int main()
{
	SysTick_Init();
	OLED_Init();
	
	uart_init(UART_0,115200);  
	
	int x = 0;
	while(1)
	{
		printf("test:%d\r\n", x);
		x++;
		delay_ms(1000);
	}	

}
