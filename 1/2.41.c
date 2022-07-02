/*
# 2.41-稀疏多项式求导
## 描述
试以循环链表作稀疏多项式的存储结构，编写求其导函数的算法，要求利用原多项式中的节点空间存放其导函数（多项式），同时释放所有无用（被删）节点。
稀疏多项式中采用的循环链表存储结构**LinkedPoly**定义为
'''
typedef struct PolyNode{
  PolyTerm data;
  Struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;

'''

## 输入
输入为给定的多项式

## 输出
输出为求导之后的结果，按照多项式中每一项的幂次由高到低排列
如果导数为0，则输出0

## 样例1
### 输入
- 2x + 4x^2 + 2x^3 + 3x^3 + 2x + 3x^2 - 3x^10

### 输出
- 30x^9 + 15x^2 + 14x

## 样例2
### 输入
3x^2 + 4

### 输出
6x

*/

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