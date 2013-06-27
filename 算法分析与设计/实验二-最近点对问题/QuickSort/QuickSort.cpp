/** 
* 单链表的快排序 
* author :blue 
* data   :2010-4-6 
*/  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
//链表节点  
struct node {  
    int data;  
    struct node *next;  
};  
//链表快排序函数  
void QListSort(struct node **head, struct node *end);
//打印链表  
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
    * 初始化链表 
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
        //取第一个节点作为比较的基准，小于基准的在左面的子链表中，  
        //大于基准的在右边的子链表中  
        for (old = (*head)->next; old != end; old = old->next) {  
            if (old->data < pivot->data) {   //小于基准,加入到左面的子链表,继续比较  
                ++left_count;  
                *left_walk = old;            //把该节点加入到左边的链表中，  
                left_walk = &(old->next);  
            } else {                         //大于基准,加入到右边的子链表，继续比较  
                ++right_count;  
                *right_walk = old;             
                right_walk = &(old->next);  
            }  
        }  
        //合并链表  
        *right_walk = end;       //结束右链表  
        *left_walk = pivot;      //把基准置于正确的位置上  
        pivot->next = right;     //把链表合并  
        //对较小的子链表进行快排序，较大的子链表进行迭代排序。  
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