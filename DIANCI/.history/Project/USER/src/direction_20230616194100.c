/*
 * @Author: lanchanghai
 * @Date: 2023-06-09 22:32:02
 * @LastEditors: lanchanghai
 * @LastEditTime: 2023-06-16 19:40:35
 * @FilePath: \DIANCI\Project\USER\src\direction.c
 */
#include "headfile.h"

//舵机参数
#define Servos_Middle 3390               // 舵机中值       
#define Servos_Zmax 3750                 // 舵机左最值       
#define Servos_Ymax 2990                 // 舵机右最值
//定义ADC的最值
//因为使用12位精度ADC故 2的12次方=4096
uint16 ADC_MAX,ADC_MIN;
  




//ba
//软件滤波限幅法
//限幅法滤波//



