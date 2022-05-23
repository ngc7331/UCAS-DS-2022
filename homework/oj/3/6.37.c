/*
# 6.37 先序遍历的非递归形式
## 描述
使用栈的基本操作写出二叉树先序遍历的非递归形式的算法。

## 输入
输入为 $n$ 行，表示 $n$ 个节点的信息。
第 $i， i\in[1, n]$ 行为节点 $i$ 的信息，包括一个字符 $c$ 和两个数字 $p$ 和 $q$， 这表示第 $i$ 个节点的内容为字符 $c$, 其左孩子为 $p$, 右孩子为 $q$。空节点使用 -1 表示。

## 输出
输出为一行，按照先序遍历的顺序打印出二叉树节点的内容（即每个节点所对应的字符 $c$）, 并以空格隔开。

## 样例1
### 输入
A -1 -1

### 输出
A

## 样例2
### 输入
A 2 -1
B -1 -1

### 输出
A B

## 样例3
### 输入
A 2 4
B -1 3
C -1 -1
D -1 -1

### 输出
A B C D

*/

#include <stdio.h>

#define TREEMAXNODE 1000

typedef enum {
    ERROR = -1,
    OK
} Status;

typedef struct {
    char e;
    int left, right;
} tnode;

typedef struct {
    tnode node[TREEMAXNODE];
    int size;
} SqBiTree;

#define STACKSIZE 1000
typedef tnode ElemType;

typedef struct {
    int top;
    ElemType base[STACKSIZE];
} SSqStack;

Status InitStack(SSqStack *s) {
    s->top = 0;
    return OK;
}

Status GetTop(SSqStack *s, ElemType *e) {
    if (s->top == 0) return ERROR;
    *e = s->base[s->top];
    return OK;
}

Status Push(SSqStack *s, ElemType e) {
    if (s->top >= STACKSIZE-1) return ERROR;
    s->base[++s->top] = e;
    return OK;
}

Status Pop(SSqStack *s, ElemType *e) {
    if (s->top == 0) return ERROR;
    *e = s->base[s->top--];
    return OK;
}

int isStackEmpty(SSqStack s) {
    return s.top == 0;
}

int main(int argc, char *argv[]) {
    int i=1;
    char tmp[1000];
    char e;
    int left, right;
    SqBiTree t;
    t.size = 0;
    fgets(tmp, 1000, stdin);
    while (sscanf(tmp, "%c %d %d", &e, &left, &right) == 3) {
        t.node[i].e = e;
        t.node[i].left = left;
        t.node[i].right = right;
        t.size ++;
        i ++;
        fgets(tmp, 1000, stdin);
    }

    SSqStack s; InitStack(&s);
    Push(&s, t.node[1]);
    while (!isStackEmpty(s)) {
        tnode n;
        Pop(&s, &n);
        if (n.right != -1) Push(&s, t.node[n.right]);
        if (n.left != -1) Push(&s, t.node[n.left]);
        printf("%c%c", n.e, isStackEmpty(s)?'\n':' ');
    }
    return 0;
}