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

void insertList(List l, int x) {
    List n = newNode();
    n->data = x;
    n->next = l->next;
    l->next = n;
    return ;
}

void selectSort(List l) {
    Node *tail = l;
    while (tail && tail->next) {
        Node *p = tail->next, *min = tail->next;
        Node *pp = tail, *pmin = tail;
        while (p) {
            if (p->data < min->data) {
                pmin = pp;
                min = p;
            }
            pp = pp->next;
            p = p->next;
        }
        pmin->next = min->next;
        min->next = tail->next;
        tail->next = min;
        tail = min;
    }
}

void printList(List l) {
    while ((l=l->next))
        printf("%d%c", l->data, l->next ? ' ' : '\n');
}

int main(int argc, char *argv[]) {
    int x;
    Node l = {0, NULL};
    while (scanf("%d", &x) == 1)
        insertList(&l, x);
    selectSort(&l);
    printList(&l);
    return 0;
}