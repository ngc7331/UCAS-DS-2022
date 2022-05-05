#include <stdio.h>

#define TREEMAXNODE 1000
#define CACHESIZE 10000

void swapLR(int *L, int *R, int i) {
    if (i == 0) return ;
    swapLR(L, R, L[i]);
    swapLR(L, R, R[i]);
    int tmp = L[i];
    L[i] = R[i];
    R[i] = tmp;
}

int main(int argc, char *argv[]) {
    int L[TREEMAXNODE], R[TREEMAXNODE];
    char tmp[CACHESIZE], *tmpp = tmp;
    int offset;
    int i = 0, length;
    // input
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &L[i++], &offset) == 1) {
        tmpp += offset;
    }
    length = i-1;
    tmpp = tmp;
    i = 0;
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &R[i++], &offset) == 1) {
        tmpp += offset;
    }

    // swap
    swapLR(L, R, 1);

    // output
    for (i=0; i<length; i++) {
        printf("%d%c", L[i], i==length-1?'\n':' ');
    }
    for (i=0; i<length; i++) {
        printf("%d%c", R[i], i==length-1?'\n':' ');
    }
    return 0;
}