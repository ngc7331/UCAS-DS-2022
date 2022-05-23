/*
# 8.15-可利用空间表
## 描述
设被管理空间的上下界地址分别由变量highbound和lowbound给出，形成一个由同样大小的块组成的“堆”。试写一个算法，将所有tag域为0的块按始址递增顺序链接成一个可利用空间表。

## 输入
输入分为两行，第一行为管理空间的上下界变量的highbound，lowbound以及每个块的大小，第二行为每个块的tag

## 输出
输出为可利用空间表，每一行代表每个元素，每个元素包含三个数字，分别代表tag，起始地址和空间大小

## 样例1
### 输入
0 20 2
0 0 1 1 0 0 1 0 1 1

### 输出
0 0 4
0 8 4
0 14 2

## 样例2
### 输入
30 40 1
1 1 1 1 1 1 1 1 1 1

### 输出
0 0 0

## 样例3
### 输入
10 25 3
0 0 0 0 1

### 输出
0 10 12

*/

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FREE,
    USED
} TAG;

typedef struct __node {
    TAG tag;
    int start;
    int size;
    struct __node *next;
} word, *Space;

Space newSpace(TAG tag, int start, int size) {
    Space n = (Space) malloc(sizeof(word));
    n->tag = tag;
    n->start = start;
    n->size = size;
    n->next = NULL;
    return n;
}

void insertList(Space *lp, Space n) {
    if (*lp == NULL || (*lp)->start > n->start + n->size) {
        n->next = *lp;
        *lp = n;
    } else {
        Space l = *lp, p = l->next, pp = l;
        while (p != NULL && p->start < n->start + n->size) {
            p = p->next;
            pp = pp->next;
        }
        pp->next = n;
        n->next = p;
    }
}

void printList(Space l) {
    if (l == NULL)
        printf("0 0 0\n");
    else {
        while (l != NULL) {
            printf("0 %d %d\n", l->start, l->size);
            l = l->next;
        }
    }
}

int main(int argc, char *argv[]) {
    Space l = NULL;
    int highbound, lowbound, blocksize;
    TAG t;
    scanf("%d %d %d\n", &highbound, &lowbound, &blocksize);
    int start=highbound, size=0;
    for (int i=0; i<(lowbound-highbound)/blocksize; i++) {
        scanf("%d", (int *)&t);
        switch (t) {
        case FREE:
            size += blocksize;
            break;
        case USED:
            if (size)
                insertList(&l, newSpace(FREE, start, size));
            size = 0;
            start = highbound + (i+1) * blocksize;
            break;
        }
    }
    if (start == highbound) {
        insertList(&l, newSpace(FREE, start, lowbound-highbound));
    }
    printList(l);
    return 0;
}