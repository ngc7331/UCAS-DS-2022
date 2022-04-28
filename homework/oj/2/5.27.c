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