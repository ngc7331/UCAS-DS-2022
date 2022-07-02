/*
# 3.18-括号配对
## 描述
试写一个判别表达式中开,闭括号是否配对出现的算法。
比如:'(a+b(c-d))'是配对出现的,而'(d-e))'不是配对出现的。

## 输入
表达式,如:'a+b(c-d)’

## 输出
表达式中的括号是否配对出现,是则输出1,否则输出0

## 样例1
### 输入
(a+b(c-d))

### 输出
1

## 样例2
### 输入
(d-e))

### 输出
0

*/

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

//4. 元素入栈
int Push(SqStack *s, ElemType e) {
    if (s->top >= s->size)
        if (IncreStack(s) == 1) return 1;
    s->base[s->top++] = e;
    return 0;
}

//5. (栈顶)元素出栈
int Pop(SqStack *s, ElemType *e) {
    if (s->top == 0) return 1;
    *e = s->base[--s->top];
    return 0;
}

//6. 判断栈是否为空
int IsStackEmpty(SqStack *s) {
    return s->top == 0;
}

int main() {
    SqStack s;
    InitStack(&s);
    char c, d;
    int flag = 1;
    while((c=getchar()) != '\n' && c!=EOF) {
        switch (c) {
            case '(':
            case '[':
            case '{':
                Push(&s, c);
                break;
            case ')':
                if (Pop(&s, &d) || d!='(')
                    flag = 0;
                break;
            case ']':
                if (Pop(&s, &d) || d!='[')
                    flag = 0;
                break;
            case '}':
                if (Pop(&s, &d) || d!='{')
                    flag = 0;
                break;
        }
        if (flag == 0) break;
    }
    if (!IsStackEmpty(&s)) flag = 0;
    printf("%d\n", flag);
    return 0;
}
