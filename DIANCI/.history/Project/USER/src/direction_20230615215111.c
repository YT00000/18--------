#include "headfile.h"

//舵机参数
#define Servos_Middle 3390               // 舵机中值       
#define Servos_Zmax 3750                 // 舵机左最值       
#define Servos_Ymax 2990                 // 舵机右最值
//定义ADC的最值
//因为使用12位精度ADC故 2的12次方=4096
uint16 ADC_MAX,ADC_MIN;
  
//软件滤波限幅法

//限幅法滤波//
void AD_value()
{
       uint8 i;
       uint16 temp; 
     for ( i = 0; i < ADC_CH; i++)
     {
       temp = DmaAdBuffer[i][10]<<8;
       temp = temp | DmaAdBuffer[i][11];
       if(temp > max1)
     }

}


