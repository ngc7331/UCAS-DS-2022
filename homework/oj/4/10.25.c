/*
# 10.25 链表的插入排序
## 描述
试编写教科书10.2.2节中所述链表插入排序的算法。

## 输入
输入分为两行：
第一行为输入的序列的长度；
第二行为一个无序序列，数与数之间用空格隔开。

## 输出
输出经过链表插入排序后的序列（从小到大排序），<span style="color: rgb(51, 51, 51);">数与数之间用空格隔开。</span>

## 样例1
### 输入
6
6 5 1 2 4 3

### 输出
1 2 3 4 5 6

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

void insertAscList(List l, int x) {
    List n = newNode();
    n->data = x;
    while (l->next && l->next->data < x) l = l->next;
    n->next = l->next;
    l->next = n;
    return ;
}

void printList(List l) {
    while ((l=l->next))
        printf("%d%c", l->data, l->next ? ' ' : '\n');
}

int main(int argc, char *argv[]) {
    int len, x;
    Node l = {0, NULL};
    scanf("%d", &len);
    while (len--) {
        scanf("%d", &x);
        insertAscList(&l, x);
    }
    printList(&l);
    return 0;
}