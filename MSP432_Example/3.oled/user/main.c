#include "headfile.h"

int main()
{
	SysTick_Init();
	OLED_Init();
	
	float x = 1.5433;
	while(1)
	{
		OLED_ShowString(1, 1, "oled");
		OLED_ShowNum(2, 1, 1, 1);
		OLED_ShowFloat(3, 1, x, 1, 4);
	}

}
