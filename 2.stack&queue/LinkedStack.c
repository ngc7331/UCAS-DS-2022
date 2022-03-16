#include "../ds.h"
#include <stdlib.h>

#ifndef __ELEMTYPE_DEF
#define __ELEMTYPE_DEF
typedef int ElemType;
#endif // __ELEMTYPE_DEF

// TODO

struct __node {
    ElemType data;
    struct __node *prev, *next;
};

typedef struct {
    struct __node *head, *top;
    int len;
} LinkedStack;

//1. 构造一个空栈S
Status InitStack(LinkedStack *s) {
    s->head = (struct __node *) malloc(sizeof(struct __node));
    s->head->next = s->head->prev = NULL;
    s->top = NULL;
    s->len = 0;
    return OK;
}

//2. 取栈的长度
int GetLen(LinkedStack *s) {
    return s->len;
}

//3. 查看栈顶元素
Status GetTop(LinkedStack *s, ElemType *e) {
    if (s->len == 0) return ERROR;
    *e = s->top->data;
    return OK;
}

//4. 元素入栈
Status Push(LinkedStack *s, ElemType e) {
    struct __node *p = (struct __node *) malloc(sizeof(struct __node));
    s->base[++s->top] = e;
    return OK;
}

//5. (栈顶)元素出栈
Status Pop(LinkedStack *s, ElemType *e) {
    if (s->top == 0) return ERROR;
    *e = s->base[s->top--];
    return OK;
}

//6. 判断栈是否为空
int IsStackEmpty(LinkedStack *s) {
    return s->len == 0;
}

//7. 遍历栈，从栈顶到栈底依次对每个元素调用visit()
Status StackTraverse(LinkedStack *s, void visit(ElemType *e)) {
    if (s->top == 0) return ERROR;
    struct __node *p = s->top;
    while (p != s->head) {
        visit(p->data);
        p = p->prev;
    }
    return OK;
}
