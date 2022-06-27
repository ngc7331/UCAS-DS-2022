#include <stdio.h>

#define MAXLENGTH 10000

int main(int argc, char *argv[]) {
    int a[MAXLENGTH], c[MAXLENGTH], len=0;
    while (scanf("%d", &a[len]) == 1) len ++;
    for (int i=0; i<len; i++) {
        c[i] = 0;
        for (int j=0; j<len; j++)
            if (a[j] < a[i]) c[i] ++;
        printf("%d ", c[i]);
    }
    return 0;
}