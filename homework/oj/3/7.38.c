/*
# 7.38-有向无环图转逆波兰式
## 描述
一个四则运算算术表达式以有向无环图的邻接表方式存储，每个操作数原子都由单个字母表示。写一个算法输出其逆波兰表达式。

## 输入
输入第一行为图的顶点个数n
第二行开始的n行输入每个节点，第一个元素为节点的字符，第二个元素开始为对应邻接表的节点

## 输出
输出逆波兰式

## 样例1
### 输入
3
+ 1 2
b
a

### 输出
ab+

## 样例2
### 输入
5
* 2 1
+ 4 3
c
a
b

### 输出
ab+c*

## 样例3
### 输入
7
- 2 1
* 6 5
+ 4 3
c
d
a
b

### 输出
ab*cd+-

*/

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