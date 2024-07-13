#include "headfile.h"

int main()
{
	SysTick_Init();
	OLED_Init();

	tim_interrupt_ms_init(TIMA_0, 50);
	gpio_init(P_2,Pin_0,OUT); 	
	
	while(1)
	{

	}

}
