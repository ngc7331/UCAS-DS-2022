/*
# 2.12-顺序表比较
## 描述
设$A=(a_1,...,a_m)$和$B=(b_1,...,b_n)$均为顺序表，$A'$和$B'$分别A和B中除去最大共同前缀后的子表（例如，$A=(x,y,y,z,x,z)$，$B=(x,y,y,z,y,x,x,z)$，则两者中最大的共同前缀为$(x,y,y,z)$，在两表中除去最大共同前缀后的子表分别为$A'=(x,z)$和$B'=(y,x,x,z)$)。若$A'=B'=NULL$，则$A=B$；若$A'=NULL$，而$B' 不等于 NULL$，或者两者均不为NULL，且$A'$的首元小于$B'$的首元，则$A<B$；否则$A>B$。试写一个比较$A,B$大小的算法。（请注意，在算法中，不要破坏原表$A$和$B$，并且，也不一定先求得$A'$和$B'$才进行比较）。

## 输入
输入为两行，分别代表$A$和$B$中的元素，以逗号分开。每个顺序表最多100个元素。

## 输出
输出A和B的比较结果，0代表$A=B$，1代表$A<B$，2代表$A>B$

## 样例1
### 输入
a,b,c,d
a,b,c,d,e

### 输出
1

## 样例2
### 输入
a,w,s
a,h,l

### 输出
2

*/

#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100
#define INCRESIZE 100

typedef char ElemType;

typedef struct {
    int length, size;
    ElemType *arr;
} SqList;

int InitList(SqList *s) {
    s->arr = (ElemType *) malloc(sizeof(ElemType) * INITSIZE);
    if (s->arr == NULL) return -1;
    s->size = INITSIZE;
    s->length = 0;
    return 0;
}

int IncreList(SqList *s) {
    s->arr = (ElemType *) realloc(s, sizeof(ElemType) * (s->size + INCRESIZE));
    if (s->arr == NULL) return -1;
    s->size += INCRESIZE;
    return 0;
}

int InsertList(SqList *s, ElemType data, int pos) {
    if (s->length >= s->size)
        if (IncreList(s) == -1) return -1;
    for (int i=s->length; i>pos; i--)
        s->arr[i] = s->arr[i-1];
    s->arr[pos] = data;
    s->length ++;
    return 0;
}

int TailInsert(SqList *s, ElemType data) {
    return InsertList(s, data, s->length);
}

void input(SqList *s) {
    char c;
    while ((c=getchar()) != '\n' && c != EOF) {
        if (c==',') continue;
        TailInsert(s, c);
    }
}

int compare(SqList a, SqList b) {
    int i=0;
    while (i<a.length && i<b.length && a.arr[i]==b.arr[i]) i++;
    if (i == a.length) {
        if (i == b.length) return 0;    // a' & b' is NULL
        return 1;                       // a' is NULL
    }
    if (i == b.length)
        return 2;                       // b' is NULL
    return (a.arr[i] > b.arr[i]) + 1;   // if a>b return 2, else return 1
}

int main() {
    SqList a, b;
    InitList(&a);
    InitList(&b);
    input(&a);
    input(&b);
    printf("%d", compare(a, b));
    return 0;
}