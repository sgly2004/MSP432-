#include "headfile.h"

DIO_PORT_Odd_Interruptable_Type *gpio_index1[5] = {P1,P3,P5,P7,P9};
DIO_PORT_Even_Interruptable_Type *gpio_index2[5] = {P2,P4,P6,P8,P10};


//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO��ʼ��
// @param	  gpiox	  ѡ��GPIO�˿�	
// @param	  pinx    ѡ�����ź�
// @param	  mode    ѡ����ģʽ
// @return		void  
// Sample usage:		gpio_init(P_2,Pin_0,OUT); 		
//-------------------------------------------------------------------------------------------------------------------
void gpio_init(GPIOn_enum gpiox,Pinx_enum pinx,GPIO_Mode_enum mode)
{
	if(gpiox%2)
	{
		gpio_index1[(gpiox-1)/2]->SEL0 &= ~(1<<pinx);
		gpio_index1[(gpiox-1)/2]->SEL1 &= ~(1<<pinx);  //���ö˿�Ϊͨ��IO��
		switch(mode)
		{
			case OUT:
			{
				gpio_index1[(gpiox-1)/2]->DIR |= 1<<pinx;    //���ö˿�Ϊ���
				gpio_index1[(gpiox-1)/2]->OUT &= ~(1<<pinx); //Ĭ������͵�ƽ
				break;
			}
			case IN_UP:
			{
				gpio_index1[(gpiox-1)/2]->DIR &= ~(1<<pinx);  //���ö˿�Ϊ����
				gpio_index1[(gpiox-1)/2]->REN |= 1<<pinx; //ʹ������/��������
				gpio_index1[(gpiox-1)/2]->OUT |= 1<<pinx; //��������
				break;
			}
			case IN_DOWN:
			{
				gpio_index1[(gpiox-1)/2]->DIR &= ~(1<<pinx);  //���ö˿�Ϊ����
				gpio_index1[(gpiox-1)/2]->REN |= 1<<pinx; //ʹ������/��������
				gpio_index1[(gpiox-1)/2]->OUT &= ~(1<<pinx); //��������
				break;
			}
		}
	}
	else
	{
		gpio_index2[gpiox/2-1]->SEL0 &= ~(1<<pinx);
		gpio_index2[gpiox/2-1]->SEL1 &= ~(1<<pinx);  //���ö˿�Ϊͨ��IO��
		switch(mode)
		{
			case OUT:
			{
				gpio_index2[gpiox/2-1]->DIR |= 1<<pinx;    //���ö˿�Ϊ���
				gpio_index2[gpiox/2-1]->OUT &= ~(1<<pinx); //Ĭ������͵�ƽ
				break;
			}
			case IN_UP:
			{
				gpio_index2[gpiox/2-1]->DIR &= ~(1<<pinx);  //���ö˿�Ϊ����
				gpio_index2[gpiox/2-1]->REN |= 1<<pinx; //ʹ������/��������
				gpio_index2[gpiox/2-1]->OUT |= 1<<pinx; //��������
				break;
			}
			case IN_DOWN:
			{
				gpio_index2[gpiox/2-1]->DIR &= ~(1<<pinx);  //���ö˿�Ϊ����
				gpio_index2[gpiox/2-1]->REN |= 1<<pinx; //ʹ������/��������
				gpio_index2[gpiox/2-1]->OUT &= ~(1<<pinx); //��������
				break;
			}
		}		
	}
	

}

//-------------------------------------------------------------------------------------------------------------------
// @brief	  ����GPIO��ƽ
// @param	  gpiox	  ѡ��GPIO�˿�	
// @param	  pinx    ѡ�����ź�
// @param	  state   �������ŵ�ƽ(0/1)
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
// @brief	  ��ȡGPIO��ƽ
// @param	  gpiox	  ѡ��GPIO�˿�	
// @param	  pinx    ѡ�����ź�
// @return	  ���ŵ�ƽ 
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
