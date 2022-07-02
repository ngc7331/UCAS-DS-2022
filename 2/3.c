/*
# 3-改进的迷宫寻路
## 描述
给定一张地图及入口与出口，人只能走上下左右，但要达到出口时，必须先拿到钥匙，然而钥匙掉落在迷宫中，你需要从中捡取，求拿到钥匙并走出迷宫的最快路线。

## 输入
输入分为两个部分。第一部分是两个整数X与Y，X<100，Y<100，表示迷宫的行与列，第二部分是迷宫地图，1表示迷宫的墙，0表示人可走，R表示入口，C表示出口，Y表示钥匙。

## 输出
拿到钥匙并走出迷宫的最快路线(最左上角坐标为1，1)

## 样例1
### 输入
5 7
1R10001
1010101
1000011
101100C
1Y00011

### 输出
1 2
2 2
3 2
4 2
5 2
5 3
5 4
5 5
4 5
4 6
4 7

*/

#include <stdio.h>
#include <stdlib.h>

#define MAPMAXIZE 100

#define WALL '1'
#define PATH '0'
#define ENTRANCE 'R'
#define EXIT 'C'
#define KEY 'Y'

typedef struct {
    int x, y;
} Position2d, Size2d;

typedef struct __step{
    int s;
    Position2d p;
    struct __step *parent;
} Step;

typedef struct {
    char map[MAPMAXIZE + 2][MAPMAXIZE + 2];
    Size2d size;
    Position2d entrance, exit, key;
} Maze;

typedef Step ElemType;

typedef struct __node {
    Step e;
    struct __node *next;
} QNode;

typedef struct {
    QNode *head, *tail;
} Queue;

void QueueInit(Queue *q) {
    q->head = q->tail = (QNode *) malloc(sizeof(QNode));
    q->head->next = NULL;
}

int QueueIsEmpty(Queue q) {
    return q.head == q.tail;
}

void Enqueue(Queue *q, ElemType e) {
    QNode *n = (QNode *) malloc(sizeof(QNode));
    n->e = e;
    n->next = NULL;
    q->tail->next = n;
    q->tail = n;
}

void Dequeue(Queue *q, ElemType *e) {
    if (QueueIsEmpty(*q)) return ; // queue is empty
    QNode *h = q->head->next;
    *e = h->e;
    q->head->next = h->next;
    if (q->tail == h) q->tail = q->head;
    free(h);
}

void QueueGetTail(Queue q, ElemType *e) {
    *e = q.tail->e;
}

int walk(Maze m, int x, int y, Step *prev, Position2d target, Queue *q) {
    if (m.map[x][y] == WALL) return -1; // can't walk here
    Position2d p = {x, y};
    Step s = {prev->s+1, p, prev};
    Enqueue(q, s);
    m.map[x][y] = WALL; // walked, marked as WALL
    if (x == target.x && y == target.y) return 1; // reached target!
    return 0;
}

void printPath(Step *last) {
    if (last->parent == NULL) return ; // this never prints the 1st step(start)
    printPath(last->parent); // print path recursively to form a reversed-order
    printf("%d %d\n", last->p.x, last->p.y);
}

void solveMaze(Maze m, Position2d start, Position2d target) {
    // BFS method
    Maze __m = m; // copy the maze to keep it from being modified
    Queue q; QueueInit(&q);
    Step s = {0, start, NULL};
    Enqueue(&q, s);
    while (!QueueIsEmpty(q)) {
        Step *prev = (Step *) malloc(sizeof(Step));
        Dequeue(&q, prev);
        // try to walk around
        if (walk(__m, prev->p.x-1, prev->p.y, prev, target, &q) == 1 ||
            walk(__m, prev->p.x+1, prev->p.y, prev, target, &q) == 1 ||
            walk(__m, prev->p.x, prev->p.y-1, prev, target, &q) == 1 ||
            walk(__m, prev->p.x, prev->p.y+1, prev, target, &q) == 1
        ) break;
    }
    // now queue->tail is the last step, which reached target
    // and the steps forms a parent-tree
    // so we can use the parent field to traverse the entire vaild path
    Step last;
    QueueGetTail(q, &last);
    printPath(&last);
}

int main() {
    Maze m;
    scanf("%d %d\n", &(m.size.x), &(m.size.y));
    for (int i=0; i<=m.size.x+1; i++) {
        for (int j=0; j<=m.size.y+1; j++) {
            if (i==0 || j==0 || i==m.size.x+1 || j==m.size.y+1) // build the surrounding wall
                m.map[i][j] = '1';
            else {
                m.map[i][j] = getchar();
                if (m.map[i][j] == '\n') // if c is a '\n', re-getchar
                    m.map[i][j] = getchar();
                if (m.map[i][j] == ENTRANCE)
                    m.entrance.x = i, m.entrance.y = j;
                else if (m.map[i][j] == EXIT)
                    m.exit.x = i, m.exit.y = j;
                else if (m.map[i][j] == KEY)
                    m.key.x = i, m.key.y = j;
            }
        }
    }
    printf("%d %d\n", m.entrance.x, m.entrance.y); // the entrance must be the first step
    solveMaze(m, m.entrance, m.key); // find the shortest path from entrance to key
    solveMaze(m, m.key, m.exit);     // find the shortest path from key to exit
    return 0;
}