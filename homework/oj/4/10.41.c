// counting sort

#include <stdio.h>

int main(int argc, char *argv[]) {
    int count[10000];
    for (int i=0; i<10000; i++)
        count[i] = 0;
    int x;
    while (scanf("%d", &x) == 1) count[x] ++;
    for (int i=0; i<10000; i++)
        for (int j=0; j<count[i]; j++)
            printf("%d ", i);
    return 0;
}
