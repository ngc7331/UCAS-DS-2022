/*
# 6.58-线索二叉树插入
## 描述
试写一个算法，在中序全线索二叉树的节点*p之下，插入一棵以节点*x为根，只有左子树的中序全线索二叉树，使*x为根的二叉树成为*p的左子树。若*p原来有左子树，则令它为*x的右子树。完成插入之后的二叉树应保持全线索化的特性。
例如，给定二叉树如下，*p=2

*image deleted*


若以节点*x=7为根的二叉树如下，

*image deleted*


则插入后的二叉树如下，

*image deleted*

## 输入
首先输入*p所在的二叉树，使用**6.43**中的表示法表示。
然后输入*p节点
最后输入以*x为根的二叉树，同样使用**6.43**中的表示法表示，注意此时的根节点不一定为1，此时数组中的下标和节点的对应关系如下所示。
例如，例子中的*x所在二叉树的表示为
L=7 8 0
R=7 0 0
此时，设偏移量o为根节号减1，即o=7-1=6，节点7的左右子节点对应L[7-6]=8，R[7-6]=8，节点8的左右子节点对应L[8-6]=0，R[8-6]=0。

## 输出
输出插入之后树的中序遍历序列

## 样例1
### 输入
1 2 4 0 0 0
1 3 5 0 0 0
2
7 8 0
7 0 0

### 输出
8 7 4 2 5 1 3

## 样例2
### 输入
1 0 0
1 2 0
1
3 4 5 0 0
3 0 6 0 0

### 输出
5 4 6 3 1 2

*/

#include <stdio.h>

int mode = 0;

#define TREEMAXNODE 1000
#define CACHESIZE 10000

typedef struct {
    int vexnum;
    int root;
    int R[TREEMAXNODE], L[TREEMAXNODE];
} Tree;

int input(int array[], int root) {
    char tmp[CACHESIZE], *tmpp = tmp;
    int offset;
    int i = root;
    // input
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &array[i++], &offset) == 1)
        tmpp += offset;
    return i - 2 - root;
}

void inputTree(Tree *t, int root) {
    t->root = root;
    t->vexnum = input(t->L, root);
    input(t->R, root);
    if (t->L[root] == root) {
        mode = 1;
        for (int i=root-1; i<root+t->vexnum; i++) {
            t->L[i] = t->L[i+1];
            t->R[i] = t->R[i+1];
        }
        t->root --;
    }
}

void inorderThreading(Tree *t, int p, int prev, int succ) {
    if (t->L[p] <= t->root)
        t->L[p] = prev;
    else
        inorderThreading(t, t->L[p], prev, p);
    if (t->R[p] <= t->root)
        t->R[p] = succ;
    else
        inorderThreading(t, t->R[p], p, succ);
}

int getLeft(Tree t) {
    int i = t.root + 1;
    while (t.L[i] != 0)
        i = t.L[i];
    return i;
}

void inorderPrint(Tree t) {
    // t must be a threading tree
    // find the most left node
    int i = getLeft(t);
    // print
    while (i != 0) {
        printf("%d%c", i, t.R[i]!=0 ? ' ' : '\n');
        i = t.R[i];
    }
}

void insert(Tree *p, int n, Tree x) {
    // copy x to p
    for (int i=x.root+mode; i<=x.root+x.vexnum; i++) {
        p->L[i] = x.L[i];
        p->R[i] = x.R[i];
    }
    p->vexnum += x.vexnum;
    // insert
    int l = getLeft(*p);
    p->L[l] = x.root + 1;
    p->R[x.root + 1] = l;
    p->L[n] = x.root + 1;
}

int main(int argc, char *argv[]) {
    Tree p, x;
    int n;
    inputTree(&p, 0);
    scanf("%d\n", &n);
    inputTree(&x, p.vexnum+1);
    inorderThreading(&p, p.root+1, 0, 0);
    inorderThreading(&x, x.root+1, 0, 0);
    insert(&p, n, x);
    inorderPrint(p);
    return 0;
}