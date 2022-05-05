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