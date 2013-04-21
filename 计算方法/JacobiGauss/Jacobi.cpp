/*
*Jacobi.cpp
*���ܣ�Jacobi����
*ʱ�䣺2013.4.1
*/
#include "Jacobi.h"
void Jacobi(int n , double E)
{
	int i; // ����ѭ��
	int k=0; //��¼��������
	double maxE;

	//���ó�ʼֵ
	double *a = (double *)malloc(sizeof(double)*(n+1));
	for(i=1;i<=n;i++)
	{
		a[i]=0;
		printf("%d :X0=%f ,",k,a[i]);
	}

	printf("\n");
	//����µĽ�
	double *temp = (double *)malloc(sizeof(double)*(n+1));
    do
	{
		CalculateJ(a,temp);
		k++;
		printf("%d :",k);
		for(i=1;i<=n;i++)
		{
			printf("X%d=%f ,",i,temp[i]);
		}
		printf("\n");
		swapX(temp,a,n);
		maxE = fabs(temp[1]-a[1]);
		for(i=2;i<=n;i++)
		{
			if(maxE<fabs(temp[i]-a[i]))
				maxE = fabs(temp[i]-a[i]);
		}
	}while(maxE	>=E);
	return ;
}

//����x
void CalculateJ(double *a,double *temp)
{
	temp[1] = -2.4-0.4*a[2]-0.2*a[3];
	temp[2] = 5+0.25*a[1]+0.5*a[3];
	temp[3] = 0.3-0.2*a[1]+0.3*a[2];
	return ;
}
