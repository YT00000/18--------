#ifndef _DIRECTION_H
#define _DIRECTION_H


#include "zf__DMA.h"
extern uint16 DMA_ADC_dat[ADC_CH][(ADC_DATA-4)/2];   //��DMA��ADC���ݸߵ�λ�ϲ�(ÿһ��ͨ��ת���˴�)
extern float average[ADC_CH];  //ADCÿһ��ͨ��ȥ�����Сֵ��ƽ��ֵ
extern float normalization_result[ADC_CH];//ƽ��ֵ��һ��

void pooled_data(void);
void bubble_sort(void);
void average_value(void);
void normalization(void);
float my_sqrt(float number);
float my_pow(float x);
void prepare_dat(void);





#endif


