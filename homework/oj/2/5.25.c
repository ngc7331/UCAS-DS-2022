#include <stdio.h>
#include <stdlib.h>

#define CACHESIZE 10000

typedef int ElemType;

typedef struct __node {
    struct __node *next;
    ElemType data;
} LNode, *LList;

int InitList(LList *head) {
    *head = (LList) malloc(sizeof(LNode));
    (*head)->data = 0;
    (*head)->next = NULL;
}

int InsertList(LList head, ElemType data) {
    LNode *n = (LNode *) malloc(sizeof(LNode));
    n->next = head->next;
    n->data = data;
    head->data ++;
    head->next = n;
    return 0;
}

void InputList(char *input, LList head) {
    int x, offset;
    if (sscanf(input, "%d%n", &x, &offset) != 1)
        return ;
    InputList(input+offset, head);
    InsertList(head, x);
}

void PrintList(LList head) {
    LNode *p = head->next;
    if (p==NULL) printf("\n");
    while (p != NULL) {
        printf("%d%c", p->data, p->next==NULL?'\n':' ');
        p = p->next;
    }
}

// T(m, n) = O(m * n)

int main() {
    int m, n;
    int x, offset;
    LList V1, V2;
    InitList(&V1); InitList(&V2);
    int B1[1000][1000], B2;
    char tmp[CACHESIZE];
    scanf("%d %d", &m, &n);
    // get V1
    getchar();
    fgets(tmp, CACHESIZE, stdin);
    InputList(tmp, V1);
    // get B1
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            scanf("%d", &B1[i][j]);
    // get V2
    getchar();
    fgets(tmp, CACHESIZE, stdin);
    InputList(tmp, V2);
    // get B2 & caculate
    LNode *p1=V1->next, *pp1=V1, *p2=V2->next;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d", &B2);
            if (B2 & B1[i][j]) {
                // B1，B2均非零
                if (p1->data + p2->data == 0) {
                    B1[i][j] = 0;
                    pp1->next = p1->next;
                }
                else {
                    p1->data = p1->data + p2->data;
                    pp1 = pp1->next;
                }
                p1 = p1->next;
                p2 = p2->next;
            }
            else if (B1[i][j]) {
                // 仅B1非零
                p1 = p1->next;
                pp1 = pp1->next;
            }
            else if (B2) {
                // 仅B2非零
                pp1->next = p2;
                pp1 = p2;
                p2 = p2->next;
                pp1->next = p1;
                B1[i][j] = 1;
            }
        }
    }
    // print V
    PrintList(V1);
    // print B
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            printf("%d%c", B1[i][j], j==n-1?'\n':' ');
    return 0;
}