/*
 * @Author: lanchanghai
 * @Date: 2023-06-09 22:32:02
 * @LastEditors: lanchanghai
 * @LastEditTime: 2023-06-16 16:48:10
 * @FilePath: \DIANCI\Project\USER\inc\PID.h
 */
#ifndef _PID_H
#define _PID_H
#include "headfile.h"

typedef struct
{
		float       Kp;   //p
    float     	Ki;   //I
	  float       Kd;   //D
	  float       imax; //�����޷�
	  
	  float       out_p; //Kp���
	  float       out_i; //Ki���
	  float       out_d; //Kd���
	  float       out;   //pid���
	
	  float       integrator;//����ֵ
	  float       limit;   //�����޷�
	  float       error;    //��ǰ���
	  float       last_error; //�ϴ����
	  float       last_last_error;//���ϴ����  
	  float       last_derivative;//�ϴ�����뵱ǰ���֮��
	
	  
}PIDL_Type_Def;
typedef struct
{
		float       Kp;   //p
    float     	Ki;   //I
	  float       Kd;   //D
	  float       imax; //�����޷�
	  
	  float       out_p; //Kp���
	  float       out_i; //Ki���
	  float       out_d; //Kd���
	  float       out;   //pid���
	
	  float       integrator;//����ֵ
	  float       limit;
	  float       error;    //��ǰ���
	  float       last_error;//�ϴ����
	  float       last_last_error;//���ϴ����
	  float       last_derivative;//�ϴ�����뵱ǰ���֮��
	  
}PIDR_Type_Def;

extern PIDL_Type_Def  pid_LL;
extern PIDR_Type_Def  pid_RR;
float constrain_float(float amt, float low, float high);
void PIDL_Init(PIDL_Type_Def *PIDL);
void PIDR_Init(PIDR_Type_Def *PIDR);
float PIDL_Inc(float error_L, PIDL_Type_Def *PIDL);
float PIDR_Inc(float error_R, PIDR_Type_Def *PIDR);
// float PIDR_Loc(float error_R,PIDR_Type_Def *PIDR);
// float PIDL_Loc(float error_L,PIDL_Type_Def *PIDL);

#endif














