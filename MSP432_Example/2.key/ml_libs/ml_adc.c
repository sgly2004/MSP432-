#include "headfile.h"

ADC_TypeDef ADC_14;

//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC引脚初始化
// @param	  chn	  选择ADC通道 查看ml_adc.h里的枚举类型
// @return		void  
// Sample usage:		adc_pin_init(ADC_CH0);	 内部调用,用户无需关心
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
// @brief		ADC启动转换
// @param	  chn	  选择ADC通道 查看ml_adc.h里的枚举类型
// @return		void  
// Sample usage:		adc_start(chn);  内部调用,用户无需关心
//-------------------------------------------------------------------------------------------------------------------
void adc_start(ADC_CHn_eunm chn)
{
	ADC14->CTL0 &= ~(1<<1);   	// 失能转换
	ADC14->MCTL[0] &= ~0x1f;    // 清除输入通道选择
	ADC14->MCTL[0] |= chn;      // 选择输入通道
	ADC14->CTL0 |= 1<<26;       // SHP 采样时间
	ADC14->CTL0 |= 1<<1;       	// 使能转换
	ADC14->CTL0 |= 1<<0;    	  // 开始转换
}


//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC转换值获取
// @param	  chn	  选择ADC通道 查看ml_adc.h里的枚举类型
// @return		void  
// Sample usage:		uint16_t va = adc_get(ADC_CH0);  最大值 2^14 - 1 = 16383
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
// @brief		ADC初始化
// @param	  chn	  选择ADC通道 查看ml_adc.h里的枚举类型
// @return		void  
// Sample usage:			adc_init(ADC_CH0);
//-------------------------------------------------------------------------------------------------------------------
void adc_init(ADC_CHn_eunm chn)
{
	ADC14->CTL0 |= 1<<4;  	 // 使能ADC核心
	ADC14->CTL0	|= 3<<19;  	 // 选择时钟源:MCLK
	ADC14->CTL0 |= 1<<30;  	 // 预分频:4分频  
	ADC14->CTL0 |= 1<<24;    // 分频:5分频    ----- 48MHZ / (4×5) = 2.4MHZ
	
	adc_pin_init(chn);    	 // 配置IO口为模拟输入模式

	ADC14->CTL1 &= ~(0x1f<<16);  	// 配置ADC存储器 MEM0
	ADC14->CTL0 &= ~(3<<17);     	// 配置转换模式:单通道 单次转换
	ADC14->IER0 |= 1<<0;   	      // 使能ADC中断
	
	Interrupt_enableInterrupt(INT_ADC14);  //使能中断
	Interrupt_enableMaster();              //使能总中断
}



