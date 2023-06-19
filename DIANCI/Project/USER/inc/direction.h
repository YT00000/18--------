#ifndef _DIRECTION_H
#define _DIRECTION_H


#include "zf__DMA.h"



extern float poserror;
extern uint16 DMA_ADC_dat[ADC_CH][(ADC_DATA-4)/2];   //将DMA中ADC数据高低位合并(每一个通道转换八次)
extern float average[ADC_CH];  //ADC每一个通道去掉最大小值的平均值
extern float normalization_result[ADC_CH];//平均值归一化


typedef struct
{
	 float SumError;						//误差累计	
	 float PrevError;					//Error[-2]	
	 float Direct_Parameter;		//曲线拟合后的偏差
	 float Pre1_Error[4];			//4次偏差缓存
	 float KP;  								//比例系数
	 float KI; 								//积分系数
	 float KD;									//微分系数
}DirectPidStruct;
void pooled_data(void);
void bubble_sort(void);
void average_value(void);
void normalization(void);
float my_sqrt(float number);
float my_pow(float x);
void prepare_dat(void);
void cal_poserror(float a_Ls,float a_La,float a_Lv,float a_Rs,float a_Ra,float a_Rv);
float fabs(float x);
void Direction_out(void);
void Steering_Angl(int angl);


#endif


