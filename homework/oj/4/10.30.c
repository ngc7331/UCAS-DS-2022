/*
# 10.30-快排非递归
## 描述
按照下述原则编写快排的非递归算法：
（1）一趟排序之后，先对长度较短的子序列进行排序，且将另一子序列的上、下界入栈保存
（2）若待排序记录数<=3，则不再进行分割，而是直接进行比较排序

## 输入
输入待排序列

## 输出
输出排序完成后的序列

## 样例1
### 输入
18 39 21 23 9 1

### 输出
1 9 18 21 23 39

*/

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