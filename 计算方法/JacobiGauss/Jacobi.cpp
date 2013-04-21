/*
*Jacobi.cpp
*功能：Jacobi迭代
*时间：2013.4.1
*/
#include "Jacobi.h"
void Jacobi(int n , double E)
{
	int i; // 用来循环
	int k=0; //记录迭代次数
	double maxE;

	//设置初始值
	double *a = (double *)malloc(sizeof(double)*(n+1));
	for(i=1;i<=n;i++)
	{
		a[i]=0;
		printf("%d :X0=%f ,",k,a[i]);
	}

	printf("\n");
	//存放新的解
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

//计算x
void CalculateJ(double *a,double *temp)
{
	temp[1] = -2.4-0.4*a[2]-0.2*a[3];
	temp[2] = 5+0.25*a[1]+0.5*a[3];
	temp[3] = 0.3-0.2*a[1]+0.3*a[2];
	return ;
}
