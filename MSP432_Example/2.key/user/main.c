#include "headfile.h"

int main()
{
	SysTick_Init();
	OLED_Init();

	gpio_init(P_1,Pin_1,IN_UP);
	gpio_init(P_2,Pin_0,OUT); 	
	
	while(1)
	{
		if(gpio_get(P_1,Pin_1) == 0)
		{
			delay_ms(20);
			while(gpio_get(P_1,Pin_1) == 0);
			delay_ms(20);

			gpio_set(P_2,Pin_0,1);
		}
	}

}
