#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief	  初始化外部中断 
// @param	  gpiox	  选择GPIO端口	   注意只有P_1~P_6可以使用外部中断
// @param	  pinx    选择引脚号
// @param	  mode    选择模式 上升沿触发-RISING 下降沿触发-FALLING
// @return		void  
// Sample usage:		exti_init(P_1,Pin_4,FALLING);
//-------------------------------------------------------------------------------------------------------------------
void exti_init(GPIOn_enum gpiox,Pinx_enum pinx,EXTI_MODE_enum mode)
{
	
	if(gpiox%2)
	{
		gpio_index1[(gpiox-1)/2]->SEL0 &= ~(1<<pinx);
		gpio_index1[(gpiox-1)/2]->SEL1 &= ~(1<<pinx);  //配置端口为通用IO口

		gpio_index1[(gpiox-1)/2]->DIR &= ~(1<<pinx);  //配置端口为输入
		gpio_index1[(gpiox-1)/2]->REN |= 1<<pinx; //使能上拉/下拉电阻
		
		if(mode==0x00)       //上升沿触发
		{
			gpio_index1[(gpiox-1)/2]->OUT &= ~(1<<pinx); //下拉输入
			gpio_index1[(gpiox-1)/2]->IES &= ~(1<<pinx); //配置为上升沿触发方式
		}
		else if(mode==0x01)  //下降沿触发
		{
			gpio_index1[(gpiox-1)/2]->OUT |= 1<<pinx; //上拉输入
			gpio_index1[(gpiox-1)/2]->IES |= 1<<pinx; //配置为下降沿触发方式
		}
		
		gpio_index1[(gpiox-1)/2]->IFG &= ~(1<<pinx);  //清除中断标志位
		gpio_index1[(gpiox-1)/2]->IE |= 1<<pinx;       //端口中断使能
		Interrupt_enableInterrupt(50+gpiox);  //使能中断
		Interrupt_enableMaster();      //使能总中断
	}
	else
	{
		gpio_index2[gpiox/2-1]->SEL0 &= ~(1<<pinx);
		gpio_index2[gpiox/2-1]->SEL1 &= ~(1<<pinx);  //配置端口为通用IO口

		gpio_index2[gpiox/2-1]->DIR &= ~(1<<pinx);  //配置端口为输入
		gpio_index2[gpiox/2-1]->REN |= 1<<pinx; //使能上拉/下拉电阻
		
		if(mode==0x00)       //上升沿触发
		{
			gpio_index2[gpiox/2-1]->OUT &= ~(1<<pinx); //下拉输入
			gpio_index2[gpiox/2-1]->IES &= ~(1<<pinx); //配置为上升沿触发方式
		}
		else if(mode==0x01)  //下降沿触发
		{
			gpio_index2[gpiox/2-1]->OUT |= 1<<pinx; //上拉输入
			gpio_index2[gpiox/2-1]->IES |= 1<<pinx; //配置为下降沿触发方式
		}
		
		gpio_index2[gpiox/2-1]->IFG &= ~(1<<pinx);  //清除中断标志位
		gpio_index2[gpiox/2-1]->IE |= 1<<pinx;       //端口中断使能
		Interrupt_enableInterrupt(50+gpiox);  //使能中断
		Interrupt_enableMaster();      //使能总中断
	}
	
}
