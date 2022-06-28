/*
# 10.35-三叉堆排序算法
## 描述
假设定义堆为满足如下性质的完全三叉树：(1)空树为堆；(2)根结点的值不小于所有子树根的值，且所有子树均为堆。编写利用上述定义的堆进行排序的算法，并分析推导算法的时间复杂度。

## 输入
输入为一行，即为待排序的数据序列

## 输出
输出为一行，即为利用三叉堆排序处理后有序的数据序列

## 样例1
### 输入
3 5 -6 7 96 15 7 29 1 23 42 -10 55 63 27

### 输出
-10 -6 1 3 5 7 7 15 23 27 29 42 55 63 96

*/

#include <stdio.h>

#define MAXHEAPSIZE 10000
#define NEGINFINITE 0x80000000

#define left(a)   (3*a + 1)
#define middle(a) (3*a + 2)
#define right(a)  (3*a + 3)

#define MAX(a, b) ((a)>(b)?(a):(b))

void swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int biggestChild(int heap[], int i, int len) {
    int l = left(i), m = middle(i), r = right(i);
    int ln = heap[l], mn = heap[m], rn = heap[r];
    if (ln >= mn || m >= len) {
        if (ln >= rn || r >= len) return l;
        return r;
    }
    if (mn >= rn || r >= len) return m;
    return r;
}

int main(int argc, char *argv[]) {
    int heap[MAXHEAPSIZE], len=0;
    while (scanf("%d", &heap[len]) == 1) len++;
    // 建大顶堆
    for (int i=len/3-1; i>=0; i--) {
        int j = i;
        while (left(j) < len) {  // 非叶
            int b = biggestChild(heap, j, len);
            if (heap[j] < heap[b]) {
                swap(heap, j, b);
                j = b;
            }
            else break;
        }
    }

    // 堆排序
    for (int i=len-1; i>=0; i--) {
        swap(heap, 0, i);
        int j = 0;
        while (left(j) < i) {
            int b = biggestChild(heap, j, i);
            if (heap[j] < heap[b]) {
                swap(heap, j, b);
                j = b;
            }
            else break;
        }
    }

    // 输出
    for (int i=0; i<len; i++) {
        printf("%d%c", heap[i], i==len-1? '\n' : ' ');
    }

    return 0;
}