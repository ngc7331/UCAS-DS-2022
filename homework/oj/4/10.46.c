#include <stdio.h>

#define MAXLENGTH 10000
#define INFINITE 0x7fffffff

typedef struct {
    int key;
    // record
} rec;

int main(int argc, char *argv[]) {
    int len;
    rec a[MAXLENGTH], b[MAXLENGTH];
    int selected[MAXLENGTH];
    scanf("%d", &len);
    for (int i=0; i<len; i++) {
        selected[i] = 0;
        scanf("%d", &b[i].key);
    }
    int min, minj;
    for (int i=0; i<len; i++) {
        min = INFINITE;
        for (int j=0; j<len; j++)
            if (!selected[j] && b[j].key < min)
                min = b[j].key, minj = j;
        a[i] = b[minj];
        selected[minj] = 1;
    }
    for (int i=0; i<len; i++)
        printf("%d ", a[i].key);
    return 0;
}