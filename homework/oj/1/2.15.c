/*
# 2.15-链表合并
## 描述
已知指针ha和hb分别指向两个单链表的头结点，并且已知两个链表的长度分别为m和n。试写一算法将这两个链表连接在一起（即令其中一个表的首元节点连在另一个表的最后一个节点之后），假设指针hc指向连接后的链表的头结点，并要求算法以尽可能短的时间完成链接运算。

## 输入
输入包括三行，第一行是两个链表的长度m和n，第二行和第三行分别为链表ha和hb中的元素，以空格分隔。

## 输出
输出合并后的链表hc，元素以空格分隔

## 样例1
### 输入
5 3
1 2 3 4 5
1 2 3

### 输出
1 2 3 1 2 3 4 5

*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct __node {
    struct __node *next;
    ElemType data;
} LNode, LList;

int InitList(LList *head) {
    head->next = NULL;
}

int InsertList(LList *head, ElemType data) {
    LNode *n = (LNode *) malloc(sizeof(LNode));
    n->next = head->next;
    n->data = data;
    head->next = n;
    return 0;
}

void PrintList(LList *head) {
    LNode *p = head->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
}

void input(LList *head, int len) {
    if (len <= 0) return ;
    int data;
    scanf("%d", &data);
    input(head, len-1);
    InsertList(head, data);
}

void extend(LList *a, LList *b) {
    LNode *p = a;
    while (p->next != NULL) p = p->next;
    p->next = b->next;
}

int main() {
    int m, n;
    LList a, b;
    InitList(&a);
    InitList(&b);
    scanf("%d %d", &m, &n);
    input(&a, m);
    input(&b, n);

    LList *ha = &a, *hb = &b;
    if (m>n) extend(hb, ha);
    else extend(ha, hb);

    if (m>n) PrintList(hb);
    else PrintList(ha);
    return 0;
}