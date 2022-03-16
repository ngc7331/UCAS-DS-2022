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