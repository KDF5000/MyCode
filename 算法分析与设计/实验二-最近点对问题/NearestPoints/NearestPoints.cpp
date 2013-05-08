#include "NearestPoints.h"
#define N 15
//�ȽϾ������������
double findNearest3Point(Point *P,int n)
{
	if(P==NULL)
		return MAXDISTANCE;
	Point *cur = P;
	Point *next =NULL;
	double distance = MAXDISTANCE;
	double currentDis = MAXDISTANCE ;
	while(cur->next!=NULL)
	{
		next = cur->next;
		while(next!=NULL)
		{
			currentDis = pow(pow((cur->x - next->x),2)+pow(cur->y - next->y,2) , 0.5);
			if(currentDis<distance)
				distance = currentDis;
			next = next->next;
		}
		cur = cur->next;
	}
	return distance;
}
//�ڼ���p�в���value
bool findX(Point *p,double value,int n)
{
	int i=1;
	Point *cur = p;
	while(i<=n && cur!=NULL )
	{
		if(cur->x==value)
			return true;
		i++;
		cur = cur->next;
	}
	return false;
}
//�ڼ���p�в���value
bool findY(Point *p,double value,int n)
{
	int i=1;
	Point *cur = p;
	while(i<=n && cur!=NULL )
	{
		if(cur->y==value)
			return true;
		i++;
		cur = cur->next;
	}
	return false;
}

double findNearest(Point *P,Point *X,Point *Y,int n)
{
	if(n<=1)
	{
		printf("���������������㣡");
		return ERROR;
	}
	if(n<=3)
		return findNearest3Point(P,n);
	//������P�ֳ����������ּ���
	Point *PL,*PR;
	PL = PR = P;
	int i=1; //���ڼ���
	while(i<=n/2)
	{
		PR = PR->next;
		i++;
	}
	//����XL,XR
	Point *XL,*XR,*newNode,*pL,*pR;
	XL = XR = pL =pR = NULL;
	Point *pX = X;
	while(pX!=NULL)
	{
		if(findX(PL,pX->x,n/2))
		{
			if(XL==NULL)
			{
				XL = (struct Point *)malloc(sizeof(struct Point));
				XL->x = pX->x;
				XL->y = pX->y;
				XL->next = NULL;
				pL = XL;
			}
			else
			{
				newNode = (struct Point *)malloc(sizeof(struct Point));
				newNode->x = pX->x;
				newNode->y = pX->y;
				newNode->next = NULL;
				pL->next = newNode;
				pL = pL->next;
			}
		}
		else
		{
			if(XR==NULL)
			{
				XR = (struct Point *)malloc(sizeof(struct Point));
				XR->x = pX->x;
				XR->y = pX->y;
				XR->next = NULL;
				pR = XR;
			}
			else
			{
				newNode = (struct Point *)malloc(sizeof(struct Point));
				newNode->x = pX->x;
				newNode->y = pX->y;
				newNode->next = NULL;
				pR->next = newNode;
				pR = newNode;
			}
		}
		pX = pX->next;
	}
	//����YL,YR
	Point *YL,*YR;
	YL = YR = pL =pR = NULL;
	Point *pY = Y;
	while(pY!=NULL)
	{
		if(findY(PL,pY->y,n-n/2))
		{
			if(YL==NULL)
			{
				YL = (struct Point *)malloc(sizeof(struct Point));
				YL->x = pY->x;
				YL->y = pY->y;
				YL->next = NULL;
				pL = YL;
			}
			else
			{
				newNode = (struct Point *)malloc(sizeof(struct Point));
				newNode->x = pY->x;
				newNode->y = pY->y;
				newNode->next = NULL;
				pL->next = newNode;
				pL = pL->next;
			}
		}
		else
		{
			if(YR==NULL)
			{
				YR = (Point *)malloc(sizeof(Point));
				YR->x = pY->x;
				YR->y = pY->y;
				YR->next = NULL;
				pR = YR;
			}
			else
			{
				newNode = (struct Point *)malloc(sizeof(struct Point));
				newNode->x = pY->x;
				newNode->y = pY->y;
				newNode->next = NULL;
				pR->next = newNode;
				pR = pR->next;
			}
		}
		pY = pY->next;
	}
	double QL = findNearest(PL,XL,YL,n/2);
	double QR = findNearest(PR,XR,YR,n-n/2);
	double Q = QL < QR ? QL : QR;
	//����Y~
	Point *y ,*curY;
	y = curY = NULL;
	Point *pmid = P;
	Point *yQ = Y;
	//�ҳ��ֽ紦��Xֵ
	i=1;
	while(i<n/2)
	{
		pmid = pmid->next;
		i++;
	}
	//����2Q��Χxֵ
	double xQ0 = pmid->x-Q;
	double xQ1 = pmid->x+Q;
	int Rangecount=0;
	//���ֽ���2Q��Χ�ĵ��ҳ��ŵ�y����
	while(yQ!=NULL)
	{
		if(yQ->x>=xQ0 && yQ->x<=xQ1)
		{
			if(y==NULL)
			{
				y = (struct Point *)malloc(sizeof(struct Point));
				y->x = yQ->x;
				y->y = yQ->y;
				y->next = NULL;
				curY = y;
				Rangecount++;
			}
			else
			{
				newNode = (struct Point *)malloc(sizeof(struct Point));
				newNode->x = yQ->x;
				newNode->y = yQ->y;
				newNode->next = NULL;
				curY->next = newNode;
				curY = curY->next;
				Rangecount++;
			}
		}
		yQ = yQ->next;
	}
	//����ֽ��߸�����������
	double Qdistance = findNearest3Point(y,Rangecount);
	return (Qdistance < Q ? Qdistance:Q );
}
//�����������
void QuickSort(Point *header , Point *tail,int type)
{
	Point *pivot;
	if(header==NULL || tail==NULL)
	{
		return ;
	}
	if(header->next==tail)
	{
		compare2points(header,tail,type);
		return ;
	}
	if(header!= tail && tail->next!=header)
	{
		pivot = partiton(header,tail,type); 
		//printf("pivot=%f\n",pivot->x);
		//print_list(header);
		QuickSort(header,preNode(header,tail,pivot),type);
		QuickSort(pivot->next,tail,type);
	}
}
//����ָ���ڵ��ǰһ���ڵ�
Point * preNode(Point *header,Point *tail,Point *node)
{
	Point *p = header;
	while(p!=tail)
	{
		if(p->next==node)
			return p;
		p = p->next;
	}
	return NULL;
}
//�ָ�����
Point * partiton(Point *header,Point *tail,int type)
{

	int pivot;
	Point *i,*j;
	i = j =header;
	switch(type)
	{
	case SORTX:
		pivot = tail->x;
		for(;j->next!=tail->next;j = j->next)
		{
			//���С����Ԫ���������
			if(j->x<pivot)
			{
				exchange(i,j);
				i = i->next;
			}
		}
	    exchange(i,tail);
		break;
	case SORTY:
		pivot = tail->y;
		for(;j->next!=tail->next;j = j->next)
		{
			//���С����Ԫ���������
			if(j->y<pivot)
			{
			 	exchange(i,j);
				i = i->next;
			}
		}
		exchange(i,tail);
		break;
	default:
		break;
	}
	return i;
}
//���������ڵ��ֵ
void exchange(Point *i,Point *j)
{
	double tempX = 0.0;
	double tempY = 0.0;
	tempX = i->x;
	tempY = i->y;
	i->x = j->x;
	i->y = j->y;
	j->x = tempX;
	j->y = tempY;	
}
//ֻ�������ڵ�ʱ
void compare2points(Point *header,Point *tail,int type)
{
	switch(type)
	{
	case SORTX:
		if(header->x > tail->x) 
			exchange(header,tail);
		break;
	case SORTY:
		if(header->y > tail->y)
			exchange(header,tail);
		break;
	default:
		break;
	}
}
//��ӡ����
void print_list(Point *head) 
{  
    Point *p;  
    for (p = head; p != NULL; p = p->next) 
	{  
        printf("(%4.2lf,%4.2lf) ", p->x,p->y);  
		//printf("%2.0lf ",p->x);
    }  
    printf("\n");  
} 
void main()
{
	Point *header,*X,*Y,*newNode;
	header = X = Y = newNode = NULL;
    Point *p1,*p2;  
    int i = 0;  
	srand((unsigned)time(NULL));  
	//����һ����Լ�
	for(i=0;i<N;i++)
	{
		if(NULL==header)
		{
			header = (struct Point *)malloc(sizeof(struct Point));
			header->next = NULL;
			header->x = rand()%100+1;
			header->y = rand()%100+1;
			p1 = header;
		}
		else{
			newNode = (struct Point *)malloc(sizeof(struct Point));
			newNode->next = NULL;
			newNode->x = rand()%100+1;
			newNode->y = rand()%100+1;
			p1->next = newNode;
			p1 = p1->next;
		}
	}
	print_list(header);  
	//����Լ����Ƶ�һ�ݵ�X
	for(p1=header;p1!=NULL;p1 = p1->next)
	{
		if(NULL==X)
		{
			X = (struct Point *)malloc(sizeof(struct Point));
			X->next = NULL;
			X->x = p1->x;
			X->y = p1->y;
			p2 = X;
		}
		else{
			newNode = (struct Point *)malloc(sizeof(struct Point));
			newNode->next = NULL;
			newNode->x = p1->x;
			newNode->y = p1->y;
			p2->next = newNode;
			p2 = p2->next;
		}
	}
	//Ԥ����X
	QuickSort(X, p2,SORTX);  
	print_list(X);  
	//����Լ�����һ�ݵ�Y
	for(p1=header;p1!=NULL;p1 = p1->next)
	{
		if(NULL==Y)
		{
			Y = (struct Point *)malloc(sizeof(struct Point));
			Y->next = NULL;
			Y->x = p1->x;
			Y->y = p1->y;
			p2 = Y;
		}else{
			newNode = (struct Point *)malloc(sizeof(struct Point));
			newNode->next = NULL;
			newNode->x = p1->x;
			newNode->y = p1->y;
			p2->next = newNode;
			p2 = p2->next;
		}
	}
	//Ԥ����Y
	QuickSort(Y, p2,SORTY);  
	print_list(Y); 
    printf("result= %lf\n",findNearest(header,X,Y,N));
    /** 
    * ��ʼ������ 
    */  
   /* Point *head = (struct Point*)malloc(sizeof(struct Point));  
    head->next = NULL;  
    head->x = 0; 
	head->y= 0;
	p1 = head;
    srand((unsigned)time(NULL));  
    for (i = 1; i < 11; ++i) {  
        p2 = (struct Point*)malloc(sizeof(struct Point));  
        p2->x = rand()%100 + 1;  
		p2->y = rand()%100 + 1;  
		p2->next = NULL;
        p1->next = p2;
		p1 = p2;
    }  
      
    print_list(head);  
    printf("---------------------------------\n");  
    QuickSort(head, p2,SORTX);  
    print_list(head);  */
}