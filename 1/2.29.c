/*
# 2.29-修改链表
## 描述
已知A，B和C为三个递增有序的线性表，现要求对A表做如下操作：删去那些既在B表中出现又在C表中出现的元素。试对顺序表编写实现上述操作的算法。

## 输入
输入包含三行，分别为ABC三个线性表中的元素，以逗号分隔

## 输出
输出操作之后的A表中的元素

## 样例1
### 输入
a,b,c,d,e,f,g
b,e,g,h,h
c,e,g,h

### 输出
a,b,c,d,f

*/

#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct __node {
    struct __node *next;
    ElemType data;
} LNode, *LList;

LList InitList() {
    LList head = (LList) malloc(sizeof(LNode));
    head->next = NULL;
    return head;
}

int InsertList(LList head, ElemType data) {
    LNode *n = (LNode *) malloc(sizeof(LNode));
    n->next = head->next;
    n->data = data;
    head->next = n;
    return 0;
}

int ModList(LList A, LList B, LList C) {
    LNode *pa = A->next, *pb = B->next, *pc = C->next;
    LNode *ppa = A;
    while (pa != NULL) {
        while (pb != NULL && pb->data < pa->data) pb = pb->next;
        while (pc != NULL && pc->data < pa->data) pc = pc->next;
        if (pb == NULL || pc == NULL)
            return 0;
        if (pa->data == pb->data && pa->data == pc->data) {
            LNode *tmp = pa;
            ppa->next = pa->next;
            pa = pa->next;
            free(tmp);
        }
        else {
            pa = pa->next;
            ppa = ppa->next;
        }
    }
    return 0;
}

void PrintList(LList head) {
    LNode *p = head->next;
    if (p == NULL)
        printf("NULL\n");
    while (p != NULL) {
        printf("%c%c", p->data, p->next==NULL?'\n':',');
        p = p->next;
    }
}

void input(LList head) {
    char c=getchar(), sign=getchar();
    if (sign == ',') input(head);
    InsertList(head, c);
}

int main() {
    LList A = InitList(), B = InitList(), C = InitList();
    input(A);
    input(B);
    input(C);

    ModList(A, B, C);

    PrintList(A);
    return 0;
}