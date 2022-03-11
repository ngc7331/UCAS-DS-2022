#include <stdio.h>

void swap(int *x, int i, int j) {
    int tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
}

int main() {
    int x[3];
    for (int i=0; i<3; i++) {
        scanf("%d", &x[i]);
        for (int j=0; j<i; j++) {
            if (x[i] > x[j]) swap(x, i, j);
        }
    }
    for (int i=0; i<3; i++) printf("%d ", x[i]);
    return 0;
}