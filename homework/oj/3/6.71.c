#include <stdio.h>

#define TREEMAXNODE 1000

typedef struct {
    char e;
    int left, right;
} tnode;

typedef struct {
    tnode node[TREEMAXNODE];
    int size;
} SqBiTree;

void PrintHyphen(int num) {
    while (num--) printf("-");
}

void PrintRecessedTable(SqBiTree t, int i, int depth) {
    // arg: t is a child-sibling tree
    while (i != -1) {
        PrintHyphen(depth); printf("%c\n", t.node[i].e);
        PrintRecessedTable(t, t.node[i].left, depth+1);
        i = t.node[i].right;
    }
}

int main(int argc, char *argv[]) {
    char e;
    int left, right;
    SqBiTree t;
    t.size = 0;
    while (scanf("%c %d %d\n", &e, &left, &right) == 3) {
        t.node[t.size+1].e = e;
        t.node[t.size+1].left = left;
        t.node[t.size+1].right = right;
        t.size ++;
    }

    PrintRecessedTable(t, 1, 0);

    return 0;
}