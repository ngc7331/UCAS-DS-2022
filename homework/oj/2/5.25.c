#include <stdio.h>
#include <stdlib.h>

#define CACHESIZE 10000

// T(m, n) = O(m * n)

int main() {
    int m, n;
    int x, offset;
    char B1[10000][10000], B2;
    char *tmp = malloc(CACHESIZE+1);
    scanf("%d %d", &m, &n);
    // get A1
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmp, "%d%n", &x, &offset) == 1) {
        tmp += offset;
        // TODO
    }
    // get B1
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            scanf("%d", B1[i][j]);
    // get A2
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmp, "%d%n", &x, &offset) == 1) {
        tmp += offset;
        // TODO
    }
    // get B2 & caculate
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d", B2);
            if (B2 & B1[i][j]) {
                // 均非零
            }
            else if (B2 | B1[i][j]) {
                // 仅一个矩阵非零
            }
        }
    }
    return 0;
}