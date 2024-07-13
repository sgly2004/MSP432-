#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief	  ��ʼ���ⲿ�ж� 
// @param	  gpiox	  ѡ��GPIO�˿�	   ע��ֻ��P_1~P_6����ʹ���ⲿ�ж�
// @param	  pinx    ѡ�����ź�
// @param	  mode    ѡ��ģʽ �����ش���-RISING �½��ش���-FALLING
// @return		void  
// Sample usage:		exti_init(P_1,Pin_4,FALLING);
//-------------------------------------------------------------------------------------------------------------------
void exti_init(GPIOn_enum gpiox,Pinx_enum pinx,EXTI_MODE_enum mode)
{
	
	if(gpiox%2)
	{
		gpio_index1[(gpiox-1)/2]->SEL0 &= ~(1<<pinx);
		gpio_index1[(gpiox-1)/2]->SEL1 &= ~(1<<pinx);  //���ö˿�Ϊͨ��IO��

		gpio_index1[(gpiox-1)/2]->DIR &= ~(1<<pinx);  //���ö˿�Ϊ����
		gpio_index1[(gpiox-1)/2]->REN |= 1<<pinx; //ʹ������/��������
		
		if(mode==0x00)       //�����ش���
		{
			gpio_index1[(gpiox-1)/2]->OUT &= ~(1<<pinx); //��������
			gpio_index1[(gpiox-1)/2]->IES &= ~(1<<pinx); //����Ϊ�����ش�����ʽ
		}
		else if(mode==0x01)  //�½��ش���
		{
			gpio_index1[(gpiox-1)/2]->OUT |= 1<<pinx; //��������
			gpio_index1[(gpiox-1)/2]->IES |= 1<<pinx; //����Ϊ�½��ش�����ʽ
		}
		
		gpio_index1[(gpiox-1)/2]->IFG &= ~(1<<pinx);  //����жϱ�־λ
		gpio_index1[(gpiox-1)/2]->IE |= 1<<pinx;       //�˿��ж�ʹ��
		Interrupt_enableInterrupt(50+gpiox);  //ʹ���ж�
		Interrupt_enableMaster();      //ʹ�����ж�
	}
	else
	{
		gpio_index2[gpiox/2-1]->SEL0 &= ~(1<<pinx);
		gpio_index2[gpiox/2-1]->SEL1 &= ~(1<<pinx);  //���ö˿�Ϊͨ��IO��

		gpio_index2[gpiox/2-1]->DIR &= ~(1<<pinx);  //���ö˿�Ϊ����
		gpio_index2[gpiox/2-1]->REN |= 1<<pinx; //ʹ������/��������
		
		if(mode==0x00)       //�����ش���
		{
			gpio_index2[gpiox/2-1]->OUT &= ~(1<<pinx); //��������
			gpio_index2[gpiox/2-1]->IES &= ~(1<<pinx); //����Ϊ�����ش�����ʽ
		}
		else if(mode==0x01)  //�½��ش���
		{
			gpio_index2[gpiox/2-1]->OUT |= 1<<pinx; //��������
			gpio_index2[gpiox/2-1]->IES |= 1<<pinx; //����Ϊ�½��ش�����ʽ
		}
		
		gpio_index2[gpiox/2-1]->IFG &= ~(1<<pinx);  //����жϱ�־λ
		gpio_index2[gpiox/2-1]->IE |= 1<<pinx;       //�˿��ж�ʹ��
		Interrupt_enableInterrupt(50+gpiox);  //ʹ���ж�
		Interrupt_enableMaster();      //ʹ�����ж�
	}
	
}
