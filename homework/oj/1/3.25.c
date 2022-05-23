/*
# 3.25-递归函数非递归法计算
## 描述
试写出求递归函数Ｆ(n)的递归算法，并消除递归:
F(n ) = n + 1 (n = 0)
F(n) = n * F(n / 2) (n > 0)

## 输入
输入非负整数ｎ

## 输出
计算出的F(n)函数的值

## 样例1
### 输入
10

### 输出
100

*/

#include <stdio.h>

// 递归版本
int F_re(int n) {
    if (n==0) return 1;
    return F_re(n/2) * n;
}

// 非递归版本
int F(int n) {
    int cache[n+1];
    cache[0] = 1;
    for (int i=1; i<=n; i++) {
        cache[i] = i * cache[i/2];
    }
    return cache[n];
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", F(n));
}