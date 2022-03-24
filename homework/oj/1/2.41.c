#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define abs(a) ((a)>0?(a):-(a))

typedef struct {
    int a, e;
} PolyTerm;

typedef struct PolyNode {
  PolyTerm data;
  struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;

LinkedPoly InitPoly() {
    LinkedPoly p = (LinkedPoly) malloc(sizeof(PolyNode));
    p->next = NULL;
    return p;
}

int InsertPoly(LinkedPoly p, int a, int e) {
    if (a == 0 || e < 0) return 1;
    // 保证指数降序，找到插入位置
    PolyLink pp = p->next;
    while (pp != NULL && pp->data.e > e) {
        pp = pp->next;
        p = p->next;
    }
    // 有同指数的项，系数直接相加
    if (pp != NULL && pp->data.e == e) {
        pp->data.a += a;
        if (pp->data.a == 0) { // 系数为零，释放
            p->next = pp->next;
            free(pp);
            return 1;
        }
        return 0;
    }
    // 无同指数的项，新建结点插入到p和pp之间
    PolyNode *n = (PolyNode *) malloc(sizeof(PolyNode));
    if (n == NULL) return -1;
    n->data.a = a;
    n->data.e = e;
    n->next = pp;
    p->next = n;
    return 0;
}

void D(LinkedPoly p) {
    PolyLink pp = p->next;
    if (pp == NULL) return ;
    while (pp != NULL) {
        pp->data.a *= pp->data.e;
        pp->data.e --;
        if (pp->data.a == 0) {
            p->next = pp->next;
            free(pp);
            pp = p->next;
        }
        else {
            p = p->next;
            pp = pp->next;
        }
    }
}

void input(LinkedPoly p) {
    int a = 0, e = 0;
    char tmp;
    int sign = 1;
    int *num = &a;
    int findx = 0;
    while ((tmp=getchar()) != EOF && tmp != '\n') {
        switch (tmp) {
        case '-': case '+':
            sign = tmp == '+' ? 1 : -1;
            num = &a;
            findx = 0;
            a = e = 0;
            break;
        case 'x': case '^':
            findx = 1;
            if (a == 0) a = 1;
            num = &e;
            break;
        case ' ':
            if (a) {
                if (!e && findx) e = 1;
                InsertPoly(p, sign * a, e);
            }
            break;
        default:
            *num = *num * 10 + tmp - '0';
        }
    }
    if (!e && findx) e = 1;
    InsertPoly(p, sign * a, e);
}

void print(LinkedPoly p) {
    PolyLink pp = p->next;
    if (pp == NULL) printf("0");
    while (pp != NULL) {
        if (pp->data.a > 0) {
            if (pp != p->next) printf("+ ");
        }
        else printf("- ");
        if (abs(pp->data.a) != 1) printf("%d", abs(pp->data.a));
        if (pp->data.e > 0) printf("x");
        if (pp->data.e > 1) printf("^%d", pp->data.e);
        if (abs(pp->data.a) == 1 && pp->data.e == 0) printf("1");
        if (pp->next != NULL) printf(" ");
        pp = pp->next;
    }
    printf("\n");
}

int main() {
    LinkedPoly p = InitPoly();
    input(p);
    D(p);
    print(p);
}