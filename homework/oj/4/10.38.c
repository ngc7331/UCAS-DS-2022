#include <stdio.h>
#include <stdlib.h>

#define MAXSEG 1000

typedef struct __node {
    int data;
    struct __node *next;
} Node, *List;

Node *newNode() {
    Node *n = (Node *) malloc(sizeof(Node));
    n->next = NULL;
    return n;
}

void insertList(List l, int x) {
    List n = newNode();
    n->data = x;
    while (l->next != NULL) l = l->next;
    l->next = n;
    return ;
}

void merge(List *l1, int len1, List l2, int len2) {
    List p = *l1;
    List r = newNode();
    int i, j;
    for (i=0, j=0; i<len1 && j<len2; ){
        if (p->data < l2->data) {
            insertList(r, p->data);
            i++;
            p = p->next;
        }
        else {
            insertList(r, l2->data);
            j++;
            l2 = l2->next;
        }
    }
    for (; i<len1; i++, p=p->next)
        insertList(r, p->data);
    for (; j<len2; j++, l2=l2->next)
        insertList(r, l2->data);
    *l1 = r->next;
}

void mergeSort(List l) {
    // 划分归并段
    int len = 0, last = l->next->data;
    List S[MAXSEG];
    int L[MAXSEG] = {0};
    List p = S[0] = l->next;
    while (p) {
        if (p->data < last)
            S[++len] = p, L[len] = 0;
        last = p->data;
        L[len]++;
        p = p->next;
    }
    S[++len] = NULL;

    // 合并
    int step = 1;
    while (step < len) {
        for (int i=0; i<len; i+=2*step) {
            if (i+step >= len) break;
            merge(&S[i], L[i], S[i+step], L[i+step]);
            L[i] = L[i] + L[i+step];
        }
        step *= 2;
    }
    l->next = S[0];
}

void printList(List l) {
    while ((l=l->next))
        printf("%d%c", l->data, l->next ? ' ' : '\n');
}

int main(int argc, char *argv[]) {
    int x, len;
    scanf("%d", &len);
    List l = newNode();
    while (len --) {
        scanf("%d", &x);
        insertList(l, x);
    }
    mergeSort(l);
    printList(l);
    return 0;
}