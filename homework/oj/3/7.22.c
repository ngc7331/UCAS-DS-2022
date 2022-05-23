/*
# 7.22-判断路径是否存在
## 描述
基于图的深度优先搜索策略写一算法，判别以邻接表方式存储的有向图中是否存在由定点$v_i$到定点$v_j$的路径($i$ 不等于 $j$)注意：算法中涉及的图的基本操作必须在此存储结构上实现。

## 输入
输入第一行表示图中包含的节点数
第二行为图中的边
第三行为$i$和$j$

## 输出
输出从$v_i$到$v_j$是否存在路径，存在输出yes，不存在输出no。

## 样例1
### 输入
6
1-2,2-3,5-6,5-2,6-4,3-4
5,4

### 输出
yes

## 样例2
### 输入
4
1-2,2-3,1-3,2-4,4-2
3,1

### 输出
no

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