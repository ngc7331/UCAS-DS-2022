#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100
#define INCRESIZE 100

typedef char ElemType;

typedef struct {
    int top;
    ElemType *base;
    int size;
} SqStack;

int InitStack(SqStack *s) {
    s->base = (ElemType *) malloc(sizeof(ElemType) * INITSIZE);
    if (s->base == NULL) return 1;
    s->size = INITSIZE;
    s->top = 0;
    return 0;
}

int IncreStack(SqStack *s) {
    s->base = (ElemType *) realloc(s, sizeof(ElemType) * (s->size + INCRESIZE));
    if (s->base == NULL) return 1;
    s->size += INCRESIZE;
    return 0;
}

int GetLen(SqStack *s) {
    return s->top;
}

int GetTop(SqStack *s, ElemType *e) {
    if (s->top == 0) return 1;
    *e = s->base[s->top-1];
    return 0;
}

int Push(SqStack *s, ElemType e) {
    if (s->top >= s->size)
        if (IncreStack(s) == 1) return 1;
    s->base[s->top++] = e;
    return 0;
}

int Pop(SqStack *s, ElemType *e) {
    if (s->top == 0) return 1;
    *e = s->base[--s->top];
    return 0;
}

int IsStackEmpty(SqStack *s) {
    return s->top == 0;
}

#define SYMBOLNUM 6

char SYMBOL_LIST[SYMBOLNUM] = {
    '+', '-', '*', '/', '(', ')'
};

char PRIOR[SYMBOLNUM][SYMBOLNUM] = {
    '>','>','<','<','<','>',
    '>','>','<','<','<','>',
    '>','>','>','>','<','>',
    '>','>','>','>','<','>',
    '<','<','<','<','<','=',
    '>','>','>','>',' ','>',
};

int getSymbolOP(char c) {
    for (int i=0; i<SYMBOLNUM; i++)
        if (SYMBOL_LIST[i] == c) return i;
    return -1;
}

int isSymbol(char c) {
    return getSymbolOP(c) != -1;
}

int getPrior(char a, char b) {
    return PRIOR[getSymbolOP(a)][getSymbolOP(b)];
}

int justPop(SqStack *s, char c) {
    char d;
    Pop(s, &d);
    printf("%c", d);
    if (GetTop(s, &d)) {
        return 0; // stack is empty
    }
    switch (getPrior(d, c)) {
        case '<':
            break;
        case '>':
            justPop(s, c);
            break;
        case '=':
            Pop(s, &d);
            break;
    }
    return 0;
}

int main() {
    SqStack sym;
    InitStack(&sym);
    char c, d;
    while((c=getchar()) != '\n' && c!=EOF) {
        if (!isSymbol(c)) {
            printf("%c", c);
            continue;
        }
        // 处理符号
        if (GetTop(&sym, &d)) {
            Push(&sym, c);
            continue;
        }
        switch (getPrior(d, c)) {
            case '<':
                Push(&sym, c);
                break;
            case '>':
                justPop(&sym, c);
                if (c != ')') Push(&sym, c);
                break;
            case '=':
                Pop(&sym, &d);
        }
    }
    while (!IsStackEmpty(&sym)) {
        Pop(&sym, &d);
        printf("%c", d);
    }
    return 0;
}
