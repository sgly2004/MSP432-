#include "headfile.h"

int main()
{
	SysTick_Init();
	OLED_Init();
	
	gpio_init(P_2,Pin_0,OUT); 	
	gpio_init(P_2,Pin_1,OUT); 	
	gpio_init(P_2,Pin_2,OUT); 	
	
	
	
	while(1)
	{
		gpio_set(P_2,Pin_0,1);
		delay_ms(500);
		gpio_set(P_2,Pin_0,0);
		delay_ms(500);
		
		gpio_set(P_2,Pin_1,1);
		delay_ms(500);
		gpio_set(P_2,Pin_1,0);
		delay_ms(500);
		
		gpio_set(P_2,Pin_2,1);
		delay_ms(500);
		gpio_set(P_2,Pin_2,0);
		delay_ms(500);
		
	}

}
