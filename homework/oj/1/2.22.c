/*
# 2.22-链表就地逆置
## 描述
试写一算法，实现单链表的就地逆置

## 输入
输入为给定链表的所有元素，以逗号分隔

## 输出
输出为链表逆置后的结果，以逗号分隔

## 样例1
### 输入
s,a,s,f,w,s,a,d,a,S

### 输出
S,a,d,a,s,w,f,s,a,s

*/

#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct __node {
    struct __node *next;
    ElemType data;
} LNode, LList;

int InitList(LList *head) {
    head->next = NULL;
    return 0;
}

int InsertList(LList *head, ElemType data) {
    LNode *n = (LNode *) malloc(sizeof(LNode));
    n->next = head->next;
    n->data = data;
    head->next = n;
    return 0;
}

int ReverseList(LList *head) {
    LNode *traverser = head->next, *pp=NULL, *p;
    while (traverser != NULL) {
        p = traverser;
        traverser = traverser->next;
        p->next = pp;
        pp = p;
    }
    head->next = p;
    return 0;
}

void PrintList(LList *head) {
    LNode *p = head->next;
    if (p == NULL)
        printf("NULL\n");
    while (p != NULL) {
        printf("%c%c", p->data, p->next==NULL?'\n':',');
        p = p->next;
    }
}

void input(LList *head) {
    char c=getchar(), sign=getchar();
    if (sign == ',') input(head);
    InsertList(head, c);
}

int main() {
    LList *list = (LList *) malloc(sizeof(LList));
    InitList(list);

    input(list);

    ReverseList(list);

    PrintList(list);
    return 0;
}