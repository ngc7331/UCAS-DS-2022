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