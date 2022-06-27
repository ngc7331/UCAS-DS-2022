#include <stdio.h>
#include <stdlib.h>

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
        printf("%d%c", l->data, l->next ? ' ' : '\n');
}

int main(int argc, char *argv[]) {
    int len, x;
    Node l = {0, NULL};
    scanf("%d", &len);
    while (len--) {
        scanf("%d", &x);
        insertAscList(&l, x);
    }
    printList(&l);
    return 0;
}