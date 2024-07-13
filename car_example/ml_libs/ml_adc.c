#include "headfile.h"

ADC_TypeDef ADC_14;

//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC���ų�ʼ��
// @param	  chn	  ѡ��ADCͨ�� �鿴ml_adc.h���ö������
// @return		void  
// Sample usage:		adc_pin_init(ADC_CH0);	 �ڲ�����,�û��������
//-------------------------------------------------------------------------------------------------------------------
void adc_pin_init(ADC_CHn_eunm chn)
{
	switch(chn)
	{
		case ADC_CH0:
		{
			P5->SEL0 |= 1<<5;
			P5->SEL1 |= 1<<5;
			break;
		}
		case ADC_CH1:
		{
			P5->SEL0 |= 1<<4;
			P5->SEL1 |= 1<<4;
			break;
		}
		case ADC_CH2:
		{
			P5->SEL0 |= 1<<3;
			P5->SEL1 |= 1<<3;
			break;
		}
		case ADC_CH3:
		{
			P5->SEL0 |= 1<<2;
			P5->SEL1 |= 1<<2;
			break;
		}
		case ADC_CH4:
		{
			P5->SEL0 |= 1<<1;
			P5->SEL1 |= 1<<1;
			break;
		}
		case ADC_CH5:
		{
			P5->SEL0 |= 1<<0;
			P5->SEL1 |= 1<<0;
			break;
		}
		case ADC_CH6:
		{
			P4->SEL0 |= 1<<7;
			P4->SEL1 |= 1<<7;
			break;
		}
		case ADC_CH7:
		{
			P4->SEL0 |= 1<<6;
			P4->SEL1 |= 1<<6;
			break;
		}
		case ADC_CH8:
		{
			P4->SEL0 |= 1<<5;
			P4->SEL1 |= 1<<5;
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC����ת��
// @param	  chn	  ѡ��ADCͨ�� �鿴ml_adc.h���ö������
// @return		void  
// Sample usage:		adc_start(chn);  �ڲ�����,�û��������
//-------------------------------------------------------------------------------------------------------------------
void adc_start(ADC_CHn_eunm chn)
{
	ADC14->CTL0 &= ~(1<<1);   	// ʧ��ת��
	ADC14->MCTL[0] &= ~0x1f;    // �������ͨ��ѡ��
	ADC14->MCTL[0] |= chn;      // ѡ������ͨ��
	ADC14->CTL0 |= 1<<26;       // SHP ����ʱ��
	ADC14->CTL0 |= 1<<1;       	// ʹ��ת��
	ADC14->CTL0 |= 1<<0;    	  // ��ʼת��
}


//-------------------------------------------------------------------------------------------------------------------
// @brief		ADCת��ֵ��ȡ
// @param	  chn	  ѡ��ADCͨ�� �鿴ml_adc.h���ö������
// @return		void  
// Sample usage:		uint16_t va = adc_get(ADC_CH0);  ���ֵ 2^14 - 1 = 16383
//-------------------------------------------------------------------------------------------------------------------
uint16_t adc_get(ADC_CHn_eunm chn)
{
	adc_start(chn);
	while(ADC_14.conversion_end_flag != 1);
	uint16_t adc_value = ADC_14.value;
	ADC_14.conversion_end_flag = 0;
	return adc_value;
}



//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC��ʼ��
// @param	  chn	  ѡ��ADCͨ�� �鿴ml_adc.h���ö������
// @return		void  
// Sample usage:			adc_init(ADC_CH0);
//-------------------------------------------------------------------------------------------------------------------
void adc_init(ADC_CHn_eunm chn)
{
	ADC14->CTL0 |= 1<<4;  	 // ʹ��ADC����
	ADC14->CTL0	|= 3<<19;  	 // ѡ��ʱ��Դ:MCLK
	ADC14->CTL0 |= 1<<30;  	 // Ԥ��Ƶ:4��Ƶ  
	ADC14->CTL0 |= 1<<24;    // ��Ƶ:5��Ƶ    ----- 48MHZ / (4��5) = 2.4MHZ
	
	adc_pin_init(chn);    	 // ����IO��Ϊģ������ģʽ

	ADC14->CTL1 &= ~(0x1f<<16);  	// ����ADC�洢�� MEM0
	ADC14->CTL0 &= ~(3<<17);     	// ����ת��ģʽ:��ͨ�� ����ת��
	ADC14->IER0 |= 1<<0;   	      // ʹ��ADC�ж�
	
	Interrupt_enableInterrupt(INT_ADC14);  //ʹ���ж�
	Interrupt_enableMaster();              //ʹ�����ж�
}



