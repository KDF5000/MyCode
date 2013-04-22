/*
*功能：变步长梯形求积公式
*/
#include <stdio.h>
#include <math.h>

//积分函数
double fun(double x);
//变步长梯形积分
double RepeatT(double a,double b,int n);
//变步长求积公式
double changeRepeatT(double a,double b,double E);

int main()
{
	printf("e^(-x*x) 在区间(0,1)上的积分为：%lf\n",changeRepeatT(0.0,1.0,0.00001));
	return 0;
}

//变步长梯形积分
double RepeatT(double a,double b,int n)
{
	double sum = 0;
	int i;
	double h = (b-a)/n;  //设置步长
	for(i=0;i<n;i++)     //迭代求和计算积分
		sum += h/2*(fun(a+i*h)+fun(a+(i+1)*h));
	return sum;
}
//积分函数
double fun(double x)
{
	return (exp(-x*x));
}

//变步长求积公式
double changeRepeatT(double a,double b,double E)
{
	int n=1; //n等分
	double h; //步长
	int k=0;
	int i;		//控制循环变量
	double sumT0 = 0;  //记录每次积分值
	double sumT1 = RepeatT(a,b,n);
	printf("k=%d T=%lf\n",k,sumT1);

	//变步长计算复化梯形积分
	while(fabs(sumT0-sumT1)>E)
	{
		n *=2 ;
		k++;
		sumT0 = sumT1;
		sumT1 = RepeatT(a,b,n);
		printf("k=%d T=%lf\n",k,sumT1);
	}
	return sumT1;
}