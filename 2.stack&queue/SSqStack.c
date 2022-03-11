#include "../ds.h"
#include <stdlib.h>

#define STACKSIZE 100

#ifndef __ELEMTYPE_DEF
#define __ELEMTYPE_DEF
typedef int ElemType;
#endif // __ELEMTYPE_DEF

typedef struct {
    int top;
    ElemType base[STACKSIZE];
} SSqStack;

//1. 构造一个空栈S
Status InitStack(SSqStack *s) {
    s->top = 0;
    return OK;
}

//2. 取栈的长度
int GetLen(SSqStack *s) {
    return s->top-1;
}

//3. 查看栈顶元素
Status GetTop(SSqStack *s, ElemType *e) {
    if (s->top == 0) return ERROR;
    *e = s->base[s->top];
    return OK;
}

//4. 元素入栈
Status Push(SSqStack *s, ElemType e) {
    if (s->top >= STACKSIZE-1) return ERROR;
    s->base[++s->top] = e;
    return OK;
}

//5. (栈顶)元素出栈
Status Pop(SSqStack *s, ElemType *e) {
    if (s->top == 0) return ERROR;
    *e = s->base[s->top--];
    return OK;
}

//6. 判断栈是否为空
int IsStackEmpty(SSqStack *s) {
    return s->top == 0;
}

//7. 遍历栈，从栈顶到栈底依次对每个元素调用visit()
Status StackTraverse(SSqStack *s, void visit(ElemType *e)) {
    if (s->top == 0) return ERROR;
    for (int i=s->top; i>=0; i--)
        visit(&s->base[i]);
    return OK;
}
