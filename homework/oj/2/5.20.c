#include <stdio.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int P[m][n];
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            scanf("%d", &P[i][j]);
    for (int i=m-1; i>=0; i--) {
        for (int j=n-1; j>=0; j--) {
            if (!P[i][j]) continue;
            if (P[i][j] != 1) printf("%d", P[i][j]);
            if (i) printf("xE%d", i);
            if (j) printf("yE%d", j);
            if (i || j) printf("+");
        }
    }
    return 0;
}