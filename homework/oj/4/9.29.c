#include <stdio.h>
#include <stdlib.h>

#define CACHESIZE 10000

typedef enum {
    False,
    True,
} Bool;

typedef struct __node{
    int key;
    struct __node *next;
} node, *list;

node *newNode() {
    return (node *) malloc(sizeof(node));
}

void insertTailList(list *lp, int k) {
    if (*lp == NULL) {
        list l = *lp = newNode();
        l->next = l;
        l->key = k;
    } else {
        list p = *lp, n = newNode();
        n->key = k;
        n->next = *lp;
        while (p->next != *lp) p = p->next;
        p->next = n;
    }
}

list h, t;
Bool search(int k) {
    if (k == t->key)
        return True;
    else if (k < t->key) {
        t = h;
        while (t->next != h && t->key != k) t = t->next;
        return t->key == k;
    } else {
        list tmp = t;
        while (t->next != tmp && t->key != k) t = t->next;
        return t->key == k;
    }
}

int main(int argc, char *argv[]) {
    list l = NULL;
    char tmp[CACHESIZE], *tmpp=tmp;
    int k, offset;
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &k, &offset) == 1) {
        tmpp += offset;
        insertTailList(&l, k);
    }
    h = t = l;
    tmpp = tmp;
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &k, &offset) == 1) {
        tmpp += offset;
        printf("%d ", search(k));
    }
    return 0;
}