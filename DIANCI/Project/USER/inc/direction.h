#ifndef _DIRECTION_H
#define _DIRECTION_H


#include "zf__DMA.h"
extern uint16 DMA_ADC_dat[ADC_CH][(ADC_DATA-4)/2];   //将DMA中ADC数据高低位合并(每一个通道转换八次)
extern float average[ADC_CH];  //ADC每一个通道去掉最大小值的平均值
extern float normalization_result[ADC_CH];//平均值归一化

void pooled_data(void);
void bubble_sort(void);
void average_value(void);
void normalization(void);
float my_sqrt(float number);
float my_pow(float x);
void prepare_dat(void);





#endif


