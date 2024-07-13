#include "headfile.h"

Timer_A_Type *tim_index[4] = {TIMER_A0,TIMER_A1,TIMER_A2,TIMER_A3};

//-------------------------------------------------------------------------------------------------------------------
// @brief	  初始化定时器中断 
// @param	  timn	  选择定时器	
// @param	  timer   中断时间间隔(单位ms 不要超过85ms)
// @return		void  
// Sample usage:		tim_interrupt_ms_init(TIMA_0,10);
//-------------------------------------------------------------------------------------------------------------------
void tim_interrupt_ms_init(TIMAn_enum timn,int timer)
{ 
  
	tim_index[timn]->CTL |= 1<<9;  //选择SMCLK为时钟源
	tim_index[timn]->CTL |= 1<<2;  //清除计数值
	
	tim_index[timn]->CTL |= 3<<6;  //8分频
	tim_index[timn]->EX0 |= 0x07;  //8分频 预分频值为8*8=64
	
	tim_index[timn]->CCR[0] = 750*timer-1; //自动重装载值ARR
	
	tim_index[timn]->CTL |= 1<<1;  //定时器中断使能
	Interrupt_enableInterrupt(2*timn+25);  //使能中断
	tim_index[timn]->CTL |= 1<<4;  //计数使能(向上计数)
	Interrupt_enableMaster();      //使能中断
	
}


