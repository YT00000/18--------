/*
 * @Author: lanchanghai
 * @Date: 2023-06-09 22:32:02
 * @LastEditors: lanchanghai
 * @LastEditTime: 2023-06-11 09:48:42
 * @FilePath: \DIANCI\Project\USER\inc\motor.h
 */
#ifndef _MOTOR_H
#define _MOTOR_H
#include "headfile.h"

extern int8 RUN ;
void PID_control(int32 expected_speedL,int32 expected_speedR);
void motor_Control(void);
void motor_init(void);         
void qian(void);
void hou(void);
void ting(void);

#define   motorduty_Max  70*500   //占空比设置成70%，即70*500=35000，若占空比为X，则motorduty_Max为 X*500
#define   motorduty_Min  -70*500



#endif


