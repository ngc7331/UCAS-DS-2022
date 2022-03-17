#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// THIS MIGHT NOT SATISFY REQUIREMENT:
// __node.i should be removed?

typedef struct __node {
    struct __node *prior, *next;
    ElemType data;
    int freq, i;
} DLNode, *DLList;

DLList InitList() {
    DLList head = (DLList) malloc(sizeof(DLNode));
    if (head == NULL) return NULL;
    head->prior = head->next = head;
    return head;
}

int InsertList(DLList head, ElemType data) {
    DLNode *n = (DLNode *) malloc(sizeof(DLNode));
    if (n == NULL) return 1;
    n->prior = head;
    n->next = head->next;
    head->next->prior = n;
    head->next = n;
    n->data = data;
    n->freq = n->i = 0;
    return 0;
}

int LOCATE(DLList L, int x, int i) {
    DLNode *n = L->next;
    while (n != L && n->data != x) n = n->next;
    if (n == L) return -1; // 未定位到，即 x \notin list

    n->freq ++; // 频度++
    if (n->i == 0) n->i = i;

    // 找 n 入表位置
    DLNode *p = n->prior;
    while (p != L && p->freq < n->freq) p = p->prior;
    while (p != L && p->freq == n->freq && p->i > n->i) p = p->prior;

    // n 出列表
    n->prior->next = n->next;
    n->next->prior = n->prior;

    // n 入列表 (p后)
    n->prior = p;
    n->next = p->next;
    p->next->prior = n;
    p->next = n;
    return 0;
}

void input(DLList list, int n) {
    int data;
    if (n <= 0) return ;
    scanf("%d", &data);
    input(list, n-1);
    InsertList(list, data);
}

void PrintList(DLList head) {
    DLNode *p = head->next;
    if (p == head)
        printf("NULL\n");
    while (p != head) {
        printf("%d ", p->data);
        p = p->next;
    }
}

int main() {
    DLList list = InitList();
    int data, n, i=0;
    scanf("%d", &n);
    input(list, n);
    while (scanf("%d", &data) == 1)
        LOCATE(list, data, ++i);
    PrintList(list);
    return 0;
}