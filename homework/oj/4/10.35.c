#include <stdio.h>

#define MAXHEAPSIZE 10000
#define NEGINFINITE 0x80000000

#define left(a)   (3*a + 1)
#define middle(a) (3*a + 2)
#define right(a)  (3*a + 3)

#define MAX(a, b) ((a)>(b)?(a):(b))

void swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int biggestChild(int heap[], int i, int len) {
    int l = left(i), m = middle(i), r = right(i);
    int ln = heap[l], mn = heap[m], rn = heap[r];
    if (ln >= mn || m >= len) {
        if (ln >= rn || r >= len) return l;
        return r;
    }
    if (mn >= rn || r >= len) return m;
    return r;
}

int main(int argc, char *argv[]) {
    int heap[MAXHEAPSIZE], len=0;
    while (scanf("%d", &heap[len]) == 1) len++;
    // 建大顶堆
    for (int i=len/3-1; i>=0; i--) {
        int j = i;
        while (left(j) < len) {  // 非叶
            int b = biggestChild(heap, j, len);
            if (heap[j] < heap[b]) {
                swap(heap, j, b);
                j = b;
            }
            else break;
        }
    }

    // 堆排序
    for (int i=len-1; i>=0; i--) {
        swap(heap, 0, i);
        int j = 0;
        while (left(j) < i) {
            int b = biggestChild(heap, j, i);
            if (heap[j] < heap[b]) {
                swap(heap, j, b);
                j = b;
            }
            else break;
        }
    }

    // 输出
    for (int i=0; i<len; i++) {
        printf("%d%c", heap[i], i==len-1? '\n' : ' ');
    }

    return 0;
}