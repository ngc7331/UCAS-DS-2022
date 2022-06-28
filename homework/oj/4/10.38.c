/*
# 10.38-2-路归并排序
## 描述

2-路归并排序的另一策略是，先对待排序序列扫描一遍，找出并划分为若干个最大有序子列，将这些子列作为初始归并段。试写一个算法在链表结构上实现这一策略。

## 输入
输入分为两行：
第一行代表输入的数据元素的个数
第二行是输入的所有数据元素，元素之间用空格隔开

## 输出
输出经过2-路归并排序后的数据元素序列，元素之间用空格隔开（数据元素按从小到大排序）

## 样例1
### 输入
5
2 5 3 1 4

### 输出
1 2 3 4 5

*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSEG 1000

typedef struct __node {
    int data;
    struct __node *next;
} Node, *List;

Node *newNode() {
    Node *n = (Node *) malloc(sizeof(Node));
    n->next = NULL;
    return n;
}

void insertList(List l, int x) {
    List n = newNode();
    n->data = x;
    while (l->next != NULL) l = l->next;
    l->next = n;
    return ;
}

void merge(List *l1, int len1, List l2, int len2) {
    List p = *l1;
    List r = newNode();
    int i, j;
    for (i=0, j=0; i<len1 && j<len2; ){
        if (p->data < l2->data) {
            insertList(r, p->data);
            i++;
            p = p->next;
        }
        else {
            insertList(r, l2->data);
            j++;
            l2 = l2->next;
        }
    }
    for (; i<len1; i++, p=p->next)
        insertList(r, p->data);
    for (; j<len2; j++, l2=l2->next)
        insertList(r, l2->data);
    *l1 = r->next;
}

void mergeSort(List l) {
    // 划分归并段
    int len = 0, last = l->next->data;
    List S[MAXSEG];
    int L[MAXSEG] = {0};
    List p = S[0] = l->next;
    while (p) {
        if (p->data < last)
            S[++len] = p, L[len] = 0;
        last = p->data;
        L[len]++;
        p = p->next;
    }
    S[++len] = NULL;

    // 合并
    int step = 1;
    while (step < len) {
        for (int i=0; i<len; i+=2*step) {
            if (i+step >= len) break;
            merge(&S[i], L[i], S[i+step], L[i+step]);
            L[i] = L[i] + L[i+step];
        }
        step *= 2;
    }
    l->next = S[0];
}

void printList(List l) {
    while ((l=l->next))
        printf("%d%c", l->data, l->next ? ' ' : '\n');
}

int main(int argc, char *argv[]) {
    int x, len;
    scanf("%d", &len);
    List l = newNode();
    while (len --) {
        scanf("%d", &x);
        insertList(l, x);
    }
    mergeSort(l);
    printList(l);
    return 0;
}