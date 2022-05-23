/*
# 2.19-链表删除指定范围的元素
## 描述
已知线性表中的元素以递增有序排列，并以单链表为存储结构。试写一高效算法，删除表中所有值大于mink且小于maxk的元素（若表中存在这样的元素），同时释放被删节点的空间。
注意：mink和maxk是给定的两个参变量，他们的值可以和表中的元素相同，也可以不同。

## 输入
输入包含两行，第一行是链表中的元素，以空格分隔。
第二行分别为mink和maxk两个元素，以空格分隔。

## 输出
输出最后的链表中的元素

## 样例1
### 输入
1 2 3 4 5 8 12 15 16 22
6 18

### 输出
1 2 3 4 5 22

*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct __node {
    struct __node *next;
    ElemType data;
} LNode, LList;

int InitList(LList *head) {
    head->next = NULL;
    return 0;
}

int InsertList(LList *head, ElemType data) {
    LNode *n = (LNode *) malloc(sizeof(LNode));
    n->next = head->next;
    n->data = data;
    head->next = n;
    return 0;
}

int ListDeleteRange(LList *head, int mink, int maxk) {
    LNode *p=head->next, *pp=head;
    while (p != NULL && p->data < maxk) {
        if (p->data <= mink) pp = pp->next;
        p = p->next;
    }
    LNode *tmp = pp->next;
    pp->next = p;
    while (tmp != p) {
        LNode *ttmp = tmp;
        tmp = tmp->next;
        free(ttmp);
    }
    return 0;
}

void PrintList(LList *head) {
    LNode *p = head->next;
    if (p == NULL)
        printf("NULL\n");
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
}

void sinput(char *line, LList *head) {
    int data, offset;
    if (sscanf(line, "%d%n", &data, &offset) != 1)
        return ;
    sinput(line+offset, head);
    InsertList(head, data);
}

int main() {
    LList *list = (LList *) malloc(sizeof(LList));
    InitList(list);

    char tmp[1005];
    int mink, maxk;

    fgets(tmp, 1000, stdin);
    sinput(tmp, list);
    scanf("%d %d", &mink, &maxk);

    ListDeleteRange(list, mink, maxk);

    PrintList(list);
    return 0;
}