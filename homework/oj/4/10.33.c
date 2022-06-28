/*
# 10.33-单链表实现简单选择排序
## 描述
试以单链表为存储结构实现简单选择排序的算法

## 输入
输入为一组待排序的数字序列，共一行

## 输出
输出是将利用简单选择排序的数字序列按递增顺序排列

## 样例1
### 输入
4 8 -5 27 6 13 27 0

### 输出
-5 0 4 6 8 13 27 27

*/

#include <stdio.h>
#include <stdlib.h>

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
    n->next = l->next;
    l->next = n;
    return ;
}

void selectSort(List l) {
    Node *tail = l;
    while (tail && tail->next) {
        Node *p = tail->next, *min = tail->next;
        Node *pp = tail, *pmin = tail;
        while (p) {
            if (p->data < min->data) {
                pmin = pp;
                min = p;
            }
            pp = pp->next;
            p = p->next;
        }
        pmin->next = min->next;
        min->next = tail->next;
        tail->next = min;
        tail = min;
    }
}

void printList(List l) {
    while ((l=l->next))
        printf("%d%c", l->data, l->next ? ' ' : '\n');
}

int main(int argc, char *argv[]) {
    int x;
    Node l = {0, NULL};
    while (scanf("%d", &x) == 1)
        insertList(&l, x);
    selectSort(&l);
    printList(&l);
    return 0;
}