#include "headfile.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC��ʼ��
//  @param      adcn            
//  @param      speed      		
//  @return     void
//  Sample usage:   ��ʼ������ΪADC����,ADCʱ��Ƶ�ʣ�SYSclk/2
//-------------------------------------------------------------------------------------------------------------------
/*
  0(1.0)  //1(1.1) 2(5.4) 3(1.3) //4(1.4) 5(1.5) //6(1.6) 7(1.7) 8(0.0) 9(0.1) 10(0.2) 
	11(0.3) 12(0.4) 13(0.5) 14(0.6)
*/
void Use_adc_Init(void)
{
	
//	adc_init(ADC_P05, ADC_SYSclk_DIV_2);//ADCͨ��13
	adc_init(ADC_P00, ADC_SYSclk_DIV_2);//8
	adc_init(ADC_P17, ADC_SYSclk_DIV_2);//7
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
//void shuju_adc(void)
//{
//   uint8 i,n,x=0,y=0;
//	
//   uint16 dat[5*ADC_CH+1];
//	 
//	if(DmaADCFlag)  //�ж�ADC DMA�����Ƿ����
//		{
//			DmaADCFlag = 0; //�����ɱ�־   
//		
//				y=0;
//			  OLED_ShowNum(0,0,17,2,12);	
//			  OLED_ShowNum(0,12,00,2,12);	
//			  OLED_ShowNum(0,24,01,2,12);	
//			  OLED_ShowNum(0,36,02,2,12);	
//			  OLED_ShowNum(0,48,03,2,12);	
////        OLED_ShowNum(70,0,5,1,12);			
//				OLED_ShowString(12,0,":",12);
//	      OLED_ShowString(12,12,":",12);	
//	      OLED_ShowString(12,24,":",12);	
//	      OLED_ShowString(12,36,":",12);	
//	      OLED_ShowString(12,48,":",12);	
////			  OLED_ShowString(76,0,":",12);	
//			for(i=0; i<ADC_CH; i++)     //��ӡÿ������ͨ���Ĳ������//5
//			{
//         if(i<5)  x=18;
//				else	if(i==5) { x=82;y=0;}
//				else y=0;
//				for(n=0; n<ADC_DATA; n=n+2)   //��ӡ��ǰͨ���Ĳ�������//12
//				{				
//					dat[i]=DmaAdBuffer[i][n]<<8;
//					dat[i]=dat[i]|DmaAdBuffer[i][n+1];
//					
//					if(n==10)
//					{
//						
//						OLED_ShowNum(x,y,dat[i],4,12);	
//            OLED_Refresh();						
//					y=y+12;	
//					}
//			}	      		
//			}
//			
//		 DMA_ADC_TRIG();		//���´���������һ��ת��
//  }	
//}


