#include "headfile.h"

//舵机参数
#define Servos_Middle 3390               // 舵机中值       
#define Servos_Zmax 3750                 // 舵机左最值       
#define Servos_Ymax 2990                 // 舵机右最值

  
//软件滤波限幅法
/*
  一般来说，每个电感在赛道上采集到的值都有一个固定的范围，由于电感排布
方案的不同（水平电感、竖直电感或斜电感等）或不同赛道电磁信号的差别，这
个范围也会随之变化。这时我们可以在程序的初始化中加入一个扫描赛道的程序，
在初始化程序运行时令车左右扫描，将每个电感的最大值和最小值分别记录入
两个一维数组中，让其作为每个电感采集信号值的上下限（这样也是为了提高
赛车对于不同赛道的适应性）。在后续赛车行驶过程中，便可以过滤在这个范围之
外的电感值，从而排除偶然误差，达到软件滤波的效果。
*/
//扫描赛道//
void saomiao()
{
    uint i;
    uint16 max1=0,min1=4095;
    uint16 temp; 
     for ( i = 0; i < ADC_CH; i++)
     {
       temp = DmaAdBuffer[i][10]<<8;
       temp = temp | DmaAdBuffer[i][11];
       if (temp > max1)
       {
        max1 = temp;
       }
       if(temp < min1)
       {
        min1 = temp;
       }
     }
}
//限幅法滤波//
void AD_value()
{
       uint16 temp; 
     for ( i = 0; i < ADC_CH; i++)
     {
       temp = DmaAdBuffer[i][10]<<8;
       temp = temp | DmaAdBuffer[i][11];

}


