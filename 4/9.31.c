/*
# 9.31-二叉排序树
## 描述
试写一个判定给定二叉树是否为二叉排序树的算法，设词二叉树以二叉链表为存储结构，且树中节点的关键字均不同

## 输入
输入每行为二叉树的节点，分为三个部分，分别为当前节点包含的数字，左节点序号和右节点序号（序号从0开始），如果没有左节点或右节点则输出-1

## 输出
输出为当前二叉排序树是否为二叉排序树，是则输出1，否则输出0

## 样例1
### 输入
8 1 2
3 3 4
10 -1 -1
1 -1 -1
6 -1 -1

### 输出
1

*/

#include <stdio.h>

#define TREESIZE 1000
#define INFINITE 9999999
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

typedef enum {
    False,
    True,
} Bool;

typedef struct {
    int data;
    int left, right;
} node;

int tmaxcache[TREESIZE];
int tmax(node t[], int i) {
    if (i == -1) return -INFINITE;
    if (tmaxcache[i] == -INFINITE)
        tmaxcache[i] = max(tmax(t, t[i].left), max(tmax(t, t[i].right), t[i].data));
    return tmaxcache[i];
}

int tmincache[TREESIZE];
int tmin(node t[], int i) {
    if (i == -1) return INFINITE;
    if (tmincache[i] == INFINITE)
        tmincache[i] = min(tmin(t, t[i].left), min(tmin(t, t[i].right), t[i].data));
    return tmincache[i];
}

void initCache() {
    for (int i=0; i<TREESIZE; i++) {
        tmaxcache[i] = -INFINITE;
        tmincache[i] = INFINITE;
    }
}

Bool isBST(node t[], int i) {
    if (i == -1) return True;
    return isBST(t, t[i].left) && isBST(t, t[i].right) &&
           t[i].data > tmax(t, t[i].left) && t[i].data < tmin(t, t[i].right);
}

int main(int argc, char *argv[]) {
    node t[TREESIZE];
    initCache();
    for (int i=0; scanf("%d %d %d", &t[i].data, &t[i].left, &t[i].right) == 3; i++);
    printf("%d", isBST(t, 0));
    return 0;
}