/*
*作者：KDF5000
*功能：利用拉格朗日插值法求解近似值
*时间：2013.4.15
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//存放插值节点
struct Data{
	double x;
	double y;
	struct Data *next;
};
/****************************************************
*LagrangeInsert()
*功能：拉格朗日插值法
*****************************************************/
double LagrangeInsert(struct Data *header,double x)
{
	Data *pi,*pj,*p;
	pi=pj=header->next;
	double temp1,temp2;
	temp1=0;                //记录内循环的积
	temp2=1;				//记录外循环的和
	while(pi!=NULL)
	{
		while(pj!=NULL)
		{
			if(pi!=pj)
				temp2 *=(x-pj->x)/(pi->x-pj->x);
			pj = pj->next;
		}
		temp1 +=temp2*pi->y;
		temp2=1;
		pj = header->next;
		pi = pi->next;
	}
	return temp1;   //返回计算结果
}

void main()
{
	Data *header = (Data *)malloc(sizeof(Data));
	char str[20];
	Data *p,*newData;
	char strx[20],stry[20];
	double x;

	p=header;
	p->x=0;
	p->y=0;
	p->next=NULL;

	//输出提示信息
	printf("*******************************************\n");
	printf("使用说明：\n1.用户输入插值点，每一行输入一组：x y;\n2.输入换行表示输入结束。\n");
	printf("*******************************************\n");
	printf("x    y\n");

	//接收用户输入知道第一次输入非换行为止
	memset(str,0,sizeof(str));
	while(strlen(str)==0)
     	gets(str);
	//数据输入完毕，输入换行结束输入
	while(strlen(str)!=0)
	{
		newData = (Data *)malloc(sizeof(Data));
		sscanf(str,"%s%s",strx,stry);     //获取输入的前两个字符串 第一个为x,第二个为y
		newData->x = strtod(strx,NULL);   //将输入转换成浮点数
		newData->y = strtod(stry,NULL);   
		newData->next=NULL;
		p->next=newData;
		p = p->next;
		gets(str);
	}
	printf("请输入要计算的x值：");
	scanf("%lf",&x);
	printf("L(%f) = %f\n",x,LagrangeInsert(header,0.20));
	return ;
}
