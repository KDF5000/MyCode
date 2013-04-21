/*
*功能：变步长求积公式
*/
#include <stdio.h>
#include <math.h>

//积分函数
double fun(double x);
//变步长梯形积分
double RepeatT(double a,double b,int n);

int main()
{
	printf("sin(x*x) 在区间(0,3.14)上的积分为：%lf\n",RepeatT(0.0,3.141592653,100));
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
	return (sin(x*x));
}