/*
 * @Author: lanchanghai
 * @Date: 2023-06-09 22:32:02
 * @LastEditors: lanchanghai
 * @LastEditTime: 2023-06-11 14:48:23
 * @FilePath: \DIANCI\Project\USER\src\motor.c
 */
#include "motor.h"
int8 RUN =0; 
#define duty_Max  32768 //4096*8=32768
                         //duty_Max = Y(PIDϵ����Χ) * 4096 �� duty_Max�Ǿ���PID�ó������������ռ�ձ� 
#define duty_Min -32768

#define coefficient duty_Max/motorduty_Max  //32768/35000=0.936
//����һ�������ٶȣ��������������ٶȣ�����Ϊ�����ı�Ƶ�����䷶Χ��0~4096��
int16 expected_speedL,expected_speedR;
float now_speedL,now_speedR;  //�нӱ������е��ٶ�������ֵ
//��������ռ�ձȣ��н�PID�����ֵ
int32 out_duty_L,out_duty_R;
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
    PIDL_Init(&pid_LL);
    PIDR_Init(&pid_RR);
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
void PID_control(int32 expected_speedL,int32 expected_speedR)
{
	float error_L,error_R;

    now_speedL = Read_encoderL();
    now_speedR = Read_encoderR();
    error_L = expected_speedL - now_speedL;
    error_R = expected_speedR - now_speedR;
//����ʽPID
    out_duty_L = (int32)(PIDL_Inc(error_L,&pid_LL));
	out_duty_L = (int32)(PIDR_Inc(error_R,&pid_RR));
//���ռ�ձ�����
	if(out_duty_L >duty_Max){out_duty_L = duty_Max;}
	if(out_duty_L <duty_Min){out_duty_L = duty_Min;}	
    if(out_duty_R >duty_Min){out_duty_R = duty_Max;}
    if(out_duty_R <duty_Min){out_duty_R = duty_Min;}

}
/*************************************************************************
 *  �������ƣ�void motor_Control(void)
 *  ����˵������PID�õ���������Ե��ת�����п���
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2023.4.24
 *  ��    ע��
 *************************************************************************/
void motor_Control(void)
{
     int16 dutyR =0;
	 int16 dutyL =0;

	dutyL = out_duty_L;
	dutyR = out_duty_R;

	if(RUN == 1){//�ж��Ƿ������
//ǰת
         if (dutyR >= 0) //��ǰ��
		 {
			pwm_duty(PWMA_CH1P_P10, dutyR); 
	        pwm_duty(PWMB_CH2_P21, 0);	
		 }
		 if (dutyL >= 0)//��ǰ��
		{
			pwm_duty(PWMB_CH1_P20, dutyL);  
	        pwm_duty(PWMB_CH4_P23, 0);	  
		}
//��ת
         if (dutyR < 0)//�Һ�ת
		{
			pwm_duty(PWMA_CH1P_P10, 0); 
	        pwm_duty(PWMB_CH2_P21, -dutyR);	
		}
         if (dutyL < 0)
		 {
			pwm_duty(PWMB_CH1_P20, 0);  
	        pwm_duty(PWMB_CH4_P23, -dutyL);	  
		 }
		 
	}

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
