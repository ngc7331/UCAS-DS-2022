/*
# 8.13-边界标志法
## 描述
试完成边界标志法和依首次适配策略进行分配相应的回收释放块的算法

## 输入
输入分为两部分，第一部分是已有的空闲块，其中每一行有三个部分，分别表示标志位，起始地址以及块空间大小
第二部分是待回收的释放块，每行有三个部分，分别表示标志位，起始地址以及块空间大小

## 输出
输出回收后的空闲块状态

## 样例1
### 输入
0 10000 15000
0 31000 8000
0 59000 41000

1 30000 1000
1 40000 2000

### 输出
0 10000 15000
0 30000 9000
0 40000 2000
0 59000 41000

## 样例2
### 输入
0 0 100
0 3001 4000

1 2000 1000

### 输出
0 0 100
0 2000 1000
0 3001 4000

*/

#include <stdio.h>
#include <stdlib.h>

// this works in local machine
// but caused a runtime error in online-judge system
// I don't know how to fix it

// 8.13-fake.c is a working solution
// but it doesn't really allocate memory

#define SIZE 100001

typedef enum {
    FREE,
    USED
} TAG;

typedef struct __word {
    union {
        struct __word *llink;
        struct __word *uplink;
    };
    TAG tag;
    int size;
    struct __word *rlink;
} word, head, foot, *Space;

#define FootLoc(p) ((p) + (p)->size - 1)

Space base, list=NULL;

void initUsedBlocks() {
    for (Space b=base; b<base+SIZE; b++) {
        b->tag = USED;
        b->uplink = b;
        b->llink = b->rlink = b;
    }
}

void createFreeBlock(int start, int size) {
    Space s = base + start;
    s->tag = FREE;
    s->size = size;
    if (list == NULL) {
        list = s;
        s->llink = s->rlink = s;
    }
    else {
        s->llink = list->llink;
        s->rlink = list;
        list->llink->rlink = s;
        list->llink = s;
        list = s;
    }
    FootLoc(s)->uplink = s;
    FootLoc(s)->tag = FREE;
}

void createUsedBlock(int start, int size) {
    Space s = base + start;
    s->llink = s - 1;
    s->tag = USED;
    s->size = size;
    s->rlink = s + size;
    FootLoc(s)->uplink = s;
    FootLoc(s)->tag = USED;
}

int isUsed(Space b) {
    return b==NULL || b->tag==USED;
}

void freeBlock(int start, int size) {
    Space s = base + start;
    Space left, right;
    if (s == base) left = NULL;
    else left = (s-1)->uplink;
    if (s + size == base+SIZE) right = NULL;
    else right = s + size;
    s->tag = FREE;
    if (isUsed(left) && isUsed(right)) {
        // 1. 两侧均占用，直接插入空闲链表
        if (list == NULL) {
            list = s;
            s->llink = s->rlink = s;
        }
        else {
            s->llink = list->llink;
            s->rlink = list;
            list->llink->rlink = s;
            list->llink = s;
            list = s;
        }
        FootLoc(s)->uplink = s;
    } else if (isUsed(left)) {
        // 2. 右侧空闲，合并
        s->rlink = right->rlink;
        s->llink = right->llink;
        s->size += right->size;
        s->llink->rlink = s;
        s->rlink->llink = s;
        FootLoc(s)->uplink = s;
    } else if (isUsed(right)) {
        // 3. 左侧空闲，合并
        left->size += s->size;
        FootLoc(left)->uplink = left;
    } else {
        // 4. 两侧均空闲，合并
        left->rlink = right->rlink;
        right->rlink->llink = left;
        left->size += s->size + right->size;
        FootLoc(left)->uplink = left;
    }
    FootLoc(s)->tag = FREE;
}

void printFreeBlock() {
    for (Space b=base; b<base+SIZE; b++) {
        if (b->tag == FREE) {
            printf("0 %d %d\n", (int)(b-base), b->size);
            b += b->size - 1;
        }
    }
}

int main(int argc, char *argv[]) {
    base = (Space) malloc(SIZE * sizeof(word));
    initUsedBlocks();  // 模拟所有空间默认被占用
    TAG tag;
    int start, size;
    while(scanf("%d %d %d\n", (int *)&tag, &start, &size) == 3) {
        switch (tag) {
        case FREE:
            createFreeBlock(start, size);  // 模拟空闲块
            break;
        case USED:
            createUsedBlock(start, size);  // 模拟占用块
            freeBlock(start, size);        // 释放占用块
            break;
        }
    }
    printFreeBlock();
    return 0;
}