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
    int start;
    int size;
    struct __word *rlink;
} word, head, foot, *Space;

word list[SIZE];
int sp = 0;

void createFreeBlock(int start, int size) {
    list[sp].start = start;
    list[sp].size = size;
    list[sp].tag = FREE;
    if (sp > 0) {
        list[sp-1].rlink = list + sp;
        list[sp].llink = list + sp - 1;
        list[sp].rlink = list;
    }
    sp ++;
}

void freeBlock(int start, int size) {
    int left = -1, right = -1;
    for (int i=0; i<sp; i++) {
        if (list[i].start == start + size) right = i;
        if (list[i].start + list[i].size == start) left = i;
        // printf("%d %d %d\n", i, list[i].start, list[i].size);
    }
    // printf("%d %d\n\n", left, right);

    if (left == -1 && right == -1) {
        // 1. 两侧均占用，直接插入空闲链表
        list[sp].start = start;
        list[sp].size = size;
        int i = 0;
        while (i<sp && list[i].start+list[i].size<start) i ++;
        for (int j=sp+1; j>i; j--)
            list[j] = list[j-1];
        list[i].start = start;
        list[i].size = size;
        sp ++;
    } else if (left == -1) {
        // 2. 右侧空闲，合并
        list[right].start = start;
        list[right].size += size;
    } else if (right == -1) {
        // 3. 左侧空闲，合并
        list[left].size += size;
    } else {
        // 4. 两侧均空闲，合并
        list[left].size += size + list[right].size;
        for (int i=left+1; i<sp; i++)
            list[i] = list[i+1];
        sp --;
    }
}

void printFreeBlock() {
    for (int i=0; i<sp; i++) {
        printf("0 %d %d\n", list[i].start, list[i].size);
    }
}

int main(int argc, char *argv[]) {
    TAG tag;
    int start, size;
    while(scanf("%d %d %d", (int *)&tag, &start, &size) == 3) {
        switch (tag) {
        case FREE:
            createFreeBlock(start, size);  // 模拟空闲块
            break;
        case USED:
            freeBlock(start, size);        // 释放占用块
            break;
        }
    }
    printFreeBlock();
    return 0;
}