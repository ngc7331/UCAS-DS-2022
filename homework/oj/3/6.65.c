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