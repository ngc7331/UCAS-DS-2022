#include "../ds.h"
#include <stdlib.h>

#ifndef __ELEMTYPE_DEF
#define __ELEMTYPE_DEF
typedef int ElemType;
#endif // __ELEMTYPE_DEF

typedef struct __qnode {
    	ElemType data;
    	struct __qnode *next;
} QNode;

typedef struct {
	QNode *front, *rear;
    int len;
} LinkedQueue;

// 1. 链队列的初始化，构造一个空队列
Status InitQueue(LinkedQueue *lq) {
    lq->front = lq->rear = (QNode *) malloc(sizeof(QNode));
    if (lq->front == NULL) return ERROR;
    lq->len = 0;
    lq->front->next = lq->rear->next = NULL;
    return OK;
}

// 2. 取队列的长度
int GetLen(LinkedQueue *lq) {
    return lq->len;
}

// 3. 判断队列是否为空
int IsQueueEmpty(LinkedQueue *lq) {
    // return lq->front == lq->rear;
    return lq->len == 0;
}

// 4. 查看队头元素
Status GetFront(LinkedQueue *lq, ElemType *e) {
    e = lq->front->data;
    return OK;
}

// 5. 元素入队(尾)
Status Enqueue(LinkedQueue *lq, ElemType e) {
    QNode *n = (QNode *) malloc(sizeof(QNode));
    if (n == NULL) return ERROR;
    n->data = e;
    n->next = NULL;
    lq->rear->next = n;
    lq->rear = n;
    lq->len ++;
    return OK;
}

//6. (队头)元素出队
Status Dequeue(LinkedQueue *lq, ElemType *e) {
    QNode *n = lq->front;
    *e = n->data;
    lq->front = n->next;
    lq->len --;
    free(n);
    return OK;
}

