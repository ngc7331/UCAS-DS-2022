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