/*
*���ܣ��䲽�������ʽ
*/
#include <stdio.h>
#include <math.h>

//���ֺ���
double fun(double x);
//�䲽�����λ���
double RepeatT(double a,double b,int n);

int main()
{
	printf("sin(x*x) ������(0,3.14)�ϵĻ���Ϊ��%lf\n",RepeatT(0.0,3.141592653,100));
	return 0;
}

//�䲽�����λ���
double RepeatT(double a,double b,int n)
{
	double sum = 0;
	int i;
	double h = (b-a)/n;  //���ò���
	for(i=0;i<n;i++)     //������ͼ������
		sum += h/2*(fun(a+i*h)+fun(a+(i+1)*h));
	return sum;
}
//���ֺ���
double fun(double x)
{
	return (sin(x*x));
}