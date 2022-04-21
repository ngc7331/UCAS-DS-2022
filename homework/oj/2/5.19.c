#include <stdio.h>
#define INFINITE 9999999

void initArray(int *a, int n, int data) {
    for (int i=0; i<n; i++)
        a[i] = data;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int A[m][n];
    int lmin[m]; initArray(lmin, m, INFINITE);
    int data;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d", &data);
            if (data < lmin[i])
                lmin[i] = data;
            A[i][j] = data;
        }
    }
    for (int j=0; j<n; j++) {
        int cmax = -INFINITE;
        int k = -1;
        for (int i=0; i<m; i++) {
            if (A[i][j] > cmax)
                cmax = A[i][j], k = i;
        }
        if (lmin[k] == cmax)
            printf("%d ", cmax);
    }
    // 最坏情况时间复杂度为 O(m*n)
    return 0;
}