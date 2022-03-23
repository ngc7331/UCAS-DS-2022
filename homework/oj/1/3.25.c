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