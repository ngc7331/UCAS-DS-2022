/*
# 3.17-逆序列
## 描述
试写一算法，识别依次读入的一个以@为结束符的字符序列是否为形如“序列1&序列2”模式的字符序列。其中序列1和序列2中都不包含字符“&”，且序列2是序列1的逆序列。例如，“a+b&b+a”是属于该模式的字符序列，而“1+3&3-1”则不是。

## 输入
输入字符序列

## 输出
如果序列符合模式则输出1,不符合则输出0

## 样例1
### 输入
a+b&b+a@

### 输出
1

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

//2. 取栈的长度
int GetLen(SqStack *s) {
    return s->top;
}

//3. 查看栈顶元素
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
    while((c=getchar()) != '&') {
        Push(&s, c);
    }
    while((c=getchar()) != '@') {
        if (Pop(&s, &d) || c != d) {
            flag = 0;
            break;
        }
    }
    if (!IsStackEmpty(&s)) flag = 0;
    printf("%d\n", flag);
    return 0;
}
