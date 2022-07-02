/*
# 2.18-链表删除元素
## 描述
试写一算法，在无头节点的动态单链表上实现线性表操作DELETE(L,i)。

## 输入
输入包含两行，第一行是链表中的元素，第二行表示需要删除的第i个元素，i从0开始计数
若删除后，链表不包含元素，则输出“NULL”。

## 输出
输出删除后的链表元素

## 样例1
### 输入
1 2 3 4 5
4

### 输出
1 2 3 4

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

int ListDelete(LList *head, int n) {
    LNode *p = head;
    while (n-- > 0 && p != NULL) p = p->next;
    if (p == NULL || p->next == NULL) {
        p = NULL;
        return 0;
    }
    LNode *tmp = p->next;
    p->next = p->next->next;
    free(tmp);
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
    int n;

    fgets(tmp, 1000, stdin);
    sinput(tmp, list);
    scanf("%d", &n);

    ListDelete(list, n);

    PrintList(list);
    return 0;
}