/*
*功能：利用Jacobi迭代和Gauss迭代求解方程组
*时间：2013.4.1
*/
#include "Jacobi.h"
#include "Gauss.h"
int main ()
{
	printf("Jacobi迭代的结果：\n");
	Jacobi(3 , 0.0001);
	printf("*****************************************************\n");
	printf("Gauss迭代的结果：\n");
    Gauss(3,0.0001);
	return 0;
}