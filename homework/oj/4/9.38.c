/*
# 9.38 合并二叉排序树
## 描述
试写一算法，将两棵二叉排序树合并成一棵二叉排序树

## 输入
按照先序序列，分两行输入两棵二叉排序树各结点（结点值大于0），其中-1表示取消建立子树结点。

## 输出
按照中序序列输出合并后的二叉排序树。

## 样例1
### 输入
12 8 4 -1 -1 10 -1 -1 16 13 -1 -1 18 -1 -1
17 6 2 -1 -1 9 -1 -1 24 19 -1 -1 26 -1 -1

### 输出
2 4 6 8 9 10 12 13 16 17 18 19 24 26

*/

#include <stdio.h>
#include <stdlib.h>

#define CACHESIZE 10000

typedef struct __node {
    int data;
    struct __node *left, *right;
} node, *BST;

node *newNode(int x) {
    node *n = (node *) malloc(sizeof(node));
    n->left = n->right = NULL;
    n->data = x;
    return n;
}

void insertBST(BST *tp, int x) {
    if (*tp == NULL) {
        *tp = newNode(x);
    } else {
        BST t = *tp;
        while (x < t->data && t->left != NULL && (t = t->left) ||
               x > t->data && t->right != NULL && (t = t->right));
        if (x < t->data) t->left = newNode(x);
        else t->right = newNode(x);
    }
}

int buildBST(char **buffer, BST t) {
    // assert t != NULL
    int x, offset;
    sscanf(*buffer, "%d%n", &x, &offset);
    *buffer += offset;
    if (x == -1) return 1;  // x == -1 取消建立结点
    t->data = x;
    t->left = newNode(0);
    if (buildBST(buffer, t->left)) t->left = NULL;
    t->right = newNode(0);
    if (buildBST(buffer, t->right)) t->right = NULL;
    return 0;
}

void printAscBST(BST t) {
    if (t == NULL) return ;
    printAscBST(t->left);
    printf("%d ", t->data);
    printAscBST(t->right);
}

void mergeBST(BST t1, BST t2) {
    // assert t1 != NULL
    // 中序遍历t2结点，逐个插入t1
    if (t2 == NULL) return ;
    mergeBST(t1, t2->left);
    insertBST(&t1, t2->data);
    mergeBST(t1, t2->right);
}

int main(int argc, char *argv[]) {
    BST t1 = newNode(0), t2 = newNode(0);
    char *buffer = malloc(CACHESIZE);
    fgets(buffer, CACHESIZE, stdin);
    buildBST(&buffer, t1);
    fgets(buffer, CACHESIZE, stdin);
    buildBST(&buffer, t2);
    mergeBST(t1, t2);
    printAscBST(t1);
    return 0;
}
