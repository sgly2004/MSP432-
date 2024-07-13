#include "headfile.h"

int main()
{
	SysTick_Init();
	OLED_Init();
	
	I2C_Init();
	MPU6050_Init();
	exti_init(P_6,Pin_4,RISING);
	uint8_t id = MPU6050_Read(WHO_AM_I);
	while(1)
	{
		
		OLED_ShowSignedNum(1,1,id,5);
		OLED_ShowSignedNum(2,1,gx,5);
		OLED_ShowSignedNum(3,1,gy,5);
		OLED_ShowSignedNum(4,1,gz,5);
	}

}
