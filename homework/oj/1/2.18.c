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

int ListDelete(LList *head, int n) {
    LNode *p = head;
    while (n-- > 0 && p != NULL) p = p->next;
    if (p == NULL || p->next == NULL) {
        p = NULL;
        return 0;
    }
    LNode *tmp = p->next;
    p->next = p->next->next;
    free(tmp);
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
    int n;

    fgets(tmp, 1000, stdin);
    sinput(tmp, list);
    scanf("%d", &n);

    ListDelete(list, n);

    PrintList(list);
    return 0;
}