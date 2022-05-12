#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 1000
#define CACHESIZE 10000

#define max(a,b) ((a)>(b)?(a):(b))

typedef enum {
    False,
    True,
} Bool;

typedef char ElemType;
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

Bool isSymbol(char c) {
    return (
        c == '+' ||
        c == '-' ||
        c == '*' ||
        c == '/' ||
        c == '^' ||
        c == '%'
    );
}

void initAGraph(AGraph *g, int kind) {
    g->kind = kind;
    g->edgenum = g->vexnum = 0;
    for (int i=0; i<MAX_VERTEX_NUM; i++) {
        g->v[i].first = (NodeLink *) malloc(sizeof(NodeLink));
        g->v[i].first->next = NULL;
    }
}

void insertList(NodeLink *l, int vindex) {
    NodeLink *p = (NodeLink *) malloc(sizeof(NodeLink));
    p->next = l->next;
    p->vindex = vindex;
    l->next = p;
}

void createArc(AGraph g, int a, int b) {
    insertList(g.v[a].first, b);
    if (g.kind == 0)
        insertList(g.v[b].first, a);
}

void RPN(AGraph g, int i) {
    if (g.v[i].first->next != NULL) {
        RPN(g, g.v[i].first->next->vindex);
        RPN(g, g.v[i].first->next->next->vindex);
    }
    printf("%c", g.v[i].vertex);
}

int main(int argc, char *argv[]) {
    AGraph g;
    int a, b;
    initAGraph(&g, 1);
    scanf("%d\n", &g.vexnum);
    for (int i=0; i<g.vexnum; i++) {
        g.v[i].vertex = getchar();
        if (isSymbol(g.v[i].vertex)) {
            scanf("%d %d", &a, &b);
            createArc(g, i, a);
            createArc(g, i, b);
        }
        getchar(); // remove '\n'
    }

    RPN(g, 0);

    return 0;
}