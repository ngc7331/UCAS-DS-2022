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