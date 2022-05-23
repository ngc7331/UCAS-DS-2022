/*
# 3.24-递归函数计算
## 描述
试编写如下定义的递归函数的递归算法，并根据算法画出求ｇ(5, 2)时栈的变化过程。
g(m, n)  = 0 (m = 0, n>=0)   g(m, n) = g(m-1, 2n) + n (m>0, n>=0)

## 输入
输入ｍ与n的数值，中间以逗号隔开

## 输出
递归计算后，g(m, n)的值

## 样例1
### 输入
5,2

### 输出
62

*/

#include <stdio.h>

int g(int m, int n) {
    if (m==0 && n>=0) return 0;
    return g(m-1, 2*n) + n;
}

int main() {
    int m, n;
    scanf("%d,%d", &m, &n);
    printf("%d", g(m, n));
}