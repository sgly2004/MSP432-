#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief		PWM���ų�ʼ��
// @param	  timn	  ѡ��ʱ��	
// @param	  ccrn    ѡ��PWMͨ��
// @return		void  
// Sample usage:		pwm_pin_init(TIMA_0,PWM_Channel_3);		 �ڲ����� �������
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
// @brief		PWM��ʼ��
// @param	  timn	  ѡ��ʱ��	
// @param	  ccrn    ѡ��PWMͨ��
// @param	  fre     ����Ƶ�ʣ�Ƶ������Ҫ����15,�� fre>15��
// @return		void  
// Sample usage:		pwm_init(TIMA_0,PWM_Channel_3,10000);		
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(TIMAn_enum timn,CCRn_enum ccrn,uint16_t fre)
{
	pwm_pin_init(timn,ccrn);   //���ų�ʼ��
	
	tim_index[timn]->CTL |= 1<<9;  //ѡ��SMCLKΪʱ��Դ
	tim_index[timn]->CTL |= 1<<2;  //�������ֵ
	tim_index[timn]->CTL |= 1<<4;  //���ϼ���ģʽ
	
	tim_index[timn]->CTL |= 3<<6;  //8��Ƶ
	tim_index[timn]->EX0 |= 0x05;  //6��Ƶ Ԥ��ƵֵPSC=8*6=48
	
	tim_index[timn]->CCTL[0] = 0x80; // Toggle
	tim_index[timn]->CCR[0] = 1000000/fre-1; //�Զ���װ��ֵARR
	
	tim_index[timn]->CCTL[ccrn+1] = 0xc0;  // Toggle/set:���ϼ���ģʽ�� CCR<ARRʱ ����ߵ�ƽ
	
	tim_index[timn]->CCR[ccrn+1] = 0;   //Ĭ��ռ�ձ�����Ϊ0

}

//-------------------------------------------------------------------------------------------------------------------
// @brief		PWMռ�ձȸ���
// @param	  timn	  ѡ��ʱ��	
// @param	  ccrn    ѡ��PWMͨ��
// @param	  duty     ���幦��(��ӳռ�ձ�)  dutyȡֵ��Χ0~MAX_DUTY ��Ӧռ�ձ�=duty/MAX_DUTY*100%
// @return		void  
// Sample usage:		pwm_update(TIMA_0,PWM_Channel_3,10000);		 
//-------------------------------------------------------------------------------------------------------------------
void pwm_update(TIMAn_enum timn,CCRn_enum ccrn,uint16_t duty)
{
	if(duty>=MAX_DUTY)
		duty=MAX_DUTY;
	uint16_t temp = tim_index[timn]->CCR[0];   //��ȡARR
	tim_index[timn]->CCR[ccrn+1] = (uint16_t)((float)duty/MAX_DUTY*(temp+1)); 
}

