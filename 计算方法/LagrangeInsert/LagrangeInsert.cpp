/*
*���ߣ�KDF5000
*���ܣ������������ղ�ֵ��������ֵ
*ʱ�䣺2013.4.15
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//��Ų�ֵ�ڵ�
struct Data{
	double x;
	double y;
	struct Data *next;
};
/****************************************************
*LagrangeInsert()
*���ܣ��������ղ�ֵ��
*****************************************************/
double LagrangeInsert(struct Data *header,double x)
{
	Data *pi,*pj,*p;
	pi=pj=header->next;
	double temp1,temp2;
	temp1=0;                //��¼��ѭ���Ļ�
	temp2=1;				//��¼��ѭ���ĺ�
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
	return temp1;   //���ؼ�����
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

	//�����ʾ��Ϣ
	printf("*******************************************\n");
	printf("ʹ��˵����\n1.�û������ֵ�㣬ÿһ������һ�飺x y;\n2.���뻻�б�ʾ���������\n");
	printf("*******************************************\n");
	printf("x    y\n");

	//�����û�����֪����һ������ǻ���Ϊֹ
	memset(str,0,sizeof(str));
	while(strlen(str)==0)
     	gets(str);
	//����������ϣ����뻻�н�������
	while(strlen(str)!=0)
	{
		newData = (Data *)malloc(sizeof(Data));
		sscanf(str,"%s%s",strx,stry);     //��ȡ�����ǰ�����ַ��� ��һ��Ϊx,�ڶ���Ϊy
		newData->x = strtod(strx,NULL);   //������ת���ɸ�����
		newData->y = strtod(stry,NULL);   
		newData->next=NULL;
		p->next=newData;
		p = p->next;
		gets(str);
	}
	printf("������Ҫ�����xֵ��");
	scanf("%lf",&x);
	printf("L(%f) = %f\n",x,LagrangeInsert(header,0.20));
	return ;
}
