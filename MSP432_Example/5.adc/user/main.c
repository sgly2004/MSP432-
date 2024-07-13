#include "headfile.h"

int main()
{
	SysTick_Init();
	OLED_Init();

	adc_init(ADC_CH0);
	uart_init(UART_0,115200); 
	
	uint16_t va;
	while(1)
	{
		va = adc_get(ADC_CH0);
		printf("adc_value:%d\r\n", va);
	}

}
