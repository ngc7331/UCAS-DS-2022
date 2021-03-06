/*
# 3.31-回文字符串
## 描述
假设称正读和反读都相同的字符序列为"回文",例如,'abba'和'abcba'是回文，
而'abcde'和'ababab'则不是回文。
试写一个算法判别读入的一个以'@'为结束符的字符序列是否为回文。

## 输入
输入字符串，以@结尾

## 输出
是回文则输出1，否则输出0

## 样例1
### 输入
abba@
abcde@

### 输出
1
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

typedef struct __qnode {
    	ElemType data;
    	struct __qnode *next;
} QNode;

typedef struct {
	QNode *front, *rear;
    int len;
} LinkedQueue;

int InitQueue(LinkedQueue *lq) {
    lq->front = lq->rear = (QNode *) malloc(sizeof(QNode));
    if (lq->front == NULL) return 1;
    lq->len = 0;
    lq->front->next = lq->rear->next = NULL;
    return 0;
}

int Enqueue(LinkedQueue *lq, ElemType e) {
    QNode *n = (QNode *) malloc(sizeof(QNode));
    if (n == NULL) return 1;
    n->data = e;
    n->next = NULL;
    lq->rear->next = n;
    lq->rear = n;
    lq->len ++;
    return 0;
}

//6. (队头)元素出队
int Dequeue(LinkedQueue *lq, ElemType *e) {
    QNode *n = lq->front->next;
    *e = n->data;
    lq->front->next = n->next;
    lq->len --;
    free(n);
    return 0;
}

int main() {
    SqStack s;
    InitStack(&s);
    LinkedQueue q;
    InitQueue(&q);
    char c, d;
    while ((c=getchar()) != '@') {
        Push(&s, c);
        Enqueue(&q, c);
    }
    while (!IsStackEmpty(&s)) {
        Pop(&s, &c);
        Dequeue(&q, &d);
        if (c != d) break;
    }
    printf("%d", IsStackEmpty(&s));
    return 0;
}