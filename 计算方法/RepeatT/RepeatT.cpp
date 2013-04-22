/*
*���ܣ��䲽�����������ʽ
*/
#include <stdio.h>
#include <math.h>

//���ֺ���
double fun(double x);
//�䲽�����λ���
double RepeatT(double a,double b,int n);
//�䲽�������ʽ
double changeRepeatT(double a,double b,double E);

int main()
{
	printf("e^(-x*x) ������(0,1)�ϵĻ���Ϊ��%lf\n",changeRepeatT(0.0,1.0,0.00001));
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
	return (exp(-x*x));
}

//�䲽�������ʽ
double changeRepeatT(double a,double b,double E)
{
	int n=1; //n�ȷ�
	double h; //����
	int k=0;
	int i;		//����ѭ������
	double sumT0 = 0;  //��¼ÿ�λ���ֵ
	double sumT1 = RepeatT(a,b,n);
	printf("k=%d T=%lf\n",k,sumT1);

	//�䲽�����㸴�����λ���
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