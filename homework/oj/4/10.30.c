#include <stdio.h>

#define STACKSIZE 100
#define MAXLENGTH 10000

typedef struct {
    int left, right;
} info;

typedef struct {
    info data[STACKSIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isStackEmpty(Stack s) {
    return s.top == -1;
}

void Push(Stack *s, info data) {
    if (s->top == STACKSIZE-1) return ;
    s->data[++s->top] = data;
}

void Pop(Stack *s, info *data) {
    if (s->top == -1) return ;
    *data = s->data[s->top--];
}

void swap(int a[], int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

void quickSort(int a[], int len) {
    Stack s;
    initStack(&s);
    info current = {0, len-1};
    Push(&s, current);
    while (!isStackEmpty(s)) {
        Pop(&s, &current);
        int i=current.left, j=current.right;
        if (j - i + 1 <= 3) {
            if (a[i] > a[j]) swap(a, i, j);
            if (a[i] > a[(i+j)/2]) swap(a, i, (i+j)/2);
        }
        else {
            while (i < j) {
                while (a[j] > a[i]) j--;
                swap(a, i, j);
                if (i >= j) break;
                while (a[i] < a[j]) i++;
                swap(a, i, j);
            }
            info l = {current.left, i-1};
            info r = {j+1, current.right};
            Push(&s, l);
            Push(&s, r);
        }
    }
}

int main(int argc, char *argv[]) {
    int a[MAXLENGTH], len=0;
    while (scanf("%d", &a[len]) == 1) len++;
    quickSort(a, len);
    for (int i=0; i<len; i++)
        printf("%d%c", a[i], i==len-1?'\n':' ');
    return 0;
}