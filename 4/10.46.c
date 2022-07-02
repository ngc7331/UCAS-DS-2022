/*
# 10.46 序列的排序方法
## 描述
序列b的每个元素是一个记录，每个记录占的存储量比其关键字占的存储量大得多，因而记录的移动操作是极为费时的。试写一个算法，将序列b的排序结果放入序列a中，且每个记录只拷贝一次而无其他移动。你的算法可以调用第10章中给出的任何排序算法。思考：当记录存于链表中时，若希望利用快速排序算法对关键字排序，从而最后实现链表的排序，如何模仿上述方法实现？

## 输入
输入分为两行：
第一行为序列b中元素的个数；
第二行为序列b中元素（一个无序序列），数与数之间用空格隔开。

## 输出
<font>输出序列a中的元素（即序列b的排序结果，从小到大排序）</font>，数与数之间用空格隔开。

## 样例1
### 输入
4
-5 66 21 1

### 输出
-5 1 21 66

*/

#include <stdio.h>

#define MAXLENGTH 10000
#define INFINITE 0x7fffffff

typedef struct {
    int key;
    // record
} rec;

int main(int argc, char *argv[]) {
    int len;
    rec a[MAXLENGTH], b[MAXLENGTH];
    int selected[MAXLENGTH];
    scanf("%d", &len);
    for (int i=0; i<len; i++) {
        selected[i] = 0;
        scanf("%d", &b[i].key);
    }
    int min, minj;
    for (int i=0; i<len; i++) {
        min = INFINITE;
        for (int j=0; j<len; j++)
            if (!selected[j] && b[j].key < min)
                min = b[j].key, minj = j;
        a[i] = b[minj];
        selected[minj] = 1;
    }
    for (int i=0; i<len; i++)
        printf("%d ", a[i].key);
    return 0;
}