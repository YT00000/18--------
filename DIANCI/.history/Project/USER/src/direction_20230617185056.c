/*
 * @Author: lanchanghai
 * @Date: 2023-06-09 22:32:02
 * @LastEditors: lanchanghai
 * @LastEditTime: 2023-06-17 18:50:42
 * @FilePath: \DIANCI\Project\USER\src\direction.c
 */
#include "headfile.h"

//舵机参数
#define Servos_Middle 3390               // 舵机中值       
#define Servos_Zmax 3750                 // 舵机左最值       
#define Servos_Ymax 2990                 // 舵机右最值
//定义ADC的最值
//因为使用12位精度ADC故 2的12次方=4096
#define ADC_MAX    4096                  //ADC 12位精度 2的12次方=4096
#define ADC_MIN     0                    

uint16 DMA_ADC_dat[ADC_CH][(ADC_DATA-4)/2];   //将DMA中ADC数据高低位合并(每一个通道转换八次)
float average[ADC_CH];  //ADC每一个通道去掉最大小值的平均值
float normalization_result[ADC_CH];//平均值归一化



//把DMA中数据和在一起12位数据
void pooled_data(void)
{
     uint8 i,j,n,a;
     a=((ADC_DATA-4)/2);
     for(i=0;i<ADC_CH;i++)
     {
     for(j=0,n=0;j<a;j=j+2,n++)
     {
      DMA_ADC_dat[i][n] = DmaAdBuffer[i][j]<<8;
      DMA_ADC_dat[i][n] = DMA_ADC_dat[i][n]|DmaAdBuffer[i][j+1];
     }

     }

}
//软件滤波限幅法
//限幅法滤波//
//冒泡排序一个通道电感的值//
void bubble_sort(void)
{
   uint8 i,j,n,a,temp;
    a=((ADC_DATA-4)/2);
    for(n=0;n<ADC_CH;n++)
    {
     for(i=0;i<a;i++)
     {
        for(j=0;j<a-1-i;j++)
        {
         if(DMA_ADC_dat[n][j]>DMA_ADC_dat[n][j+1])    //这里默认采用升序来排列 
          {
            temp = DMA_ADC_dat[n][j];
            DMA_ADC_dat[n][j] = DMA_ADC_dat[n][j+1];
            DMA_ADC_dat[n][j+1] = temp;
          }
        }
     }
    }
}
//排序完的数组去掉最大最小值求平均值
void average_value(void)
{
  uint8 i,j,n,a,temp;
    a=((ADC_DATA-4)/2);
    for(n=0;n<ADC_CH;n++)
    {
        average[n] = 0;
     for(i=1;i<a-1;i++) //去掉最大最小的值
     {
        average[n] = average[n]+DMA_ADC_dat[n][i];
     }
        average[n] = average[n]/(a-2);
    }
}
//归一化
/*
归一化的公式如下：(x-Min)/(Max-Min).其中,x为实时检测到的变量,Min与Max
为标定的电感采集最小与最大值.具体代码如下:
AD_M_Left[0] =(uint16)(99*(LeftAverage[0]-M_Left_min)/(M_Left_max[0]-M_Left_min)+1);
*/
//若想舵机更顺滑可以对偏差error的计算进行处理，例如将归一化后的值开方
void normalization(void)
{
    uint8 i;
    for(i=0;i<ADC_CH;i++)
    {
    normalization_result[i] =100*((average[i]-ADC_MIN)/(ADC_MAX-ADC_MIN));

    }
    
}
//开方
//======================================================================
//函数名称 : my_sqrt(float number)
//功能描述 : 开平方算法
//输入参数 : 
//输出参数 : 
//返回值   : NONE
//备注     :  
//======================================================================
float my_sqrt(float number)
{
    long i;
    float x, y;
    const float f = 1.5F;
    x = number * 0.5F;
    y = number;
    i = * ( long * ) &y;
    i = 0x5f3759df - ( i >> 1 );

    y = * ( float * ) &i;
    y = y * ( f - ( x * y * y ) );
    y = y * ( f - ( x * y * y ) );
    return number * y;
}
float my_pow(float x)
{
	return x*x;
}
//在计算偏差之前应调用好的函数
void prepare_dat(void)
{
   pooled_data();//把DMA中数据和在一起12位数据
   bubble_sort()

}
//======================================================================
//函数名称 : cal_poserror
//功能描述 : 差比和计算误差
//输入参数 : 
//输出参数 : 
//返回值   : NONE
//备注     :  across横电感 vertical竖电感 splayed八字型
//        (/ 十  十 \)
//======================================================================
void cal_poserror(float a_Ls,float a_La,float a_Lv,float a_Rs,float a_Ra,float a_Rv)
{
   float cha ,he;
   cha = 

}





