/*
# 7.27-判断无向图是否存在简单路径
## 描述
采用邻接表存储结构，编写一个判别无向图中任意给定的两个顶点之间是否存在一条长度为k的简单路径的算法。
注：一条路径为简单路径指的是其顶点序列中不含有重现的顶点

## 输入
第一行为顶点个数和k，用逗号分隔
第二行为起点和终点
第三行为图中的边

## 输出
输出是否存在满足条件的简单回路，存在输出yes，不存在输出no

## 样例1
### 输入
4,4
1,4
1-2,2-3,3-4,4-2,1-3

### 输出
no

## 样例2
### 输入
4,2
1,4
1-2,2-3,3-1,2-4

### 输出
yes

*/

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

void createArc(AGraph g, int a, int b) {
    insertDesList(g.v[a].first, b);
    if (g.kind == 0)
        insertDesList(g.v[b].first, a);
}

Bool DFS(AGraph g, int a, int b, int depth, int k, int visited[]) {
    if (visited[a] == 1 || depth > k) return False;
    if (a == b && depth == k) return True;
    visited[a] = 1;
    NodeLink *p = g.v[a].first->next;
    while (p != NULL) {
        if (DFS(g, p->vindex, b, depth+1, k, visited))
            return True;
        p = p->next;
    }
    visited[a] = 0;
    return False;
}

int main(int argc, char *argv[]) {
    AGraph g;
    int a, b, k, from, to;
    int offset;
    int visited[MAX_VERTEX_NUM] = {0};
    char tmp[CACHESIZE], *tmpp = tmp;
    initAGraph(&g, 0);
    scanf("%d,%d\n", &g.vexnum, &k);
    scanf("%d,%d\n", &from, &to);
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d-%d%n", &a, &b, &offset) == 2) {
        tmpp += offset + 1;
        createArc(g, a, b);
        g.edgenum ++;
    }
    printf("%s", DFS(g, from, to, 0, k, visited) ? "yes" : "no");
    return 0;
}