/*
 * @Author: lanchanghai
 * @Date: 2023-06-09 22:32:02
 * @LastEditors: lanchanghai
 * @LastEditTime: 2023-06-16 19:55:11
 * @FilePath: \DIANCI\Project\USER\src\adc.c
 */
#include "headfile.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC��ʼ��
//  @param      adcn            
//  @param      speed      		
//  @return     void
//  Sample usage:   ��ʼ������ΪADC����,ADCʱ��Ƶ�ʣ�SYSclk/2
//-------------------------------------------------------------------------------------------------------------------
/*
  0(1.0)  //1(1.1) 2(5.4) 3(1.3) 4(1.4) 5(1.5) 6(1.6) 7(1.7) 8(0.0) 9(0.1) 10(0.2) 
	11(0.3) 12(0.4) 13(0.5) 14(0.6)
*/
void Use_adc_Init(void)
{
	
//	adc_init(ADC_P05, ADC_SYSclk_DIV_2);//ADCͨ��13
	adc_init(ADC_P16, ADC_SYSclk_DIV_2);//6
	adc_init(ADC_P17, ADC_SYSclk_DIV_2);//7
	adc_init(ADC_P00, ADC_SYSclk_DIV_2);//8
	adc_init(ADC_P01, ADC_SYSclk_DIV_2);//9
	adc_init(ADC_P02, ADC_SYSclk_DIV_2);//10
	adc_init(ADC_P03, ADC_SYSclk_DIV_2);//11	
	
	
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADCת��һ�ζ�ֵ
//  @param      adcn            ѡ��ADCͨ��
//  @param      resolution      �ֱ���
//  @return     void
//  Sample usage:               adc_convert(ADC_P10, ADC_10BIT);
//-------------------------------------------------------------------------------------------------------------------
///*����������֤��ʼ������Ҫ�����ã�ֱ�Ӷ�ν��е���ת������*/DMA���ö���ֱ��ת��
//void Read_adc_once(void)
//{
//   adc_data[0] = adc_once(ADC_P11,ADC_12BIT);
//	 adc_data[1] = adc_once(ADC_P13,ADC_12BIT);
//	 adc_data[2] = adc_once(ADC_P14,ADC_12BIT);
//	 adc_data[3] = adc_once(ADC_P15,ADC_12BIT);
//	 adc_data[4] = adc_once(ADC_P16,ADC_12BIT);
//}
//����ת����6�θĳ�8��
void shuju_adc(void)
{
   uint8 i,n,j,x=0,y=0;
 
	if(DmaADCFlag)  //�ж�ADC DMA�����Ƿ����
		{
			bubble_sort();
			average_value();
			normalization();
			DmaADCFlag = 0; //�����ɱ�־   
		
				y=0;
			  OLED_ShowNum(0,0,16,2,12);	
			  OLED_ShowNum(0,12,17,2,12);	
			  OLED_ShowNum(0,24,00,2,12);	
			  OLED_ShowNum(0,36,01,2,12);	
			  OLED_ShowNum(0,48,02,2,12);	
        OLED_ShowNum(60,0,03,2,12);			
				OLED_ShowString(12,0,":",12);
	      OLED_ShowString(12,12,":",12);	
	      OLED_ShowString(12,24,":",12);	
	      OLED_ShowString(12,36,":",12);	
	      OLED_ShowString(12,48,":",12);	
			  OLED_ShowString(72,0,":",12);	
			for(i=0; i<ADC_CH; i++)     //��ӡÿ������ͨ���Ĳ������//5
			{
         if(i<5)  x=15;
				else	if(i==5) { x=78;y=0;}
				else y=0;
							
        
				oled_printf_float(x,y,my_sqrt(normalization_result[i]),2,3,12);
            OLED_Refresh();						
					y=y+12;	
					}
		
			
		 DMA_ADC_TRIG();		//���´���������һ��ת��
  }	
}


