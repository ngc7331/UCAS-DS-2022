/*
# 5.25. 稀疏矩阵加法
## 描述
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
第$2$到$m_1+1$ 行: 和矩阵的 $B$ 矩阵。
提示：每行的最后一个元素之后不要输出多余空格！

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