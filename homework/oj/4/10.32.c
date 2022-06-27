#include <stdio.h>

int main(int argc, char *argv[]) {
    int count[3] = {0, 0, 0};
    int x;
    while (scanf("%d", &x) == 1) count[x-1] ++;
    for (int i=0; i<3; i++)
        for (int j=0; j<count[i]; j++)
            printf("%d ", i+1);
    return 0;
}