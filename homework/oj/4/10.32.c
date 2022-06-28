/*
# 10.32-荷兰旗问题
## 描述
荷兰国旗问题：设有一个仅由红、白、蓝三种颜色的条块组成的条块序列。请编写一个时间复杂度为O(n)的算法，使得这些条块按红、白、蓝的顺序排好，即排成荷兰旗图案。

## 输入
输入条块序列，其中1表示红，2表示白，3表示蓝

## 输出
输出排序好的序列

## 样例1
### 输入
2 3 3 3 1 1 1

### 输出
1 1 1 2 3 3 3

*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int count[3] = {0, 0, 0};
    int x;
    while (scanf("%d", &x) == 1) count[x-1] ++;
    for (int i=0; i<3; i++)
        for (int j=0; j<count[i]; j++)
            printf("%d ", i+1);
    return 0;
}