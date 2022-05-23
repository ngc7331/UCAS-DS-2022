/*
# 1.17-k阶斐波那契数列
## 描述
已知k阶斐波那契序列的定义为
$f_0=0, f_1=0, ..., f_{k-2}=0, f_{k-1}=1$
$f_n=f_{n-1}+f_{n-2}+...+f_{n-k}, n=k,k+1,...$
试编写求k阶裴波那契序列的第m项值的函数算法，k和m均以值调用的形式在函数参数表中出现。

## 输入
输入为k和m（m从0开始，$f_0$对应m=0）

## 输出
输出第m项的值

## 样例1
### 输入
2 7

### 输出
13

*/

#include <stdio.h>

int sum(int *n, int s, int e) {
    int sum = 0;
    for (int i=s; i<e; i++) sum += n[i];
    return sum;
}

int fib(int k, int m) {
    int cache[100000] = {0};
    cache[k-1] = 1;
    for (int i=k; i<=m; i++)
        cache[i] = sum(cache, i-k, i);
    return cache[m];
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);
    printf("%d", fib(k, m));
    return 0;
}