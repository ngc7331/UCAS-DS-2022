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