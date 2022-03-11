#include "../ds.h"
#include <stdlib.h>

#define INITSIZE 100
#define INCRESIZE 100

#ifndef __ELEMTYPE_DEF
#define __ELEMTYPE_DEF
typedef int ElemType;
#endif // __ELEMTYPE_DEF

typedef struct {
    int top;
    ElemType *base;
    int size;
} SqStack;

//1. 构造一个空栈S
Status InitStack(SqStack *s) {
    s->base = (ElemType *) malloc(sizeof(ElemType) * INITSIZE);
    if (s->base == NULL) return ERROR;
    s->size = INITSIZE;
    s->top = 0;
    return OK;
}

//1.1. 扩容栈S
Status IncreStack(SqStack *s) {
    s->base = (ElemType *) realloc(s, sizeof(ElemType) * (s->size + INCRESIZE));
    if (s->base == NULL) return ERROR;
    s->size += INCRESIZE;
    return OK;
}

//2. 取栈的长度
int GetLen(SqStack *s) {
    return s->top;
}

//3. 查看栈顶元素
Status GetTop(SqStack *s, ElemType *e) {
    if (s->top == 0) return ERROR;
    *e = s->base[s->top-1];
    return OK;
}

//4. 元素入栈
Status Push(SqStack *s, ElemType e) {
    if (s->top >= s->size)
        if (IncreStack(s) == ERROR) return ERROR;
    s->base[s->top++] = e;
    return OK;
}

//5. (栈顶)元素出栈
Status Pop(SqStack *s, ElemType *e) {
    if (s->top == 0) return ERROR;
    *e = s->base[--s->top];
    return OK;
}

//6. 判断栈是否为空
int IsStackEmpty(SqStack *s) {
    return s->top == 0;
}

//7. 遍历栈，从栈顶到栈底依次对每个元素调用visit()
Status StackTraverse(SqStack *s, void visit(ElemType *e)) {
    if (s->top == 0) return ERROR;
    for (int i=s->top-1; i>=0; i--)
        visit(&s->base[i]);
    return OK;
}
