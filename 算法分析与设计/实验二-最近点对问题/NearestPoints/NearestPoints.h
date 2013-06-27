#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>  

#define N 100  //设置成100个点的集合
#define MAXDISTANCE 1000.0  //无穷大
#define ERROR -1			//输入错误
#define SORTX 0             //设置排序值为x
#define SORTY 1              //设置排序值为y
struct Point{
	double x;
	double y;
	struct Point *next;
};
//直接查找最近点对
double findNearest3Point(Point *P,int n);

//在集合p中查找value
bool findX(Point *p,double value,int n);

//在集合p中查找value
bool findY(Point *p,double value,int n);

//查找最近点对
double findNearest(Point *P,Point *X,Point *Y,int n);

//链表快速排序
void QuickSort(Point *header , Point *tail,int type);

//查找指定节点的前一个节点
Point * preNode(Point *header,Point *tail,Point *node);

//分割链表
Point * partiton(Point *header,Point *tail,int type);

//交换两个节点的值
void exchange(Point *i,Point *j);

//打印链表
void print_list(Point *head) ;

//只有两个节点时
void compare2points(Point *header,Point *tail,int type);