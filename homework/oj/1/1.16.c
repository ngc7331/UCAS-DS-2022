/*
# 1.16-三整数排序
## 描述
写一个算法，自大到小依次输出顺序读入的三个整数，x，y和z的值

## 输入
输入x，y和z

## 输出
输出自大到小的排序

## 样例1
### 输入
 1 2 3

### 输出
 3 2 1

*/

#include <stdio.h>

void swap(int *x, int i, int j) {
    int tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
}

int main() {
    int x[3];
    for (int i=0; i<3; i++) {
        scanf("%d", &x[i]);
        for (int j=0; j<i; j++) {
            if (x[i] > x[j]) swap(x, i, j);
        }
    }
    for (int i=0; i<3; i++) printf("%d ", x[i]);
    return 0;
}