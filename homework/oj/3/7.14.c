#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 1000

typedef int ElemType;
typedef struct __node {
    int vindex;
    struct __node *next;
} NodeLink;

typedef struct {
    int vexnum, edgenum, kind;
    struct {
        ElemType vertex;
        NodeLink *first;
    } v[MAX_VERTEX_NUM];
} AGraph;

void initAGraph(AGraph *g, int kind) {
    g->kind = kind;
    for (int i=0; i<MAX_VERTEX_NUM; i++) {
        g->v[i].first = (NodeLink *) malloc(sizeof(NodeLink));
        g->v[i].first->next = NULL;
    }
}

void insertDesList(NodeLink *l, int vindex) {
    NodeLink *p=l->next, *pp = l;
    while (p != NULL && p->vindex > vindex) {
        p = p->next;
        pp = pp->next;
    }
    pp->next = (NodeLink *) malloc(sizeof(NodeLink));
    pp->next->vindex = vindex;
    pp->next->next = p;
}

void printList(NodeLink *l) {
    l = l->next;
    while (l != NULL) {
        printf("%d%c", l->vindex, l->next==NULL?'\n':',');
        l = l->next;
    }
}

void printAGraph(AGraph g) {
    for (int i=1; i<=g.vexnum; i++) {
        printf("%d%c", i, g.v[i].first->next==NULL?'\n':' ');
        printList(g.v[i].first);
    }
}

int main(int argc, char *argv[]) {
    AGraph g;
    initAGraph(&g, 1);
    scanf("%d,%d", &g.vexnum, &g.edgenum);
    int has_zero = 0;
    for (int i=0; i<g.edgenum; i++) {
        int a, b;
        scanf("%d-%d", &a, &b);
        getchar(); // clear ','
        if (a == 0 || b == 0) has_zero = 1;
        insertDesList(g.v[a].first, b);
    }

    printAGraph(g);

    return 0;
}