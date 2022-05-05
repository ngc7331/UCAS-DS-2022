#include <stdio.h>
#include <stdlib.h>

#define TREEMAXNODE 1000

typedef enum {
    False,
    True
} Bool;

typedef enum {
    ERROR = -1,
    OK
} Status;

typedef struct {
    char e;
    int left, right;
} tnode;

typedef struct {
    int i, level;
} tninfo;

typedef struct {
    tnode node[TREEMAXNODE];
    int size;
} SqBiTree;

typedef tninfo ElemType;

typedef struct __qnode {
    	ElemType data;
    	struct __qnode *next;
} QNode;

typedef struct {
	QNode *front, *rear;
    int len;
} LinkedQueue;

Status InitQueue(LinkedQueue *lq) {
    lq->front = lq->rear = (QNode *) malloc(sizeof(QNode));
    if (lq->front == NULL) return ERROR;
    lq->len = 0;
    lq->front->next = lq->rear->next = NULL;
    return OK;
}

int IsQueueEmpty(LinkedQueue *lq) {
    // return lq->front == lq->rear;
    return lq->len == 0;
}

Status GetFront(LinkedQueue *lq, ElemType *e) {
    if (IsQueueEmpty(lq)) return ERROR;
    *e = lq->front->next->data;
    return OK;
}

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

Status Dequeue(LinkedQueue *lq, ElemType *e) {
    if (IsQueueEmpty(lq)) return ERROR;
    QNode *n = lq->front->next;
    *e = n->data;
    lq->front->next = n->next;
    lq->len --;
    free(n);
    if (IsQueueEmpty(lq)) lq->rear = lq->front;
    return OK;
}

Bool isCompleteBiTree(SqBiTree t) {
    // 层序遍历
    LinkedQueue q; InitQueue(&q);
    tninfo root = {1, 0};
    Enqueue(&q, root);
    Bool flag = True, full = True;
    while (!IsQueueEmpty(&q)) {
        tninfo n;
        Dequeue(&q, &n);
        tninfo left = {t.node[n.i].left, n.level+1};
        tninfo right = {t.node[n.i].right, n.level+1};
        if (t.node[n.i].left != -1) {
            if (!full) { // 已有不饱和的结点，然而新结点仍有左孩子
                flag = False;
                break;
            }
            Enqueue(&q, left);
            if (t.node[n.i].right != -1)
                Enqueue(&q, right);
            else
                full = False;
        }
        else {
            if (t.node[n.i].right != -1) { // 无左孩子，却又右孩子
                flag = False;
                break;
            }
            full = False;
        }
    }
    return flag;
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

    printf("%s", isCompleteBiTree(t) ? "Yes" : "No");

    return 0;
}