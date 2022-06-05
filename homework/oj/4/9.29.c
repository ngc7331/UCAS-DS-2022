/*
# 9.29-有序表查找
## 描述
已知一非空有序表，表中记录按关键字递增排列，以不带头结点的单循环链表作存储结构，外设两个指针h和t，其中h始终指向关键字最小的节点，t则在表中浮动，其初始位置和h相同，在每次查找之后指向刚查到的节点。查找算法的策略是：首先将给定值K和t->key进行比较，若相等，则查找成功；否则因K小于或大于t->key而从h所指节点或t所指节点的后继节点进行查找，按上述过程编写查找算法。

## 输入
第一行输入顺序表中的元素，以空格分隔
第二行输入需要查找的元素，以空格分隔

## 输出
对每个需要查找的元素输出是否查找到，能查找到输出1，否则输出0

## 样例1
### 输入
2 4 32 64 100
1 2 3

### 输出
0 1 0

*/

#include <stdio.h>
#include <stdlib.h>

#define CACHESIZE 10000

typedef enum {
    False,
    True,
} Bool;

typedef struct __node{
    int key;
    struct __node *next;
} node, *list;

node *newNode() {
    return (node *) malloc(sizeof(node));
}

void insertTailList(list *lp, int k) {
    if (*lp == NULL) {
        list l = *lp = newNode();
        l->next = l;
        l->key = k;
    } else {
        list p = *lp, n = newNode();
        n->key = k;
        n->next = *lp;
        while (p->next != *lp) p = p->next;
        p->next = n;
    }
}

list h, t;
Bool search(int k) {
    if (k == t->key)
        return True;
    else if (k < t->key) {
        t = h;
        while (t->next != h && t->key != k) t = t->next;
        return t->key == k;
    } else {
        list tmp = t;
        while (t->next != tmp && t->key != k) t = t->next;
        return t->key == k;
    }
}

int main(int argc, char *argv[]) {
    list l = NULL;
    char tmp[CACHESIZE], *tmpp=tmp;
    int k, offset;
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &k, &offset) == 1) {
        tmpp += offset;
        insertTailList(&l, k);
    }
    h = t = l;
    tmpp = tmp;
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &k, &offset) == 1) {
        tmpp += offset;
        printf("%d ", search(k));
    }
    return 0;
}