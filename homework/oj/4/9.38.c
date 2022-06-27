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
