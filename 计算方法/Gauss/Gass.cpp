#include<stdio.h>
#include"Gass.h"

//��˹��Ԫ������ѡ��Ԫ��
void Gauss (double a[][MAXNUM],int n)
{
	int i,j;
	SelectColE(a,n);   //��ѡ��Ԫ����Ԫ��������
	//�ش����
	printf("�����ǵĽ��\n");
	printM(a,3);
	for(i=n;i>=1;i--)
	{
		for(j=i+1;j<=n;j++)
			a[i][n+1]-=a[i][j]*a[j][n+1];
		a[i][n+1]/=a[i][i];
	}
	return ;
}
//ѡ������Ԫ��������Ԫ
void SelectColE(double a[][MAXNUM],int n)
{
	int i,j,k,maxRowE;
	double temp; //���ڼ�¼��Ԫʱ������
	for(j=1;j<=n;j++)
	{
	//	printf("��%d����Ԫѡ��ǰ��\n",j);
	//	printM(a,3);
		maxRowE=j;
		for(i=j;i<=n;i++)
			if(fabs(a[i][j])>fabs(a[maxRowE][j]))
				maxRowE = i;
		if(maxRowE!=j)
			swapRow(a,j,maxRowE,n);   //�������Ԫ�����н���
		//printf("��%d����Ԫ������\n",j);
	//	printM(a,3);
		//��Ԫ
		for(i=j+1;i<=n;i++)
		{
			temp =a[i][j]/a[j][j];
			for(k=j;k<=n+1;k++)
				a[i][k]-=a[j][k]*temp;
		}
		printf("��%d����Ԫ��\n",j);
		printM(a,3);
	}
	return;
}
void swapRow(double a[][MAXNUM],int m,int maxRowE,int n)
{
	int k;
	double temp;
	for(k=m;k<=n+1;k++)
	{
		temp = a[m][k];
		a[m][k] = a[maxRowE][k];
		a[maxRowE][k] = temp;
	}
	return ;
}
/*void init(double a[][MAXNUM],int n)
{
	//a=(double **)malloc(sizeof(double**)*(n+1));
	//*a=(double *)malloc(sizeof(double)*(n+2));
    double a[3][5]={{0.001,2.000,3.000,1.000},
			 {-1.000,3.712,4.623,2.000},
			 {-2.000,1.070,5.643,3.000}};
	/*for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n+1;j++)
		{
			scanf("%f,",&a[i][j]);
		}
	}
    return ;

}*/
//���Ժ���
int main()
{
    double a[4][MAXNUM];
	
	int i,n,j;
	/*double **a;
	a = (double **)malloc(sizeof(double *)*4);
    for(i=0;i<4;i++)
	{
		*a=(double *)malloc(sizeof(double)*(5));
	}*/
    a[1][1] = 0.001; a[1][2]=2.000;a[1][3]=3.000;a[1][4]=1.000;
    a[2][1] = -1.000;a[2][2]=3.712;a[2][3]=4.623;a[2][4]=2.000;
    a[3][1] = -2.000;a[3][2]=1.070;a[3][3]=5.643;a[3][4]=3.000;
	Gauss (a,3);
	for(i=1;i<=3;i++)
		printf("X%d=%f\n",i,a[i][4]);
//	printM(a,3);
	return 0;
}
//�������
void printM(double a[][MAXNUM], int n)
{
   int i,j;
   for(i=1;i<=n;i++)
	{
		for(j=1;j<=n+1;j++)
		{
			printf("%f ,",a[i][j]);
		}
        printf("\n");
	}
}