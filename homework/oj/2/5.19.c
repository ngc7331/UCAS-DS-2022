/*
# 5.19查找矩阵中的马鞍点
## 描述
若矩阵A(m*n)中的某个元素a是第i行中的最小值，同时又是第j列中的最大值，则称此元素为该矩阵中的一个马鞍点。
假设以二维数组存储矩阵Ａ(m*n)，试编写求出矩阵中所有马鞍点的算法，并分析你的算法在最坏情况下的时间复杂度。

## 输入
输入分为两部分：
第一部分位于第一行，输入二维数组的行数与列数（中间由空格间隔），
从第二行开始作为第二部分，表示为整数二维数组的读入。

## 输出
输出所有在二维数组中表示马鞍点的元素的值，中间由空格隔开

## 样例1
### 输入
3 4
10 16 13 14
15 18 15 20
5 8 12 32

### 输出
15 15

*/

#include <stdio.h>
#define INFINITE 9999999

void initArray(int *a, int n, int data) {
    for (int i=0; i<n; i++)
        a[i] = data;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int A[m][n];
    int lmin[m]; initArray(lmin, m, INFINITE);
    int data;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d", &data);
            if (data < lmin[i])
                lmin[i] = data;
            A[i][j] = data;
        }
    }
    for (int j=0; j<n; j++) {
        int cmax = -INFINITE;
        int k = -1;
        for (int i=0; i<m; i++) {
            if (A[i][j] > cmax)
                cmax = A[i][j], k = i;
        }
        if (lmin[k] == cmax)
            printf("%d ", cmax);
    }
    // 最坏情况时间复杂度为 O(m*n)
    return 0;
}