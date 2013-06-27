#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>  

#define N 100  //���ó�100����ļ���
#define MAXDISTANCE 1000.0  //�����
#define ERROR -1			//�������
#define SORTX 0             //��������ֵΪx
#define SORTY 1              //��������ֵΪy
struct Point{
	double x;
	double y;
	struct Point *next;
};
//ֱ�Ӳ���������
double findNearest3Point(Point *P,int n);

//�ڼ���p�в���value
bool findX(Point *p,double value,int n);

//�ڼ���p�в���value
bool findY(Point *p,double value,int n);

//����������
double findNearest(Point *P,Point *X,Point *Y,int n);

//�����������
void QuickSort(Point *header , Point *tail,int type);

//����ָ���ڵ��ǰһ���ڵ�
Point * preNode(Point *header,Point *tail,Point *node);

//�ָ�����
Point * partiton(Point *header,Point *tail,int type);

//���������ڵ��ֵ
void exchange(Point *i,Point *j);

//��ӡ����
void print_list(Point *head) ;

//ֻ�������ڵ�ʱ
void compare2points(Point *header,Point *tail,int type);