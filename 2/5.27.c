/*
# 5.27. 稀疏矩阵加法（十字链表）
## 描述
**使用十字链表存储表示完成**
若将稀疏矩阵 $\mathbf{A}$ 的非零元素以行序为主序的顺序存于一维数组 $V$ 中，并用二维数组 $B$ 表示 $A$ 中的相应元素是否为零元素（以0和1分别表示零元素和非零元素）。例如，

*image deleted*


可用

*image deleted*
和
*image deleted*
表示。
试写一算法，实现在上述表示法中实现矩阵相加的运算。并分析你的算法时间复杂度（在代码注释中给出）。

## 输入
第一行 为用空格隔开的两个个数 $m_1, n_1$ ，表示两个矩阵的大小为 $m_1\times{n_1}$。

第二行 为第一个矩阵的 $V$ 数组，元素用空格隔开。（如果没有非零元素，则会空出这一行）
第 $3$到$m_1+2$行：每行分别包含 $n_1$ 个元素，用空格隔开。表示第一个矩阵的 $B$ 数组。
第 $m_1+3$ 行： 第二个矩阵的 $V$ 数组，元素用空格隔开。（如果没有非零元素，则会空出这一行）
第 $m_1+4$到$2\times m_1+3$ 行：第二个矩阵的 $B$ 数组。
提示：$V$ 元素可能为负数。

## 输出
第一行: 和矩阵的 $V$ 数组。如果没有非零元素，则输出空行。
第2-$m_1+1$ 行: 和矩阵的 $B$ 矩阵。


提示：每一行的最后一个元素后不要输出多余空格

## 样例1
### 输入
2 2
1 1
1 0
0 1
-2 -1
1 0
0 1

### 输出
-1
1 0 
0 0

*/

#include <stdio.h>
#include <stdlib.h>

#define CACHESIZE 10000

typedef int ElemType;

typedef struct __node {
    struct __node *next;
    ElemType data;
} LNode, *LList;

typedef struct __OLNode {
    int i, j;
    ElemType e;
    struct __OLNode *right, *down;
} OLNODE, *Olink;

typedef struct {
    Olink *rhead, *chead;
    int mu, nu, tu;
} CList;

int InitList(LList *head) {
    *head = (LList) malloc(sizeof(LNode));
    (*head)->data = 0;
    (*head)->next = NULL;
    return 0;
}

int InitCList(CList *l, int m, int n) {
    l->mu = m, l->nu = n, l->tu = 0;
    l->rhead = (Olink *) malloc(m * sizeof(Olink));
    for (int i=0; i<m; i++) {
        l->rhead[i] = (Olink) malloc(sizeof(OLNODE));
        l->rhead[i]->i = i;
        l->rhead[i]->j = -1;
        l->rhead[i]->right = NULL;
        if (i!=0) l->rhead[i-1]->down = l->rhead[i];
    }
    l->rhead[m-1]->down = NULL;
    l->chead = (Olink *) malloc(n * sizeof(Olink));
    for (int i=0; i<n; i++) {
        l->chead[i] = (Olink) malloc(sizeof(OLNODE));
        l->chead[i]->i = -1;
        l->chead[i]->j = i;
        l->chead[i]->down = NULL;
        if (i!=0) l->chead[i-1]->right = l->chead[i];
    }
    l->chead[n-1]->right = NULL;
    return 0;
}

int InsertCList(CList l, int i, int j, int e) {
    if (e == 0) return 0;
    Olink n = (Olink) malloc(sizeof(OLNODE));
    n->i = i, n->j = j, n->e = e;
    // locate row
    Olink pp=l.chead[j], p=pp->down;
    while (p!=NULL && p->i<i) pp=p, p=p->down;
    pp->down = n, n->down = p;
    // locate column
    pp=l.rhead[i], p=pp->right;
    while (p!=NULL && p->j<j) pp=p, p=p->right;
    pp->right = n, n->right = p;
    l.tu ++;
    return 0;
}

int GetCList(CList l, int i, int j, int *e) {
    Olink p = l.rhead[i]->right;
    while (p!=NULL && p->j<j) p = p->right;
    if (p != NULL && p->j == j) *e = p->e;
    else *e = 0;
    return 0;
}

int RemoveCList(CList l, int i, int j) {
    // locate row
    Olink pp=l.chead[j], p=pp->down;
    while (p!=NULL && p->i<i) pp=p, p=p->down;
    if (p==NULL) return -1;
    pp->down = p->down;
    // locate column
    pp=l.rhead[i], p=pp->right;
    while (p!=NULL && p->j<j) pp=p, p=p->right;
    if (p==NULL) return -1;
    pp->right = p->right;
    free(p);
    l.tu --;
    return 0;
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

void PrintClist(CList l) {
    for (int i=0; i<l.mu; i++) {
        Olink p = l.rhead[i]->right;
        int j=0;
        while (p != NULL) {
            for (; j<p->j; j++)
                printf("0 ");
            printf("1%c", p->j==l.nu-1?'\n':' ');
            j++;
            p = p->right;
        }
        for (; j<l.nu; j++)
            printf("0%c", j==l.nu-1?'\n':' ');
    }
}

// T(m, n) = O(m * n)

int main() {
    int m, n;
    int x, B2;
    char tmp[CACHESIZE];
    LList V1, V2;
    CList B1;
    InitList(&V1); InitList(&V2);
    scanf("%d %d", &m, &n);
    InitCList(&B1, m, n);;
    // get V1
    getchar();
    fgets(tmp, CACHESIZE, stdin);
    InputList(tmp, V1);
    // get B1
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d", &x);
            InsertCList(B1, i, j, x);
        }
    }
    // get V2
    getchar();
    fgets(tmp, CACHESIZE, stdin);
    InputList(tmp, V2);
    // get B2 & caculate
    LNode *p1=V1->next, *pp1=V1, *p2=V2->next;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d", &B2);
            GetCList(B1, i, j, &x);
            if (B2 & x) {
                // B1，B2均非零
                if (p1->data + p2->data == 0) {
                    RemoveCList(B1, i, j);
                    pp1->next = p1->next;
                }
                else {
                    p1->data = p1->data + p2->data;
                    pp1 = pp1->next;
                }
                p1 = p1->next;
                p2 = p2->next;
            }
            else if (x) {
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
                InsertCList(B1, i, j, 1);
            }
        }
    }
    // print V
    PrintList(V1);
    // print B
    PrintClist(B1);
    return 0;
}