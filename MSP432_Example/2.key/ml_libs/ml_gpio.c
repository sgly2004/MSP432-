#include "headfile.h"

DIO_PORT_Odd_Interruptable_Type *gpio_index1[5] = {P1,P3,P5,P7,P9};
DIO_PORT_Even_Interruptable_Type *gpio_index2[5] = {P2,P4,P6,P8,P10};


//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO初始化
// @param	  gpiox	  选择GPIO端口	
// @param	  pinx    选择引脚号
// @param	  mode    选择工作模式
// @return		void  
// Sample usage:		gpio_init(P_2,Pin_0,OUT); 		
//-------------------------------------------------------------------------------------------------------------------
void gpio_init(GPIOn_enum gpiox,Pinx_enum pinx,GPIO_Mode_enum mode)
{
	if(gpiox%2)
	{
		gpio_index1[(gpiox-1)/2]->SEL0 &= ~(1<<pinx);
		gpio_index1[(gpiox-1)/2]->SEL1 &= ~(1<<pinx);  //配置端口为通用IO口
		switch(mode)
		{
			case OUT:
			{
				gpio_index1[(gpiox-1)/2]->DIR |= 1<<pinx;    //配置端口为输出
				gpio_index1[(gpiox-1)/2]->OUT &= ~(1<<pinx); //默认输出低电平
				break;
			}
			case IN_UP:
			{
				gpio_index1[(gpiox-1)/2]->DIR &= ~(1<<pinx);  //配置端口为输入
				gpio_index1[(gpiox-1)/2]->REN |= 1<<pinx; //使能上拉/下拉电阻
				gpio_index1[(gpiox-1)/2]->OUT |= 1<<pinx; //上拉输入
				break;
			}
			case IN_DOWN:
			{
				gpio_index1[(gpiox-1)/2]->DIR &= ~(1<<pinx);  //配置端口为输入
				gpio_index1[(gpiox-1)/2]->REN |= 1<<pinx; //使能上拉/下拉电阻
				gpio_index1[(gpiox-1)/2]->OUT &= ~(1<<pinx); //下拉输入
				break;
			}
		}
	}
	else
	{
		gpio_index2[gpiox/2-1]->SEL0 &= ~(1<<pinx);
		gpio_index2[gpiox/2-1]->SEL1 &= ~(1<<pinx);  //配置端口为通用IO口
		switch(mode)
		{
			case OUT:
			{
				gpio_index2[gpiox/2-1]->DIR |= 1<<pinx;    //配置端口为输出
				gpio_index2[gpiox/2-1]->OUT &= ~(1<<pinx); //默认输出低电平
				break;
			}
			case IN_UP:
			{
				gpio_index2[gpiox/2-1]->DIR &= ~(1<<pinx);  //配置端口为输入
				gpio_index2[gpiox/2-1]->REN |= 1<<pinx; //使能上拉/下拉电阻
				gpio_index2[gpiox/2-1]->OUT |= 1<<pinx; //上拉输入
				break;
			}
			case IN_DOWN:
			{
				gpio_index2[gpiox/2-1]->DIR &= ~(1<<pinx);  //配置端口为输入
				gpio_index2[gpiox/2-1]->REN |= 1<<pinx; //使能上拉/下拉电阻
				gpio_index2[gpiox/2-1]->OUT &= ~(1<<pinx); //下拉输入
				break;
			}
		}		
	}
	

}

//-------------------------------------------------------------------------------------------------------------------
// @brief	  设置GPIO电平
// @param	  gpiox	  选择GPIO端口	
// @param	  pinx    选择引脚号
// @param	  state   设置引脚电平(0/1)
// @return		void  
// Sample usage:		gpio_set(P_2,Pin_0,1);
//-------------------------------------------------------------------------------------------------------------------
void gpio_set(GPIOn_enum gpiox,Pinx_enum pinx,uint8_t state)
{
	if(gpiox%2)
	{
		if(state)
			gpio_index1[(gpiox-1)/2]->OUT |= 1<<pinx;
		else
			gpio_index1[(gpiox-1)/2]->OUT &= ~(1<<pinx);		
	}
	else
	{
		if(state)
			gpio_index2[gpiox/2-1]->OUT |= 1<<pinx;
		else
			gpio_index2[gpiox/2-1]->OUT &= ~(1<<pinx);			
	}

}

//-------------------------------------------------------------------------------------------------------------------
// @brief	  读取GPIO电平
// @param	  gpiox	  选择GPIO端口	
// @param	  pinx    选择引脚号
// @return	  引脚电平 
// Sample usage:		uint8_t state = gpio_get(P_2,Pin_0);
//-------------------------------------------------------------------------------------------------------------------
uint8_t gpio_get(GPIOn_enum gpiox,Pinx_enum pinx)
{
	uint8_t temp;
	if(gpiox%2)
		temp = gpio_index1[(gpiox-1)/2]->IN & (1<<pinx);
	else
		temp = gpio_index2[gpiox/2-1]->IN & (1<<pinx);
	
	if(temp!=0)	temp=1;
	
	return temp;
}
