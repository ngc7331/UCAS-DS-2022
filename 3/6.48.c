/*
# 6.48-求距离两个二叉树节点最近的共同祖先
## 描述
已知在二叉树中，*root为根节点，*p和*q为二叉树中的两个节点，试编写求距离它们最近的共同祖先的算法。
其中，建立二叉树的节点输入按照先序序列依次读入，比如一个二叉树的示意图如下：

*image deleted*


它的先序序列为124^^5^^3^^,其中^表示搜索到空节点。

## 输入
输入分为两行：
第一行将初始化二叉树各个节点的先序序列作为输入；
第二行将输入两个需要搜索距离它们最近的共同祖先的节点字符，中间以空格隔开。
**注意节点的类型是字符**

## 输出
输出则是距离给定的两个节点最近的共同祖先的节点字符。

## 样例1
### 输入
124^^5^^3^^
4 3

### 输出
1

## 样例2
### 输入
124^^57^^8^^36^9^^^
6 9

### 输出
3

*/

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    UNDERFLOW = -3,
    OVERFLOW,
    INFEASIBLE,
    ERROR,
    OK
} Status;

#define CACHESIZE 10000

typedef char TElemType;
typedef struct __tnode {
    TElemType e;
    struct __tnode *parent, *left, *right;
} tnode, *BiTree;

void InitTree(BiTree *t) {
    if (*t == NULL) *t = (BiTree) malloc(sizeof(tnode));
    (*t)->parent = (*t)->left = (*t)->right = NULL;
}

void BuildTree(char **s, BiTree t) {
    if (**s != '^' && **s != EOF) {
        InitTree(&(t->left));
        t->left->parent = t;
        t->left->e = *((*s)++);
        BuildTree(s, t->left);
    } else (*s)++;
    if (**s != '^' && **s != EOF) {
        InitTree(&(t->right));
        t->right->parent = t;
        t->right->e = *((*s)++);
        BuildTree(s, t->right);
    } else (*s)++;
}

BiTree locateTree(BiTree t, TElemType e) {
    if (t == NULL) return NULL;
    if (t->e == e) return t;
    BiTree lres = locateTree(t->left, e);
    if (lres == NULL) return locateTree(t->right, e);
    else return lres;
}

#define STACKSIZE 1000
typedef BiTree ElemType;

typedef struct {
    int top;
    ElemType base[STACKSIZE];
} SSqStack;

Status InitStack(SSqStack *s) {
    s->top = 0;
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
    char tmp[CACHESIZE], *tmpp = tmp+1;
    char p, q;
    fgets(tmp, CACHESIZE, stdin);
    scanf("\n%c %c", &p, &q);
    BiTree t; InitTree(&t);
    t->e = tmp[0];
    BuildTree(&tmpp, t);

    BiTree pn = locateTree(t, p), pnn;
    BiTree qn = locateTree(t, q), qnn;
    SSqStack pr, qr;
    InitStack(&pr);
    InitStack(&qr);
    while (pn != NULL) {
        Push(&pr, pn);
        pn = pn->parent;
    }
    while (qn != NULL) {
        Push(&qr, qn);
        qn = qn->parent;
    }

    do {
        pnn = pn;
        qnn = qn;
        Pop(&pr, &pn);
        Pop(&qr, &qn);
    } while (pn == qn);

    if ((pnn == pn || pnn == qn) && pnn != t)
        printf("%c", pnn->parent->e);
    else
        printf("%c", pnn->e);

    return 0;
}