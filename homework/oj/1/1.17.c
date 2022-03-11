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