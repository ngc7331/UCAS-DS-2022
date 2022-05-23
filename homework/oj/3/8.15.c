#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FREE,
    USED
} TAG;

typedef struct __node {
    TAG tag;
    int start;
    int size;
    struct __node *next;
} word, *Space;

Space newSpace(TAG tag, int start, int size) {
    Space n = (Space) malloc(sizeof(word));
    n->tag = tag;
    n->start = start;
    n->size = size;
    n->next = NULL;
    return n;
}

void insertList(Space *lp, Space n) {
    if (*lp == NULL || (*lp)->start > n->start + n->size) {
        n->next = *lp;
        *lp = n;
    } else {
        Space l = *lp, p = l->next, pp = l;
        while (p != NULL && p->start < n->start + n->size) {
            p = p->next;
            pp = pp->next;
        }
        pp->next = n;
        n->next = p;
    }
}

void printList(Space l) {
    if (l == NULL)
        printf("0 0 0\n");
    else {
        while (l != NULL) {
            printf("0 %d %d\n", l->start, l->size);
            l = l->next;
        }
    }
}

int main(int argc, char *argv[]) {
    Space l = NULL;
    int highbound, lowbound, blocksize;
    TAG t;
    scanf("%d %d %d\n", &highbound, &lowbound, &blocksize);
    int start=highbound, size=0;
    for (int i=0; i<(lowbound-highbound)/blocksize; i++) {
        scanf("%d", (int *)&t);
        switch (t) {
        case FREE:
            size += blocksize;
            break;
        case USED:
            if (size)
                insertList(&l, newSpace(FREE, start, size));
            size = 0;
            start = highbound + (i+1) * blocksize;
            break;
        }
    }
    if (start == highbound) {
        insertList(&l, newSpace(FREE, start, lowbound-highbound));
    }
    printList(l);
    return 0;
}