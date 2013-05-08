/** 
* ������Ŀ����� 
* author :blue 
* data   :2010-4-6 
*/  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
//����ڵ�  
struct node {  
    int data;  
    struct node *next;  
};  
//�����������  
void QListSort(struct node **head, struct node *end);
//��ӡ����  
void print_list(struct node *head) {  
    struct node *p;  
    for (p = head; p != NULL; p = p->next) {  
        printf("%d ", p->data);  
    }  
    printf("/n");  
}  
int main(void) {  
    struct node *head;  
    struct node *p;  
    int i = 0;  
    /** 
    * ��ʼ������ 
    */  
    head = (struct node*)malloc(sizeof(struct node));  
    head->next = NULL;  
    head->data = 0;  
    srand((unsigned)time(NULL));  
    for (i = 1; i < 11; ++i) {  
        p = (struct node*)malloc(sizeof(struct node));  
        p->data = rand() % 100 + 1;  
        p->next = head->next;  
        head->next = p;  
    }  
      
    print_list(head);  
    printf("---------------------------------/n");  
    QListSort(&head, NULL);  
    print_list(head);  
    return 0;  
}  
  
void QListSort(struct node **head, struct node *end) {  
    struct node *right;  
    struct node **left_walk, **right_walk;  
    struct node *pivot, *old;  
    int count, left_count, right_count;  
    if (*head == end)  
        return;  
    do {  
        pivot = *head;  
        left_walk = head;  
        right_walk = &right;  
        left_count = right_count = 0;  
        //ȡ��һ���ڵ���Ϊ�ȽϵĻ�׼��С�ڻ�׼����������������У�  
        //���ڻ�׼�����ұߵ���������  
        for (old = (*head)->next; old != end; old = old->next) {  
            if (old->data < pivot->data) {   //С�ڻ�׼,���뵽�����������,�����Ƚ�  
                ++left_count;  
                *left_walk = old;            //�Ѹýڵ���뵽��ߵ������У�  
                left_walk = &(old->next);  
            } else {                         //���ڻ�׼,���뵽�ұߵ������������Ƚ�  
                ++right_count;  
                *right_walk = old;             
                right_walk = &(old->next);  
            }  
        }  
        //�ϲ�����  
        *right_walk = end;       //����������  
        *left_walk = pivot;      //�ѻ�׼������ȷ��λ����  
        pivot->next = right;     //������ϲ�  
        //�Խ�С����������п����򣬽ϴ����������е�������  
        if(left_walk > right_walk) {  
            QListSort(&(pivot->next), end);  
            end = pivot;  
            count = left_count;  
        } else {  
            QListSort(head, pivot);  
            head = &(pivot->next);  
            count = right_count;  
        }  
    } while (count > 1);   
}  