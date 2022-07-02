/*
# 6.71 凹入表打印树结构
## 描述
假设树上每个结点所含的数据元素为一个字母，并且以孩子-兄弟链表为树的存储结构，试写一个按凹入表方式打印一棵树的算法。如下例，
树结构

*image deleted*


对应的凹入表

*image deleted*

## 输入
输入为 $n$ 行，表示 $n$ 个节点的信息。
第 $i， i\in[1, n]$ 行为节点 $i$ 的信息，包括一个字符 $c$ 和两个数字 $p$ 和 $q$， 这表示第 $i$ 个节点的内容为字符 $c$, 其一个子节点为 $p$, **下一个兄弟**为 $q$。空节点使用 -1 表示。

## 输出
凹入表（具体格式如样例所示,用连接符表示层次关系）。

## 样例1
### 输入
A 2 -1
B 5 3
C 7 4
D -1 -1
E -1 6
F -1 -1
G -1 -1

### 输出
A
-B
--E
--F
-C
--G
-D

## 样例2
### 输入
A 2 -1
B 3 -1
C -1 -1

### 输出
A
-B
--C

*/

#include <stdio.h>

#define TREEMAXNODE 1000

typedef struct {
    char e;
    int left, right;
} tnode;

typedef struct {
    tnode node[TREEMAXNODE];
    int size;
} SqBiTree;

void PrintHyphen(int num) {
    while (num--) printf("-");
}

void PrintRecessedTable(SqBiTree t, int i, int depth) {
    // arg: t is a child-sibling tree
    while (i != -1) {
        PrintHyphen(depth); printf("%c\n", t.node[i].e);
        PrintRecessedTable(t, t.node[i].left, depth+1);
        i = t.node[i].right;
    }
}

int main(int argc, char *argv[]) {
    char e;
    int left, right;
    SqBiTree t;
    t.size = 0;
    while (scanf("%c %d %d\n", &e, &left, &right) == 3) {
        t.node[t.size+1].e = e;
        t.node[t.size+1].left = left;
        t.node[t.size+1].right = right;
        t.size ++;
    }

    PrintRecessedTable(t, 1, 0);

    return 0;
}