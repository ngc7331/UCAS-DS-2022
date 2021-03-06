/*
# 7.15-图的基本操作
## 描述
试在邻接矩阵存储结构上实现图的基本操作：InsertVex(G, v), InsertArc(G, v, w), DeleteVex(G,v)和DeleteArc(G,v,w)

## 输入
第一行输入顶点个数
第二行开始输入邻接矩阵，注意是无向图，顶点序号从0开始
第三行开始输入对图进行的操作，IV代表InsertVex，IA代表InsertArc，DV代表DeleteVex，DA代表DeleteArc，

## 输出
输出操作后的邻接矩阵

## 样例1
### 输入
4
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
DA 1 2
DV 0

### 输出
0 0 0
0 0 1
0 1 0

## 样例2
### 输入
3
0 1 0
1 0 1
0 1 0
IV 0
IA 0 1

### 输出
0 1 0 0
1 0 1 0
0 1 0 1
0 0 1 0

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 1000

typedef struct {
    int vexnum, edgenum;
    int vex[MAX_VERTEX_NUM];
    int adj[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
} MGraph;

void InsertVex(MGraph *g, int v) {
    for (int i=g->vexnum; i>v; i--)
        for (int j=0; j<g->vexnum; j++)
            g->adj[i][j] = g->adj[i-1][j];
    for (int i=0; i<g->vexnum+1; i++)
        for (int j=g->vexnum; j>v; j--)
            g->adj[i][j] = g->adj[i][j-1];
    g->vexnum ++;
    for (int i=0; i<g->vexnum; i++) {
        g->adj[i][v] = 0;
        g->adj[v][i] = 0;
    }
}

void DeleteVex(MGraph *g, int v) {
    for (int i=0; i<g->vexnum; i++)
        if (g->adj[v][i] == 1) g->edgenum --;
    for (int i=v; i<g->vexnum; i++)
        for (int j=0; j<g->vexnum; j++)
            g->adj[i][j] = g->adj[i+1][j];
    for (int i=0; i<g->vexnum; i++)
        for (int j=v; j<g->vexnum; j++)
            g->adj[i][j] = g->adj[i][j+1];
    for (int i=0; i<g->vexnum; i++) {
        g->adj[g->vexnum][i] = 0;
        g->adj[i][g->vexnum] = 0;
    }
    g->vexnum --;
}

void InsertArc(MGraph *g, int a, int b) {
    if (g->adj[a][b] == 1) return;
    g->edgenum ++;
    g->adj[a][b] = g->adj[b][a] = 1;
}

void DeleteArc(MGraph *g, int a, int b) {
    if (g->adj[a][b] == 0) return;
    g->edgenum --;
    g->adj[a][b] = g->adj[b][a] = 0;
}

void PrintMGraph(MGraph g) {
    for (int i=0; i<g.vexnum; i++)
        for (int j=0; j<g.vexnum; j++)
            printf("%d%c", g.adj[i][j], j==g.vexnum-1 ? '\n' : ' ');
}

int main(int argc, char *argv[]) {
    MGraph g;
    scanf("%d", &g.vexnum);
    for (int i=0; i<g.vexnum; i++) {
        for (int j=0; j<g.vexnum; j++) {
            scanf("%d", &g.adj[i][j]);
            if (g.adj[i][j]) g.edgenum ++;
        }
    }
    char type[2];
    int a, b;
    while (scanf("%s %d", type, &a) == 2) {
        if (type[0] == 'D' && type[1] == 'A') {
            scanf("%d", &b);
            DeleteArc(&g, a, b);
        }
        else if (type[0] == 'D' && type[1] == 'V')
            DeleteVex(&g, a);
        else if (type[0] == 'I' && type[1] == 'A') {
            scanf("%d", &b);
            InsertArc(&g, a, b);
        }
        else if (type[0] == 'I' && type[1] == 'V')
            InsertVex(&g, a);
    }
    PrintMGraph(g);
    return 0;
}