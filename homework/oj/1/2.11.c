#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100
#define INCRESIZE 100

typedef int ElemType;

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

int InsertList(SqList *s, int data, int pos) {
    if (s->length >= s->size)
        if (IncreList(s) == -1) return -1;
    for (int i=s->length; i>pos; i--)
        s->arr[i] = s->arr[i-1];
    s->arr[pos] = data;
    s->length ++;
}

int SqInsert(SqList *s, int data, int cmp(int a, int b)) {
    int pos=0;
    while(cmp(s->arr[pos], data) && pos < s->length) pos++;
    InsertList(s, data, pos);
    return 0;
}

int smaller(int a, int b) {
    return a < b;
}

int main() {
    SqList l;
    InitList(&l);
    int data;
    while (scanf("%d", &data) == 1)
        SqInsert(&l, data, smaller);
    for (int i=0; i<l.length; i++)
        printf("%d ", l.arr[i]);
    return 0;
}