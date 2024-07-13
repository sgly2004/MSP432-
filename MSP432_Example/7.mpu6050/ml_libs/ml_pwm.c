#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief		PWM引脚初始化
// @param	  timn	  选择定时器	
// @param	  ccrn    选择PWM通道
// @return		void  
// Sample usage:		pwm_pin_init(TIMA_0,PWM_Channel_3);		 内部调用 无需关心
//-------------------------------------------------------------------------------------------------------------------
void pwm_pin_init(TIMAn_enum timn,CCRn_enum ccrn)
{
	if(timn == TIMA_0)
	{
		switch(ccrn)
		{
			case PWM_Channel_1:{gpio_init(P_2,Pin_4,OUT);P2->SEL0 |= 1<<4;P2->SEL1 &= ~(1<<4);break;}
			case PWM_Channel_2:{gpio_init(P_2,Pin_5,OUT);P2->SEL0 |= 1<<5;P2->SEL1 &= ~(1<<5);break;}
			case PWM_Channel_3:{gpio_init(P_2,Pin_6,OUT);P2->SEL0 |= 1<<6;P2->SEL1 &= ~(1<<6);break;}
			case PWM_Channel_4:{gpio_init(P_2,Pin_7,OUT);P2->SEL0 |= 1<<7;P2->SEL1 &= ~(1<<7);break;}
		}
	}
	if(timn == TIMA_1)
	{
		switch(ccrn)
		{
			case PWM_Channel_1:{gpio_init(P_7,Pin_7,OUT);P7->SEL0 |= 1<<7;P7->SEL1 &= ~(1<<7);break;}
			case PWM_Channel_2:{gpio_init(P_7,Pin_6,OUT);P7->SEL0 |= 1<<6;P7->SEL1 &= ~(1<<6);break;}
			case PWM_Channel_3:{gpio_init(P_7,Pin_5,OUT);P7->SEL0 |= 1<<5;P7->SEL1 &= ~(1<<5);break;}
			case PWM_Channel_4:{gpio_init(P_7,Pin_4,OUT);P7->SEL0 |= 1<<4;P7->SEL1 &= ~(1<<4);break;}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		PWM初始化
// @param	  timn	  选择定时器	
// @param	  ccrn    选择PWM通道
// @param	  fre     定义频率（频率至少要大于15,即 fre>15）
// @return		void  
// Sample usage:		pwm_init(TIMA_0,PWM_Channel_3,10000);		
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(TIMAn_enum timn,CCRn_enum ccrn,uint16_t fre)
{
	pwm_pin_init(timn,ccrn);   //引脚初始化
	
	tim_index[timn]->CTL |= 1<<9;  //选择SMCLK为时钟源
	tim_index[timn]->CTL |= 1<<2;  //清除计数值
	tim_index[timn]->CTL |= 1<<4;  //向上计数模式
	
	tim_index[timn]->CTL |= 3<<6;  //8分频
	tim_index[timn]->EX0 |= 0x05;  //6分频 预分频值PSC=8*6=48
	
	tim_index[timn]->CCTL[0] = 0x80; // Toggle
	tim_index[timn]->CCR[0] = 1000000/fre-1; //自动重装载值ARR
	
	tim_index[timn]->CCTL[ccrn+1] = 0xc0;  // Toggle/set:向上计数模式下 CCR<ARR时 输出高电平
	
	tim_index[timn]->CCR[ccrn+1] = 0;   //默认占空比设置为0

}

//-------------------------------------------------------------------------------------------------------------------
// @brief		PWM占空比更新
// @param	  timn	  选择定时器	
// @param	  ccrn    选择PWM通道
// @param	  duty     定义功率(反映占空比)  duty取值范围0~MAX_DUTY 对应占空比=duty/MAX_DUTY*100%
// @return		void  
// Sample usage:		pwm_update(TIMA_0,PWM_Channel_3,10000);		 
//-------------------------------------------------------------------------------------------------------------------
void pwm_update(TIMAn_enum timn,CCRn_enum ccrn,uint16_t duty)
{
	if(duty>=MAX_DUTY)
		duty=MAX_DUTY;
	uint16_t temp = tim_index[timn]->CCR[0];   //读取ARR
	tim_index[timn]->CCR[ccrn+1] = (uint16_t)((float)duty/MAX_DUTY*(temp+1)); 
}

