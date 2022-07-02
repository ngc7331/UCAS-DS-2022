/*
# 2.38-双向循环链表访问
## 描述
设有一双向循环链表，每个节点中除有prior,data和next三个域外，还增设了一个访问频度域freq。在链表被启用之前，频度域freq的值均初始化为0，而每当对链表进行一次LOCATE(L,x)的操作后，被访问的节点（即元素值等于x的节点）中的频度域freq的值便增1，同时调整链表中节点之间的次序，使其按访问频度非递增的次序顺序排列，以便始终保持被频繁访问的节点总是靠近表头结点。编写符合上述要求的LOCATE操作的算法。

## 输入
输入包含三行，第一行是链表中的元素个数，第二行是链表中的元素，第三行包含所有被访问的元素

## 输出
顺序输出从表头节点开始的链表中的元素。
注意：如果有多个元素的访问次数相同，需要按照访问次序，将先访问到的元素放在前面

## 样例1
### 输入
10
1 2 3 4 5 6 7 8 9 10
1 2 2 2 3 4 5 5 4 10 9

### 输出
2 4 5 1 3 10 9 6 7 8

*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// THIS MIGHT NOT SATISFY REQUIREMENT:
// __node.i should be removed?

typedef struct __node {
    struct __node *prior, *next;
    ElemType data;
    int freq, i;
} DLNode, *DLList;

DLList InitList() {
    DLList head = (DLList) malloc(sizeof(DLNode));
    if (head == NULL) return NULL;
    head->prior = head->next = head;
    return head;
}

int InsertList(DLList head, ElemType data) {
    DLNode *n = (DLNode *) malloc(sizeof(DLNode));
    if (n == NULL) return 1;
    n->prior = head;
    n->next = head->next;
    head->next->prior = n;
    head->next = n;
    n->data = data;
    n->freq = n->i = 0;
    return 0;
}

int LOCATE(DLList L, int x, int i) {
    DLNode *n = L->next;
    while (n != L && n->data != x) n = n->next;
    if (n == L) return -1; // 未定位到，即 x \notin list

    n->freq ++; // 频度++
    if (n->i == 0) n->i = i;

    // 找 n 入表位置
    DLNode *p = n->prior;
    while (p != L && p->freq < n->freq) p = p->prior;
    while (p != L && p->freq == n->freq && p->i > n->i) p = p->prior;

    // n 出列表
    n->prior->next = n->next;
    n->next->prior = n->prior;

    // n 入列表 (p后)
    n->prior = p;
    n->next = p->next;
    p->next->prior = n;
    p->next = n;
    return 0;
}

void input(DLList list, int n) {
    int data;
    if (n <= 0) return ;
    scanf("%d", &data);
    input(list, n-1);
    InsertList(list, data);
}

void PrintList(DLList head) {
    DLNode *p = head->next;
    if (p == head)
        printf("NULL\n");
    while (p != head) {
        printf("%d ", p->data);
        p = p->next;
    }
}

int main() {
    DLList list = InitList();
    int data, n, i=0;
    scanf("%d", &n);
    input(list, n);
    while (scanf("%d", &data) == 1)
        LOCATE(list, data, ++i);
    PrintList(list);
    return 0;
}