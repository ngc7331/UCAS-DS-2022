/*
# 6-犯罪案件判定
## 描述
城市有两个犯罪团伙A，B。已知有N (<100,000)起案件，M (<100,000)条案件线索，案件线索形如 案件X和案件Y属于不同团伙所为。现在，任给两个案件，请帮助警察判断这两个案件是不是同一个团伙所为。回答为“是”、“不是”或“不确定”。

## 输入
第一行是测试数据的组数T（1<=T<=20）。
每组测试数据的第一行包括两个数N和M，分别表示案件的数量和信息的数量，其后M行表示按时间顺序收到的M条信息。这M条信息分两类，形如：
D a b表示：案件a和案件b属于不同的团伙所为。
A a b表示：询问案件a和案件b是否属于同一个团伙所为。

## 输出
对于每条需要回答的信息，你需要输出一行答案。如果是同一个团伙所为，回答“是同一个团伙所为”，如果不是，回答“不是同一个团伙所为”，如果不确定，回答“不确定”。

## 样例1
### 输入
1
5 5
A 1 2
D 1 2
A 1 2
D 2 4
A 1 4

### 输出
不确定
不是同一个团伙所为
是同一个团伙所为

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct __node{
    struct __node *parent;
    struct __node *neg;
} node;

void swap(int *a, int *b) {
    int c = *a;
    *a = *b, *b = c;
}

void build(node *incident[], int a, int b) {
    // a and b belongs to different group
    // 1. a and b are noth unknown
    if (incident[a] == NULL && incident[b] == NULL) {
        incident[a] = (node *) malloc(sizeof(node));
        incident[b] = (node *) malloc(sizeof(node));
        incident[a]->parent = NULL;
        incident[b]->parent = NULL;
        incident[a]->neg = incident[b];
        incident[b]->neg = incident[a];
    }
    // 2. a and b are both known
    else if (incident[a] != NULL && incident[b] != NULL) {
        node *aroot = incident[a];
        node *broot = incident[a];
        while (aroot->parent != NULL) aroot = aroot->parent;
        while (broot->parent != NULL) broot = broot->parent;
        aroot->parent = broot->neg;
        aroot->neg->parent = broot;
    }
    // 3. a or b is known
    else {
        if (incident[a] == NULL)
            swap(&a, &b);
        // now a is known and b is unknown
        incident[b] = incident[a]->neg;
    }
}

void check(node *incident[], int a, int b) {
    if (incident[a] == NULL || incident[b] == NULL)
        printf("不确定\n");
    else {
        node *aroot = incident[a];
        node *broot = incident[b];
        while (aroot->parent != NULL) aroot = aroot->parent;
        while (broot->parent != NULL) broot = broot->parent;
        if (aroot == broot)
            printf("是同一个团伙所为\n");
        else if (aroot == broot->neg)
            printf("不是同一个团伙所为\n");
        else
            printf("不确定\n");
    }
}

void problem() {
    int n, m;
    scanf("%d %d\n", &n, &m);
    node *incident[m];
    for (int i=0; i<m; i++) incident[i] = NULL;
    for (int i=0; i<n; i++) {
        char tp;
        int a, b;
        scanf("%c %d %d\n", &tp, &a, &b);
        a--, b--;
        if (tp == 'D') {
            build(incident, a, b);
        } else if (tp == 'A') {
            check(incident, a, b);
        }
    }

}

int main(int argc, char *argv[]) {
    int t;
    scanf("%d", &t);
    while (t--)
        problem();
    return 0;
}