/*
# 7.42-Dijkstra算法
## 描述
以邻接表作为存储结构实现求源点到其余各顶点最短路径的Dijkstra算法

## 输入
第一行为顶点个数以及源点
第二行开始到结束为图中的边，以及边的权重

## 输出
输出源点到各个顶点的最短距离，按顶点序号从小到大排列

## 样例1
### 输入
4 1
1-2 1
1-4 3
2-3 1
3-4 2
3-1 5

### 输出
1,2,3

## 样例2
### 输入
6 1
1-2 7
1-3 9
1-6 14
3-6 2
2-3 10
2-4 15
3-4 11
6-5 9
5-4 6
3-5 7

### 输出
7,9,20,16,11

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 1000
#define INFINITE 999999

#define min(a,b) ((a)<(b)?(a):(b))

typedef enum {
    False,
    True,
} Bool;

typedef int ElemType;
typedef struct __node {
    int vindex;
    int weight;
    struct __node *next;
} WNodeLink;

typedef struct {
    int vexnum, edgenum, kind;
    struct {
        ElemType vertex;
        int dist;
        WNodeLink *first;
    } v[MAX_VERTEX_NUM];
} WAGraph;

typedef struct {
    int a, b;
    int weight;
} Edge;

void initWAGraph(WAGraph *g, int kind) {
    g->kind = kind;
    g->edgenum = g->vexnum = 0;
    for (int i=0; i<MAX_VERTEX_NUM; i++) {
        g->v[i].first = (WNodeLink *) malloc(sizeof(WNodeLink));
        g->v[i].first->next = NULL;
        g->v[i].dist = INFINITE;
    }
}

void insertWAscList(WNodeLink *l, int vindex, int weight) {
    WNodeLink *p=l->next, *pp = l;
    while (p != NULL && p->weight < weight) {
        p = p->next;
        pp = pp->next;
    }
    pp->next = (WNodeLink *) malloc(sizeof(WNodeLink));
    pp->next->vindex = vindex;
    pp->next->weight = weight;
    pp->next->next = p;
}

void createArc(WAGraph g, int a, int b, int weight) {
    insertWAscList(g.v[a].first, b, weight);
    if (g.kind == 0)
        insertWAscList(g.v[b].first, a, weight);
}

int getClosestVex(WAGraph g, int visited[]) {
    int closest_vex = 0;
    int min_dist = INFINITE;
    for (int i=1; i<=g.vexnum; i++) {
        // for all unvisited vex, check their distance
        if (visited[i] == 0 && g.v[i].dist < min_dist) {
            min_dist = g.v[i].dist;
            closest_vex = i;
        }
    }
    return closest_vex;
}

void updateDist(WAGraph *g, int start) {
    WNodeLink *p = g->v[start].first->next;
    while (p != NULL) {
        g->v[p->vindex].dist = min(g->v[p->vindex].dist, g->v[start].dist + p->weight);
        p = p->next;
    }
}

void Dijkstra(WAGraph *g, int start) {
    int visited[MAX_VERTEX_NUM] = {0};
    int visited_cnt = 1;
    g->v[start].dist = 0;
    visited[start] = 1;
    while (visited_cnt < g->vexnum) {
        updateDist(g, start);
        start = getClosestVex(*g, visited);
        if (start == 0) return ;
        visited[start] = 1;
        visited_cnt ++;
    }
}

int main(int argc, char *argv[]) {
    WAGraph g;
    int start, a, b, weight;
    initWAGraph(&g, 1);
    scanf("%d %d\n", &g.vexnum, &start);
    while (scanf("%d-%d %d\n", &a, &b, &weight) == 3)
        createArc(g, a, b, weight);

    Dijkstra(&g, start);

    for (int i=1; i<=g.vexnum; i++) {
        if (i == start) continue;
        printf("%d%c", g.v[i].dist, i==g.vexnum || i==g.vexnum-1 && start==g.vexnum ? '\n' : ',');
    }
    return 0;
}