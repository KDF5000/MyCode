/*
*���ܣ�����Jacobi������Gauss������ⷽ����
*ʱ�䣺2013.4.1
*/
#include "Jacobi.h"
#include "Gauss.h"
int main ()
{
	printf("Jacobi�����Ľ����\n");
	Jacobi(3 , 0.0001);
	printf("*****************************************************\n");
	printf("Gauss�����Ľ����\n");
    Gauss(3,0.0001);
	return 0;
}