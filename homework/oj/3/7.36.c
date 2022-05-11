#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 1000
#define CACHESIZE 10000

#define max(a,b) ((a)>(b)?(a):(b))

typedef int ElemType;
typedef struct __node {
    int vindex;
    struct __node *next;
} NodeLink;

typedef struct {
    int vexnum, edgenum, kind;
    struct {
        int MPL;
        ElemType vertex;
        NodeLink *first;
    } v[MAX_VERTEX_NUM];
} AGraph;

void initAGraph(AGraph *g, int kind) {
    g->kind = kind;
    g->edgenum = g->vexnum = 0;
    for (int i=0; i<MAX_VERTEX_NUM; i++) {
        g->v[i].MPL = 0;
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

void createArc(AGraph g, int a, int b) {
    insertDesList(g.v[a].first, b);
    if (g.kind == 0)
        insertDesList(g.v[b].first, a);
}

int DFS(AGraph g, int i, int visited[]) {
    if (visited[i] == 1) return 0;
    if (g.v[i].MPL != 0) return g.v[i].MPL;
    visited[i] = 1;
    NodeLink *p = g.v[i].first->next;
    int m = 0;
    while (p != NULL) {
        m = max(m, DFS(g, p->vindex, visited)+1);
        p = p->next;
    }
    visited[i] = 0;
    g.v[i].MPL = m;
    return m;
}

int main(int argc, char *argv[]) {
    AGraph g;
    int a, b, offset;
    char tmp[CACHESIZE], *tmpp = tmp;
    initAGraph(&g, 1);
    scanf("%d\n", &g.vexnum);
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d-%d%n", &a, &b, &offset) == 2) {
        tmpp += offset + 1;
        createArc(g, a, b);
        g.edgenum ++;
    }
    int visited[g.vexnum+1];
    for (int i=1; i<=g.vexnum; i++) {
        printf("%d%c", DFS(g, i, visited), i==g.vexnum ? '\n' : ',');
    }
    return 0;
}