/*
# 7.14-构造邻接表
## 描述
编写算法，由依次输入的顶点数目、弧的数目、各顶点的信息和各条弧的信息建立有向图的邻接表。

## 输入
第一行输入图的顶点和弧的数目，逗号分隔
第二行输入每个弧的两个顶点信息，**注意顶点序号可能从0开始（若输入的顶点序号中没有0，则默认从1开始）**

## 输出
输出邻接链表，不同链表按照表头结点的节点序号从小到大排列，每个链表中的节点按照节点的序号从大到小排列，

## 样例1
### 输入
4,6
1-4,2-1,1-3,2-4,2-3,3-4

### 输出
1 4,3
2 4,3,1
3 4
4

## 样例2
### 输入
6,5
1-2,1-3,1-4,1-5,1-6

### 输出
1 6,5,4,3,2
2
3
4
5
6

## 样例3
### 输入
5,12
0-3,0-1,1-4,1-2,1-0,2-4,2-3,2-1,3-2,3-0,4-2,4-1

### 输出
0 3,1
1 4,2,0
2 4,3,1
3 2,0
4 2,1

*/

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