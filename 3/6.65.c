/*
# 6.65-建立二叉树链表
## 描述
已知一棵二叉树的前序序列和中序序列分别存于两个一维数组中，试编写算法建立该二叉树的二叉链表，然后输出该二叉链表的后序序列。
比如一棵二叉树链表的示意图如下：

*image deleted*

前序序列数组为：[1,2,4,5,3]
中序序列数组为：[4,2,5,1,3]

## 输入
输入分为两行，
第一行输入为二叉树的先序序列；
第二行输入为二叉树的中序序列。

## 输出
输出为二叉树的后序序列

## 样例1
### 输入
12453
42513

### 输出
45231

## 样例2
### 输入
ABDHEICFJKG
DHBEIAJFKCG

### 输出
HDIEBJKFGCA

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TREEMAXNODE 1000
#define CACHESIZE 10000

typedef char ElemType;
typedef struct __LBiTNode {
    ElemType e;
    struct __LBiTNode *left, *right;
} LBiTNode, *LBiTree;

LBiTree CreateLBiTNode() {
    LBiTree n = (LBiTree) malloc(sizeof(LBiTNode));
    n->left = n->right = NULL;
    n->e = 0;
    return n;
}

char *subStr(char *s, int a, int b) {
    // returns s[a:b], including s[a], excluding s[b];
    char *sub = (char *) malloc(b-a+1);
    for (int i=a, j=0; i<b; i++, j++)
        sub[j] = s[i];
    sub[b-a] = '\0';
    return sub;
}

void BuildBiTree(LBiTree t, char *pt, char *it) {
    // arg: string a is the preorder traversal, b is the inorder traversal
    t->e = pt[0];
    int len = strlen(pt);
    // build left child
    int left_length = 0;
    while (it[left_length] != t->e) left_length ++;
    if (left_length == 0) t->left = NULL;
    else {
        char *npt = subStr(pt, 1, 1+left_length);
        char *nit = subStr(it, 0, left_length);
        t->left = CreateLBiTNode();
        BuildBiTree(t->left, npt, nit);
        free(npt);
        free(nit);
    }
    // build right child
    int right_length = len - left_length - 1;
    if (right_length == 0) t->right = NULL;
    else {
        char *npt = subStr(pt, 1+left_length, len);
        char *nit = subStr(it, 1+left_length, len);
        t->right = CreateLBiTNode();
        BuildBiTree(t->right, npt, nit);
        free(npt);
        free(nit);
    }
}

void PostTraverse(LBiTree t) {
    if (t == NULL) return;
    PostTraverse(t->left);
    PostTraverse(t->right);
    printf("%c", t->e);
}

int main(int argc, char *argv[]) {
    char pt[CACHESIZE], it[CACHESIZE];
    scanf("%s", pt);
    scanf("%s", it);
    LBiTree t = CreateLBiTNode();
    BuildBiTree(t, pt, it);
    PostTraverse(t);
    return 0;
}