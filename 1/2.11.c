/*
# 2.11-顺序表插入元素
## 描述
设顺序表va中的数据为递增有序。写一个算法，将x插入到顺序表的适当位置，保证有序性。

## 输入
输入分为两行，第一行是va顺序表，每个元素按空格分隔，第二行是x的值。
顺序表中的元素最多为100个，所有元素的值均大于0，元素为整型。

## 输出
输出插入x后，va的结果

## 样例1
### 输入
1 3 4 6 45 56
20

### 输出
1 3 4 6 20 45 56

*/

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
    return 0;
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