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

#define Tail(p) ((p)->start + (p)->size)

Space newSpace(TAG tag, int start, int size) {
    Space n = (Space) malloc(sizeof(word));
    n->tag = tag;
    n->start = start;
    n->size = size;
    n->next = NULL;
    return n;
}

Space findAscPrev(Space l, Space n) {
    // assert l != NULL
    Space p = l;
    while (p->next && p->next->start < Tail(n))
        p = p->next;
    return p;
}

void insertList(Space *lp, Space n) {
    if (!*lp)
        *lp = n;
    else if (Tail(n) < (*lp)->start) {
        // merge left
        (*lp)->start = n->start;
        (*lp)->size += n->size;
    } else if (Tail(n) == (*lp)->start) {
        // insert
        n->next = (*lp);
        (*lp) = n;
    } else {
        Space p = findAscPrev(*lp, n);
        if (Tail(p) == n->start && p->next && Tail(n) == p->next->start) {
            // merge both
            p->size += n->size + p->next->size;
            Space pp = p->next;
            p->next = pp->next;
            free(pp);
        } else if (Tail(p) == n->start) {
            // merge left
            p->size += n->size;
        } else if (p->next && Tail(n) == p->next->start) {
            p->next->start = n->start;
            p->next->size += n->size;
        } else {
            n->next = p->next;
            p->next = n;
        }
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
        if (t == FREE)
            insertList(&l, newSpace(FREE, highbound + i*blocksize, blocksize));
    }
    printList(l);
    return 0;
}