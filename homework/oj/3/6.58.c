#include <stdio.h>

int mode = 0;

#define TREEMAXNODE 1000
#define CACHESIZE 10000

typedef struct {
    int vexnum;
    int root;
    int R[TREEMAXNODE], L[TREEMAXNODE];
} Tree;

int input(int array[], int root) {
    char tmp[CACHESIZE], *tmpp = tmp;
    int offset;
    int i = root;
    // input
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &array[i++], &offset) == 1)
        tmpp += offset;
    return i - 2 - root;
}

void inputTree(Tree *t, int root) {
    t->root = root;
    t->vexnum = input(t->L, root);
    input(t->R, root);
    if (t->L[root] == root) {
        mode = 1;
        for (int i=root-1; i<root+t->vexnum; i++) {
            t->L[i] = t->L[i+1];
            t->R[i] = t->R[i+1];
        }
        t->root --;
    }
}

void inorderThreading(Tree *t, int p, int prev, int succ) {
    if (t->L[p] <= t->root)
        t->L[p] = prev;
    else
        inorderThreading(t, t->L[p], prev, p);
    if (t->R[p] <= t->root)
        t->R[p] = succ;
    else
        inorderThreading(t, t->R[p], p, succ);
}

int getLeft(Tree t) {
    int i = t.root + 1;
    while (t.L[i] != 0)
        i = t.L[i];
    return i;
}

void inorderPrint(Tree t) {
    // t must be a threading tree
    // find the most left node
    int i = getLeft(t);
    // print
    while (i != 0) {
        printf("%d%c", i, t.R[i]!=0 ? ' ' : '\n');
        i = t.R[i];
    }
}

void insert(Tree *p, int n, Tree x) {
    // copy x to p
    for (int i=x.root+mode; i<=x.root+x.vexnum; i++) {
        p->L[i] = x.L[i];
        p->R[i] = x.R[i];
    }
    p->vexnum += x.vexnum;
    // insert
    int l = getLeft(*p);
    p->L[l] = x.root + 1;
    p->R[x.root + 1] = l;
    p->L[n] = x.root + 1;
}

int main(int argc, char *argv[]) {
    Tree p, x;
    int n;
    inputTree(&p, 0);
    scanf("%d\n", &n);
    inputTree(&x, p.vexnum+1);
    inorderThreading(&p, p.root+1, 0, 0);
    inorderThreading(&x, x.root+1, 0, 0);
    insert(&p, n, x);
    inorderPrint(p);
    return 0;
}