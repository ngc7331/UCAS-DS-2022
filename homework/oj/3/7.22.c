#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 1000
#define CACHESIZE 10000

typedef enum {
    False,
    True,
} Bool;

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
    g->edgenum = g->vexnum = 0;
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

Bool DFS(AGraph g, int a, int b) {
    NodeLink *p = g.v[a].first->next;
    while (p != NULL) {
        if (b == p->vindex || DFS(g, p->vindex, b))
            return True;
        p = p->next;
    }
    return False;
}

int main(int argc, char *argv[]) {
    AGraph g;
    initAGraph(&g, 1);
    scanf("%d\n", &g.vexnum);
    int a, b;
    int offset;
    char tmp[CACHESIZE], *tmpp = tmp;
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d-%d%n", &a, &b, &offset) == 2) {
        tmpp += offset + 1;
        insertDesList(g.v[a].first, b);
        g.edgenum ++;
    }
    scanf("%d,%d", &a, &b);
    printf("%s", DFS(g, a, b) ? "yes" : "no");
    return 0;
}