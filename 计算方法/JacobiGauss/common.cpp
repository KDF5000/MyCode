/*
*common.cpp
*功能:Jacobi和Gauss迭代公用函数
*/
#include "common.h"
//交换解
void swapX(double *temp,double *a,int n)
{
	int i;
	double tmp;
	for(i=1;i<=n;i++)
	{
		tmp = temp[i];
		temp[i] = a[i];
		a[i] = tmp;
	}
	return ;
}