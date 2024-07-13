#include "headfile.h"

Timer_A_Type *tim_index[4] = {TIMER_A0,TIMER_A1,TIMER_A2,TIMER_A3};

//-------------------------------------------------------------------------------------------------------------------
// @brief	  ��ʼ����ʱ���ж� 
// @param	  timn	  ѡ��ʱ��	
// @param	  timer   �ж�ʱ����(��λms ��Ҫ����85ms)
// @return		void  
// Sample usage:		tim_interrupt_ms_init(TIMA_0,10);
//-------------------------------------------------------------------------------------------------------------------
void tim_interrupt_ms_init(TIMAn_enum timn,int timer)
{ 
  
	tim_index[timn]->CTL |= 1<<9;  //ѡ��SMCLKΪʱ��Դ
	tim_index[timn]->CTL |= 1<<2;  //�������ֵ
	
	tim_index[timn]->CTL |= 3<<6;  //8��Ƶ
	tim_index[timn]->EX0 |= 0x07;  //8��Ƶ Ԥ��ƵֵΪ8*8=64
	
	tim_index[timn]->CCR[0] = 750*timer-1; //�Զ���װ��ֵARR
	
	tim_index[timn]->CTL |= 1<<1;  //��ʱ���ж�ʹ��
	Interrupt_enableInterrupt(2*timn+25);  //ʹ���ж�
	tim_index[timn]->CTL |= 1<<4;  //����ʹ��(���ϼ���)
	Interrupt_enableMaster();      //ʹ���ж�
	
}


