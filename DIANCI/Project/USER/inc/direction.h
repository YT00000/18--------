#ifndef _DIRECTION_H
#define _DIRECTION_H


#include "zf__DMA.h"



extern float poserror;
extern uint16 DMA_ADC_dat[ADC_CH][(ADC_DATA-4)/2];   //��DMA��ADC���ݸߵ�λ�ϲ�(ÿһ��ͨ��ת���˴�)
extern float average[ADC_CH];  //ADCÿһ��ͨ��ȥ�����Сֵ��ƽ��ֵ
extern float normalization_result[ADC_CH];//ƽ��ֵ��һ��


typedef struct
{
	 float SumError;						//����ۼ�	
	 float PrevError;					//Error[-2]	
	 float Direct_Parameter;		//������Ϻ��ƫ��
	 float Pre1_Error[4];			//4��ƫ���
	 float KP;  								//����ϵ��
	 float KI; 								//����ϵ��
	 float KD;									//΢��ϵ��
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


