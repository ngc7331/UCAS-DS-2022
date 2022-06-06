/*
# 9.33-递归处理二叉排序树中关键字输出问题
## 描述
编写递归算法，从大到小输出给定二叉排序树中所有关键字不小于x的数据元素

## 输入
输入分为两部分：
第一行作为第一部分，就是给定的的二叉排序树各个数据元素
第二行作为第二部分，就是表示题目中指代的判断条件x元素

## 输出
将满足条件的数据元素从大到小输出一行

## 样例1
### 输入
-9 0 1 2 7 8 15 24 31 36 43 45
8

### 输出
45 43 36 31 24 15 8

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

void printDesBST(BST t) {
    if (t == NULL) return ;
    printDesBST(t->right);
    printf("%d ", t->data);
    printDesBST(t->left);
}

void searchAllGreater(BST t, int x) {
    if (t == NULL) return ;
    while (x > t->data && t->right != NULL && (t = t->right));
    // print all right child
    printDesBST(t->right);
    printf("%d ", t->data);
    // search in left child
    searchAllGreater(t->left, x);
}

int main(int argc, char *argv[]) {
    BST t;
    char tmp[CACHESIZE], *tmpp = tmp;
    int x, offset;
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &x, &offset) == 1) {
        tmpp += offset;
        insertBST(&t, x);
    }
    scanf("%d", &x);
    searchAllGreater(t, x);
    return 0;
}