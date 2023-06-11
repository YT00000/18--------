/*
 * @Author: lanchanghai
 * @Date: 2023-06-09 22:32:02
 * @LastEditors: lanchanghai
 * @LastEditTime: 2023-06-10 23:36:45
 * @FilePath: \DIANCI\Project\USER\src\motor.c
 */
#include "headfile.h"
//定义一个期望速度（用脉冲数代表速度），因为运用四倍频，即其范围（0~4096）
float expected_speedL

/*************************************************************************
 *  函数名称：void motor_init(void)
 *  功能说明：电机PWM初始化
 *  参数说明：无
 *  函数返回：无
 *  修改时间：2023.4.24
 *  备    注：驱动1个电机
 *************************************************************************/
void motor_init(void)
{
	pwm_init(PWMA_CH1P_P10, 15000, 0); // P1 输出PWM频率17000HZ   占空比为百分之 pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMB_CH2_P21, 15000, 0);  // P2 输出PWM频率17000HZ   占空比为百分之 pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMB_CH1_P20, 15000, 0);  // P3 输出PWM频率17000HZ   占空比为百分之 pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMB_CH4_P23, 15000, 0);  // P4 输出PWM频率17000HZ   占空比为百分之 pwm_duty / PWM_DUTY_MAX * 100
}
void qian(void) // P1-pwm  P2-0 P3-pwm P4-0时前转
{
	pwm_duty(PWMA_CH1P_P10, 5000); // 占空比10%
	pwm_duty(PWMB_CH2_P21, 0);	   // 占空比0%
	pwm_duty(PWMB_CH1_P20, 5000);  // 占空比10%
	pwm_duty(PWMB_CH4_P23, 0);	   // 占空比0%
}
void hou(void) // P1-0  P2-pwm P3-0 P4-pwm时后转
{
	pwm_duty(PWMA_CH3P_P14, 0);	   // 占空比0%
	pwm_duty(PWMA_CH4P_P16, 5000); // 占空比10%
	pwm_duty(PWMB_CH1_P20, 0);	   // 占空比0%
	pwm_duty(PWMB_CH4_P23, 5000);  // 占空比10%
}
void ting(void) // P1=P2 P3=P4或者P1.P2.P3.P4悬空时前转
{
	pwm_duty(PWMA_CH3P_P14, 0); // 占空比0%
	pwm_duty(PWMA_CH4P_P16, 0); // 占空比0%
	pwm_duty(PWMB_CH1_P20, 0);	// 占空比0%
	pwm_duty(PWMB_CH4_P23, 0);	// 占空比0%
}
