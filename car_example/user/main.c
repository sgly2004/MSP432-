#include "headfile.h"

int main()
{
	SysTick_Init();
	OLED_Init();
	
	motor_init();
	encoder_init();
	
	pid_init(&motorA, DELTA_PID, 10, 10, 5);
	pid_init(&motorB, DELTA_PID, 10, 10, 5);

	tim_interrupt_ms_init(TIMA_2,10);

	while(1)
	{
		
	}

}
