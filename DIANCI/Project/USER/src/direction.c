/*
 * @Author: lanchanghai
 * @Date: 2023-06-09 22:32:02
 * @LastEditors: lanchanghai
 * @LastEditTime: 2023-06-17 19:37:20
 * @FilePath: \DIANCI\Project\USER\src\direction.c
 */
#include "headfile.h"

float poserror=0;   //外环偏差
int Servo_duty=0;  //转向输出PWM
DirectPidStruct Direction;
//舵机参数
#define Servos_Middle 3390               // 舵机中值       
#define Servos_Zmax 3750                 // 舵机左最值       
#define Servos_Ymax 2990                 // 舵机右最值
//定义ADC的最值
//因为使用12位精度ADC故 2的12次方=4096
#define ADC_MAX    4096                  //ADC 12位精度 2的12次方=4096
#define ADC_MIN     0                    

uint16 DMA_ADC_dat[ADC_CH][(ADC_DATA-4)/2];   //将DMA中ADC数据高低位合并(每一个通道转换八次)
double average[ADC_CH]={0};  //ADC每一个通道去掉最大小值的平均值
float normalization_result[ADC_CH];//平均值归一化



//把DMA中数据和在一起12位数据
void pooled_data(void)
{
     uint8 i,j,n=0,a;
     a=((ADC_DATA-4));//16
     for(i=0;i<ADC_CH;i++)
     {
			 n=0;
     for(j=0;j<a;j=j+2)
     {
      DMA_ADC_dat[i][n] = ((uint16)DmaAdBuffer[i][j])<<8 | DmaAdBuffer[i][j+1];
			 n++;
     }

     }

}
//软件滤波限幅法
//限幅法滤波//
//冒泡排序一个通道电感的值//
void bubble_sort(void)
{
   uint8 i,j,n,a;
	uint16 temp;
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
//排序完的数组去掉三组最大最小值求平均值
void average_value(void)
{
  uint8 i,n,a,j;
	double sum=0;
	
    a=((ADC_DATA-4)/2);
    for(n=0;n<ADC_CH;n++)
    {
			sum=0;
			average[n] = 0;
			
			for(j=0;j<=6;j++)
			{  //循环递回平均值6次
       if(j==0)
			 {
				 for(i=3;i<a-3;i++) //去掉最大最小的值
				 {
					average[n] = average[n]+DMA_ADC_dat[n][i];
					
				 }
			  sum = average[n];
			 }
			 else {
				average[n] =average[n] +sum;
			  sum = average[n];
			 }
			 
        sum = sum/(a+j-6); 
		    
			
    }
			 average[n]= sum ;
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
   bubble_sort();//冒泡排序一个通道电感的值//
   average_value();//排序完的数组去掉最大最小值求平均值
   normalization();//归一化
}
//浮点型的绝对值
float fabs(float x)
{
   if(x>=0) return x;
	 if(x<0) return -x;


}
//======================================================================
//函数名称 : cal_poserror
//功能描述 : 差比和计算误差
//输入参数 : 
//输出参数 : 
//返回值   : NONE
//备注     :  across横电感 vertical竖电感 splayed八字型
//        (/ 十  十 \)   
// (A*(L-R)+B*(LM-RM))/(A*(L+R)+C*(|LM+RM|))
//======================================================================
//若输出量跟舵机打角有偏差需要调整，改变系数A B C P
void cal_poserror(float a_Ls,float a_La,float a_Lv,float a_Rs,float a_Ra,float a_Rv)
{
   float cha ,he;
	 float A=1,B=1,C=1,P=1;
   cha = my_sqrt(A*(a_La - a_Ra)) + my_sqrt(B*(a_Ls - a_Rs));
	 he = my_sqrt(A*(a_La + a_Ra)) + my_sqrt(C*fabs(a_Ls - a_Rs));
	 poserror = (cha/he)*P;
	  
}
/*******************************************************************************
* 函数名		：steering_angl
* 描述			：舵机角度设置
* 参数			：
						angl        舵机角度（正：左转  负：右转  360 <= angl <= -400）
* 返回			:void
* 编写者		：XY
* 编写日期	：2021-12-19
*******************************************************************************/
void Steering_Angl(int angl)
{
	int PWM1_duty;
	
		PWM1_duty = Servos_Middle  + angl;						//duty占空比为3390时，舵机居中
	if(PWM1_duty <= Servos_Ymax)//右转限幅
		{PWM1_duty = Servos_Ymax;}
		if(PWM1_duty >= Servos_Zmax)//左转限幅
		{PWM1_duty = Servos_Zmax;}
	pwm_init(PWMB_CH3_P22 , 50,PWM1_duty);	//PWMA设置占空比
	
	
}

//根据不同元素判断系数PD的值（Direction），用AD值控制舵机打角
void Direction_out(void)
{
  //进行标志位判断来配置每一个赛道元素的参数值  舵机一半最值为360，误差最大18，PD系数为20
	//让其近似一比一的关系
	if(circular_flag ==1)
	{
	  Direction.KP=5; 
		Direction.KD=2;
	}
   //转向PD控制
	 Direction.SumError=Direction.KP*poserror+Direction.KD*(poserror-Direction.PrevError);//电感差比和算出的偏差做增量式PD计算
	 Direction.PrevError=poserror;
	 Direction.Pre1_Error[3]= Direction.Pre1_Error[2];
	 Direction.Pre1_Error[2]= Direction.Pre1_Error[1];
	 Direction.Pre1_Error[1]= Direction.Pre1_Error[0];
	 Direction.Pre1_Error[0]=Direction.SumError;
	//拟合没有改变数值
	 Direction.Direct_Parameter=Direction.Pre1_Error[0]*0.8+Direction.Pre1_Error[1]*0.1+
																Direction.Pre1_Error[2]*0.06+Direction.Pre1_Error[3]*0.04 ;//曲线拟合   最小二乘
   Servo_duty = (int)(Direction.Direct_Parameter);
	 //转向限制幅度
	 if(Servo_duty >= 400) Servo_duty = 400;
	 if(Servo_duty <= -360) Servo_duty -360;
	  Steering_Angl(Servo_duty);
}





