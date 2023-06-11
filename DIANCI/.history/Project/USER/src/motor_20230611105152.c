/*
 * @Author: lanchanghai
 * @Date: 2023-06-09 22:32:02
 * @LastEditors: lanchanghai
 * @LastEditTime: 2023-06-11 10:51:51
 * @FilePath: \DIANCI\Project\USER\src\motor.c
 */
#include "headfile.h"
 
#define duty_Max 8*4096  //4096*8=32768
                         //duty_Max = Y(PIDϵ����Χ) * 4096 �� duty_Max�Ǿ���PID�ó������������ռ�ձ� 
#define duty_Min -8*4096

#define coefficient duty_Max/motorduty_Max  //32768/35000=0.936
//����һ�������ٶȣ��������������ٶȣ�����Ϊ�����ı�Ƶ�����䷶Χ��0~4096��
int16 expected_speedL,expected_speedR;
float new_speedL,new_speedR;  //�нӱ������е��ٶ�������ֵ
//��������ռ�ձȣ��н�PID�����ֵ
int16 out_duty_L,out_duty_R;
/*************************************************************************
 *  �������ƣ�void motor_init(void)
 *  ����˵�������PWM��ʼ��
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2023.4.24
 *  ��    ע����ʼ�����io��PID����
 *************************************************************************/
void motor_init(void)
{
	pwm_init(PWMA_CH1P_P10, 15000, 0); // P1 ���PWMƵ��15000HZ   ռ�ձ�Ϊ�ٷ�֮ pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMB_CH2_P21, 15000, 0);  // P2 ���PWMƵ��15000HZ   ռ�ձ�Ϊ�ٷ�֮ pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMB_CH1_P20, 15000, 0);  // P3 ���PWMƵ��15000HZ   ռ�ձ�Ϊ�ٷ�֮ pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMB_CH4_P23, 15000, 0);  // P4 ���PWMƵ��15000HZ   ռ�ձ�Ϊ�ٷ�֮ pwm_duty / PWM_DUTY_MAX * 100
//PID������ʼ��
    PIDL_Init(&pid_L);
    PIDR_Init(&pid_R);
}

/*************************************************************************
 *  �������ƣ�void PID_control(int16 expected_speedL,int16 expected_speedR)
 *  ����˵�����������ٶ�ֵ���ͱ��������õ������ٶ�ֵ�������PID���㣬�õ�����Ŀ�����
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2023.4.24
 *  ��    ע��
 *************************************************************************/
//��Ϊռ�ձȹ���ᵼ�µ���𻵣�������ȡ��70%Ϊ���ռ�ձȣ�35000��������1024�߱����������ı�Ƶ�������Ϊ4086��
//��������4096*8=32768����ȡP I D��0~8��
// ��ҪP I D��0~120��ռ�ձȵķ�Χmax= 4096 * PID��Χ��
//�˺�������ռ�ձȺ͵ݸ������ռ�ձ�֮��ı���ϵ��Ϊ duty_Max/(X*500)
void PID_control(int16 expected_speedL,int16 expected_speedR)
{
	float error_L,error_R;

    new_speedL = Read_encoderL();
    new_speedR = Read_encoderR();
    error_L = expected_speedL - new_speedL;
    error_R = expected_speedR - new_speedR;
//����ʽPID
    out_duty_L = (int16)(PIDL_Inc(&pid_L,error_L));
	out_duty_L = (int16)(PIDR_Inc(&pid_R,error_R));
//���ռ�ձ�����
	if(out_duty_L >duty_Max){out_duty_L = duty_Max;}
	if(out_duty_L <duty_Min){out_duty_L = duty_Min;}	
    if(out_duty_R >duty_Min){out_duty_R = motorduty_Max;}
    if(out_duty_R <duty_Min){out_duty_R = motorduty_Min;}

}










void qian(void) // P1-pwm  P2-0 P3-pwm P4-0ʱǰת
{
	pwm_duty(PWMA_CH1P_P10, 5000); // ռ�ձ�10%
	pwm_duty(PWMB_CH2_P21, 0);	   // ռ�ձ�0%
	pwm_duty(PWMB_CH1_P20, 5000);  // ռ�ձ�10%
	pwm_duty(PWMB_CH4_P23, 0);	   // ռ�ձ�0%
}
void hou(void) // P1-0  P2-pwm P3-0 P4-pwmʱ��ת
{
	pwm_duty(PWMA_CH3P_P14, 0);	   // ռ�ձ�0%
	pwm_duty(PWMA_CH4P_P16, 5000); // ռ�ձ�10%
	pwm_duty(PWMB_CH1_P20, 0);	   // ռ�ձ�0%
	pwm_duty(PWMB_CH4_P23, 5000);  // ռ�ձ�10%
}
void ting(void) // P1=P2 P3=P4����P1.P2.P3.P4����ʱǰת
{
	pwm_duty(PWMA_CH3P_P14, 0); // ռ�ձ�0%
	pwm_duty(PWMA_CH4P_P16, 0); // ռ�ձ�0%
	pwm_duty(PWMB_CH1_P20, 0);	// ռ�ձ�0%
	pwm_duty(PWMB_CH4_P23, 0);	// ռ�ձ�0%
}
