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