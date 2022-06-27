// bucket sort

#include <stdio.h>
#include <stdlib.h>

#define BUCKETNUM 400
#define MAXDATA 10000

typedef struct __node {
    int data;
    struct __node *next;
} Node, *List;

Node *newNode() {
    Node *n = (Node *) malloc(sizeof(Node));
    n->next = NULL;
    return n;
}

void insertAscList(List l, int x) {
    List n = newNode();
    n->data = x;
    while (l->next && l->next->data < x) l = l->next;
    n->next = l->next;
    l->next = n;
    return ;
}

void printList(List l) {
    while ((l=l->next))
        printf("%d ", l->data);
}

int main(int argc, char *argv[]) {
    Node count[BUCKETNUM];
    for (int i=0; i<BUCKETNUM; i++)
        count[i].next = NULL;
    int x;
    while (scanf("%d", &x) == 1) insertAscList(&count[x/(MAXDATA/BUCKETNUM)], x);
    for (int i=0; i<BUCKETNUM; i++) {
        printList(&count[i]);
    }
    return 0;
}
