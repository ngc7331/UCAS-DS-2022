#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

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

int ListDeleteRange(LList *head, int mink, int maxk) {
    LNode *p=head->next, *pp=head;
    while (p != NULL && p->data < maxk) {
        if (p->data <= mink) pp = pp->next;
        p = p->next;
    }
    LNode *tmp = pp->next;
    pp->next = p;
    while (tmp != p) {
        LNode *ttmp = tmp;
        tmp = tmp->next;
        free(ttmp);
    }
    return 0;
}

void PrintList(LList *head) {
    LNode *p = head->next;
    if (p == NULL)
        printf("NULL\n");
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
}

void sinput(char *line, LList *head) {
    int data, offset;
    if (sscanf(line, "%d%n", &data, &offset) != 1)
        return ;
    sinput(line+offset, head);
    InsertList(head, data);
}

int main() {
    LList *list = (LList *) malloc(sizeof(LList));
    InitList(list);

    char tmp[1005];
    int mink, maxk;

    fgets(tmp, 1000, stdin);
    sinput(tmp, list);
    scanf("%d %d", &mink, &maxk);

    ListDeleteRange(list, mink, maxk);

    PrintList(list);
    return 0;
}