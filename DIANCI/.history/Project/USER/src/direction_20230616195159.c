/*
 * @Author: lanchanghai
 * @Date: 2023-06-09 22:32:02
 * @LastEditors: lanchanghai
 * @LastEditTime: 2023-06-16 19:48:14
 * @FilePath: \DIANCI\Project\USER\src\direction.c
 */
#include "headfile.h"

//舵机参数
#define Servos_Middle 3390               // 舵机中值       
#define Servos_Zmax 3750                 // 舵机左最值       
#define Servos_Ymax 2990                 // 舵机右最值

#define ADC_MAX    4096                  //ADC 12位精度 2的12次方=4096
#define ADC_MIN     0                    
//定义ADC的最值
//因为使用12位精度ADC故 2的12次方=4096

  




//把DMA中数据和在一起12位数据
void pooled_data(void)
{
     uint8 i,j;
     for(i=0;i<)

}
//软件滤波限幅法
//限幅法滤波//



