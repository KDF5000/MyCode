#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UPLEFT 0
#define UPRIGHT 1
#define DOWNLEFT 3
#define DOWNRIGHT 4
#define N 16
//将Marray缓冲区数据copy到array
int ** copyM(int **array,int **Marray,int position,int n);
//将A和B相加结果保存在T
int ** addM(int **T,int **arrayA,int **arrayB,int n);
//将A-B结果保存在T
int ** jianM(int **T,int **arrayA,int **arrayB,int n);
//将arrayC拷贝回矩阵
void copyBack(int **arrayC,int **Marray,int position,int n);
//打印矩阵
void printM(int **Marray,int n);

//Strassen矩阵相乘算法
int ** StrassenM(int **MarryA ,int **MarryB,int **result,int n)
{	
	int i;
	//递归结束条件
	if(n==1)
	{
		result[0][0] = MarryA[0][0] * MarryB[0][0];
		return result;
	}
	//将A矩阵分成4等分的缓冲区
	int **A11 = (int **)malloc(sizeof(int *)*(n/2));
	int **A12 = (int **)malloc(sizeof(int *)*(n/2));
	int **A21 = (int **)malloc(sizeof(int *)*(n/2));
	int **A22 = (int **)malloc(sizeof(int *)*(n/2));
	//将B矩阵分成4等分的缓冲区
	int **B11 = (int **)malloc(sizeof(int *)*(n/2));
	int **B12 = (int **)malloc(sizeof(int *)*(n/2));
	int **B21 = (int **)malloc(sizeof(int *)*(n/2));
	int **B22 = (int **)malloc(sizeof(int *)*(n/2));
	//M缓冲区保存中间计算值
	int **M1 = (int **)malloc(sizeof(int *)*(n/2));
	int **M2 = (int **)malloc(sizeof(int *)*(n/2));
	int **M3 = (int **)malloc(sizeof(int *)*(n/2));
	int **M4= (int **)malloc(sizeof(int *)*(n/2));
	int **M5= (int **)malloc(sizeof(int *)*(n/2));
	int **M6= (int **)malloc(sizeof(int *)*(n/2));
	int **M7= (int **)malloc(sizeof(int *)*(n/2));
	//临时缓冲区用于保存相加减的结果
	int **T1= (int **)malloc(sizeof(int *)*(n/2));
	int **T2= (int **)malloc(sizeof(int *)*(n/2));
	//申请矩阵缓冲区
	for(i=0;i<n/2;i++)
	{
		A11[i] = (int *)malloc(sizeof(int )*(n/2));
		A12[i] = (int *)malloc(sizeof(int )*(n/2));
		A21[i] = (int *)malloc(sizeof(int )*(n/2));
		A22[i] = (int *)malloc(sizeof(int )*(n/2));

		B11[i] = (int *)malloc(sizeof(int )*(n/2));
		B12[i] = (int *)malloc(sizeof(int )*(n/2));
		B21[i] = (int *)malloc(sizeof(int )*(n/2));
		B22[i] = (int *)malloc(sizeof(int )*(n/2));

		M1[i] = (int *)malloc(sizeof(int)*(n/2));
		M2[i] = (int *)malloc(sizeof(int)*(n/2));
		M3[i] = (int *)malloc(sizeof(int)*(n/2));
		M4[i] = (int *)malloc(sizeof(int)*(n/2));
		M5[i] = (int *)malloc(sizeof(int)*(n/2));
		M6[i] = (int *)malloc(sizeof(int)*(n/2));
		M7[i] = (int *)malloc(sizeof(int)*(n/2));

		T1[i] = (int *)malloc(sizeof(int)*(n/2));
		T2[i] = (int *)malloc(sizeof(int)*(n/2));
	}
	//将A矩阵分成四小块
	copyM(A11,MarryA,UPLEFT,n/2);
	copyM(A12,MarryA,UPRIGHT,n/2);
	copyM(A21,MarryA,DOWNLEFT,n/2);
	copyM(A22,MarryA,DOWNRIGHT,n/2);
	//将B矩阵分成四小块
	copyM(B11,MarryB,UPLEFT,n/2);
	copyM(B12,MarryB,UPRIGHT,n/2);
	copyM(B21,MarryB,DOWNLEFT,n/2);
	copyM(B22,MarryB,DOWNRIGHT,n/2);


	//下面是计算M1-M7
	addM(T1,A11,A22,n/2);
	addM(T2,B11,B22,n/2);
	StrassenM(T1,T2,M1,n/2);

	addM(T1,A21,A22,n/2);
	StrassenM(T1,B11,M2,n/2);

	jianM(T1,B12,B22,n/2);
	StrassenM(A11,T1,M3,n/2);

	jianM(T1,B21,B11,n/2);
	StrassenM(A22,T1,M4,n/2);

	addM(T1,A11,A12,n/2);
	StrassenM(T1,B22,M5,n/2);

	jianM(T1,A21,A11,n/2);
	addM(T2,B11,B12,n/2);
	StrassenM(T1,T2,M6,n/2);

	jianM(T1,A12,A22,n/2);
	addM(T2,B21,B22,n/2);
	StrassenM(T1,T2,M7,n/2);
   
	//下面是有M1-M7的值计算相乘矩阵结果的四部分
	//上左
	addM(T1,M1,M7,n/2);
	jianM(T2,M4,M5,n/2);
	addM(T1,T1,T2,n/2);
	copyBack(T1,result,UPLEFT,n/2);
	
	//上右
	addM(T1,M3,M5,n/2);
	copyBack(T1,result,UPRIGHT,n/2);
	
	//下左
	addM(T1,M2,M4,n/2);
	copyBack(T1,result,DOWNLEFT,n/2);
	
	//下右
	jianM(T1,M1,M2,n/2);
	addM(T2,M3,M6,n/2);
	addM(T1,T1,T2,n/2);
	copyBack(T1,result,DOWNRIGHT,n/2);

	return result;
}

//将Marray缓冲区数据copy到array
int ** copyM(int **arrayAB,int **Marray,int position,int n)
{
	int i;
	switch(position)
	{
		case UPLEFT:
		for(i=0;i<n;i++)
			{
				memcpy(arrayAB[i],Marray[i],sizeof(int)*n);
			}
		break;
		case UPRIGHT:
			for(i=0;i<n;i++)
			{
				memcpy(arrayAB[i],Marray[i]+n,sizeof(int)*n);
			}
		break;
		case DOWNLEFT:
		for(i=0;i<n;i++)
			{
				memcpy(arrayAB[i],Marray[i+n],sizeof(int)*n);
			}
		break;
		case DOWNRIGHT:
			for(i=0;i<n;i++)
			{
				memcpy(arrayAB[i],Marray[i+n]+n,sizeof(int)*n);
			}
		break;
		default:
		break;
	}
	return arrayAB;
}

//将A和B相加结果保存在T
int ** addM(int **T,int **arrayA,int **arrayB,int n)
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			T[i][j] = arrayA[i][j] +arrayB[i][j];
		}
	return T;
}
//将A和B相减结果保存在T
int ** jianM(int **T,int **arrayA,int **arrayB,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{
		T[i][j] = arrayA[i][j] - arrayB[i][j];
	}
	return T;
}

//将arrayC拷贝回矩阵
void copyBack(int **arrayC,int **Marray,int position,int n)
{
	int i;
	switch(position)
	{
	case UPLEFT:
		for(i=0;i<n;i++)
		{
			memcpy(Marray[i],arrayC[i],sizeof(int)*n);
		}
	break;
	case UPRIGHT:
		for(i=0;i<n;i++)
		{
			memcpy(Marray[i]+n,arrayC[i],sizeof(int)*n);
		}
	break;
	case DOWNLEFT:
		for(i=0;i<n;i++)
		{
			memcpy(Marray[i+n],arrayC[i],sizeof(int)*n);
		}
	break;
	case DOWNRIGHT:
	for(i=0;i<n;i++)
		{
			memcpy(Marray[i+n]+n,arrayC[i],sizeof(int)*n);
		}
	break;
	default:
	break;
	}
	return;
}
//打印矩阵
void printM(int **Marray,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
	  for(j=0;j<n;j++)
	  {
	    printf("%d ",Marray[i][j] );
	  }
	  printf("\n");
	}
}
void main()
{
	int **MarrayA = (int **)malloc(sizeof(int *)*N);
	int **MarrayB = (int **)malloc(sizeof(int *)*N);
	int **Result = (int **)malloc(sizeof(int *)*N);
	int i,j;
	for(i=0;i<N;i++)
	{
		MarrayA[i] = (int *)malloc(sizeof(int)*N);
		MarrayB[i] = (int *)malloc(sizeof(int)*N);
		Result[i] = (int *)malloc(sizeof(int)*N);
	}
	for(i=0;i<N;i++)
	  for(j=0;j<N;j++)
	  {
		  /*if(i==j)
		  {
			MarrayA[i][j] = 1;
			MarrayB[i][j] = 1;
		  }else
		  {
			MarrayA[i][j] = 0;
			MarrayB[i][j] = 0;
		  }*/
			MarrayA[i][j] = rand()%10;
			MarrayB[i][j] = rand()%10;
	  }
	printf("矩阵A\n");
	printM(MarrayA,N);
	printf("矩阵B\n");
	printM(MarrayB,N);
	StrassenM(MarrayA,MarrayB,Result,N);
	printf("结果:\n");
	printM(Result,N);
	getchar();
}
