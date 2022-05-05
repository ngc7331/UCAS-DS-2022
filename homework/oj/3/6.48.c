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