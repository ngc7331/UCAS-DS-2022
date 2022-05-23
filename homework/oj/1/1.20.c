/*
# 1.20-求一元多项式的值
## 描述
编写算法求一元多项式$P_n(x_0)=\sum_{i=0}^n a_i x_0^i$的值$P_n(x_0)$

## 输入
输入第一行为$x_0$和$n$，以空格分隔，$n>=0$
输入第二行为$a_i(i=0,1,...,n)$，$-1000<=a_i<=1000$以空格分隔

## 输出
输出$P_n(x_0)$的值

## 样例1
### 输入
2 2
0 1 2

### 输出
10

*/

#include <stdio.h>

int main() {
    long long p = 0;
    int n, x0, ai, x=1;
    scanf("%d %d", &x0, &n);
    for (int i=0; i<=n; i++) {
        scanf("%d", &ai);
        p += ai * x;
        x *= x0;
    }
    printf("%lld\n", p);
    return 0;
}