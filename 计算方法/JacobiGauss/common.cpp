/*
*common.cpp
*����:Jacobi��Gauss�������ú���
*/
#include "common.h"
//������
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