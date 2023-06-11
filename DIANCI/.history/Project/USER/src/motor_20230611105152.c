/*
 * @Author: lanchanghai
 * @Date: 2023-06-09 22:32:02
 * @LastEditors: lanchanghai
 * @LastEditTime: 2023-06-11 10:51:51
 * @FilePath: \DIANCI\Project\USER\src\motor.c
 */
#include "headfile.h"
 
#define duty_Max 8*4096  //4096*8=32768
                         //duty_Max = Y(PID系数范围) * 4096 ， duty_Max是经过PID得出的输出控制量占空比 
#define duty_Min -8*4096

#define coefficient duty_Max/motorduty_Max  //32768/35000=0.936
//定义一个期望速度（用脉冲数代表速度），因为运用四倍频，即其范围（0~4096）
int16 expected_speedL,expected_speedR;
float new_speedL,new_speedR;  //承接编码器中的速度脉冲数值
//定义左右占空比，承接PID的输出值
int16 out_duty_L,out_duty_R;
/*************************************************************************
 *  函数名称：void motor_init(void)
 *  功能说明：电机PWM初始化
 *  参数说明：无
 *  函数返回：无
 *  修改时间：2023.4.24
 *  备    注：初始化电机io和PID参数
 *************************************************************************/
void motor_init(void)
{
	pwm_init(PWMA_CH1P_P10, 15000, 0); // P1 输出PWM频率15000HZ   占空比为百分之 pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMB_CH2_P21, 15000, 0);  // P2 输出PWM频率15000HZ   占空比为百分之 pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMB_CH1_P20, 15000, 0);  // P3 输出PWM频率15000HZ   占空比为百分之 pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMB_CH4_P23, 15000, 0);  // P4 输出PWM频率15000HZ   占空比为百分之 pwm_duty / PWM_DUTY_MAX * 100
//PID参数初始化
    PIDL_Init(&pid_L);
    PIDR_Init(&pid_R);
}

/*************************************************************************
 *  函数名称：void PID_control(int16 expected_speedL,int16 expected_speedR)
 *  功能说明：把期望速度值，和编码器所得的现在速度值做差进行PID计算，得到输出的控制量
 *  参数说明：无
 *  函数返回：无
 *  修改时间：2023.4.24
 *  备    注：
 *************************************************************************/
//因为占空比过大会导致电机损坏，故我们取了70%为最大占空比（35000），由于1024线编码器用了四倍频最大脉冲为4086，
//经过运算4096*8=32768，故取P I D（0~8）
// 若要P I D（0~120）占空比的范围max= 4096 * PID范围；
//此函数所得占空比和递给电机的占空比之间的比例系数为 duty_Max/(X*500)
void PID_control(int16 expected_speedL,int16 expected_speedR)
{
	float error_L,error_R;

    new_speedL = Read_encoderL();
    new_speedR = Read_encoderR();
    error_L = expected_speedL - new_speedL;
    error_R = expected_speedR - new_speedR;
//增量式PID
    out_duty_L = (int16)(PIDL_Inc(&pid_L,error_L));
	out_duty_L = (int16)(PIDR_Inc(&pid_R,error_R));
//电机占空比限制
	if(out_duty_L >duty_Max){out_duty_L = duty_Max;}
	if(out_duty_L <duty_Min){out_duty_L = duty_Min;}	
    if(out_duty_R >duty_Min){out_duty_R = motorduty_Max;}
    if(out_duty_R <duty_Min){out_duty_R = motorduty_Min;}

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
