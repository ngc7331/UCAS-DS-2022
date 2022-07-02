/*
# 1.19-阶乘
## 描述
试编写算法，计算 $i!\cdot{2^i} (i=0,1,\ldots,n-1) $的值并分别存入数组$a[arrsize]$的各个分量中。假设计算机中允许的整数最大值为$MAXINT=2^{32}-1$, 则当$n>arrsize$ 或对某个 $k(0 \le k \le n-1) $使 $k!\cdot{2^k} > MAXINT$ 时，应按出错处理。

## 输入
- 输入为两个数，用空格隔开，分别表示 $n$ 和 $arrsize$。其中 $0 \lt n, arrsize \le 20 $

## 输出
* 若没有发生出错，则依次输出$i!\cdot{2^i}(i=0,1,\ldots,n-1)$ 的每个分量，用空格隔开。
* 若发生出错，则直接输出-1。

## 样例1
### 输入
3 10

### 输出
1 2 8

## 样例2
### 输入
10 9

### 输出
-1

## 样例3
### 输入
12 15

### 输出
-1

*/

#include <stdio.h>

int main() {
    int n, arrsize;
    scanf("%d %d", &n, &arrsize);
    if (n>arrsize || n>11) {
        printf("-1\n");
        return 0;
    }
    unsigned int a[arrsize];
    a[0] = 1;
    for (int i=1; i<n; i++)
        a[i] = a[i-1] * 2 * i;
    for (int i=0; i<n; i++)
        printf("%u ", a[i]);
    return 0;
}