#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 10000
#define RADIX 10

typedef struct __node {
    int data;
    struct __node *next;
} Node, *List;

Node *newNode() {
    Node *n = (Node *) malloc(sizeof(Node));
    n->next = NULL;
    return n;
}

void alloc(List f[], List e[], int data[], int len, int key(int)) {
    for (int i=0; i<len; i++) {
        int k = key(data[i]);
        if (f[k] == NULL) {
            f[k] = e[k] = newNode();
            f[k]->data = data[i];
        }
        else {
            e[k]->next = newNode();
            e[k] = e[k]->next;
            e[k]->data = data[i];
        }

    }
}

void collect(List f[], List e[], int data[], int len) {
    for (int i=0, l=0; i<RADIX && l<len; i++) {
        while (f[i]) {
            data[l++] = f[i]->data;
            f[i] = f[i]->next;
        }
    }
}

void sort(int data[], int len, int key(int)) {
    List f[RADIX], e[RADIX];
    for (int i=0; i<RADIX; i++)
        f[i] = e[i] = NULL;
    alloc(f, e, data, len, key);
    collect(f, e, data, len);
}

int f0(int data) {
    return data % 10;
}
int f1(int data) {
    return (data / 10) % 10;
}
int f2(int data) {
    return (data / 100) % 10;
}

int main(int argc, char *argv[]) {
    int a[MAXLENGTH], len=0;
    while (scanf("%d", &a[len]) == 1) len ++;
    sort(a, len, f0);
    sort(a, len, f1);
    sort(a, len, f2);
    for (int i=0; i<len; i++)
        printf("%d ", a[i]);
    return 0;
}
