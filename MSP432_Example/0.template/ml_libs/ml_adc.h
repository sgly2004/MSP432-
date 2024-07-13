#ifndef _ml_adc_h
#define _ml_adc_h
#include "headfile.h"

typedef struct
{
	uint8_t conversion_end_flag;
	uint16_t value;
} ADC_TypeDef;//ADC14�ṹ�嶨�壬���ڱ���һЩ��־λ���ظ�ת��������

typedef enum{
  ADC_CH0,        //A0     P5.5
  ADC_CH1,        //A1     P5.4
  ADC_CH2,        //A2     P5.3
  ADC_CH3,        //A3     P5.2
  ADC_CH4,        //A4     P5.1
  ADC_CH5,        //A5     P5.0
  ADC_CH6,        //A6     P4.7
  ADC_CH7,        //A7     P4.6
  ADC_CH8,        //A8     P4.5
}ADC_CHn_eunm;//ADC14��ѡͨ���о�

void adc_init(ADC_CHn_eunm chn); 
void adc_start(ADC_CHn_eunm chn);
uint16_t adc_get(ADC_CHn_eunm chn);

extern ADC_TypeDef ADC_14;
#endif
