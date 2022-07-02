/*
# 7.25-判断有向图是否存在回路
## 描述
假设对有向图中n个顶点进行自然编号，并以三个数组$s[1..max]$，$fst[1..n]$和$lst[1..n]$表示之。其中数组$s$存放每个顶点的后继顶点的信息，第i个顶点的后继顶点存放在$s$中下标从$fst[i]$起到$lst[i]$的分量中（$i=1,2,...,n$）不包含$lst[i]$本身。若$fst[i]>lst[i]$，则第$i$个顶点无后继顶点。试编写判别该有向图中是否存在回路的算法。

## 输入
输入第一行为顶点个数
第二行为数组s
第三行为数组fst
第四行为数组lst
$s$，$fst$，$lst$的第一个元素都为0，仅为占用0位置，从下标1开始为第1个顶点的信息。d

## 输出
输出有向图是否存在回路，存在输出yes，不存在输出no

## 样例1
### 输入
3
0 2 3 3 1 1 2
0 1 3 5
0 3 5 7

### 输出
yes

## 样例2
### 输入
6
0 2 3 4 5 6
0 1 8 21 42 99 100
0 6 1 1 1 98 2

### 输出
no

*/

#include <stdio.h>

#define MAXNODENUM 1000
#define CACHESIZE 10000

typedef enum {
    False,
    True,
} Bool;

void initArray(int array[], int length) {
    while (length)
        array[--length] = 0;
}

Bool hasLoop(int s[], int fst[], int lst[], int visited[], int n) {
    if (visited[n] == 1) return True;
    visited[n] = 1;
    for (int i=fst[n]; i<lst[n]; i++) {
        if (hasLoop(s, fst, lst, visited, s[i]))
            return True;
    }
    visited[n] = 0; // failed to find loop, release
    return False;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d\n", &n);
    int s[MAXNODENUM], fst[n+1], lst[n+1], visited[n+1];
    char tmp[CACHESIZE], *tmpp=tmp;
    int i=0, offset;
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &s[i++], &offset) == 1)
        tmpp += offset + 1;
    for (i=0; i<=n; i++)
        scanf("%d", &fst[i]);
    for (i=0; i<=n; i++)
        scanf("%d", &lst[i]);

    Bool has_loop = False;
    for (int i=1; i<=n; i++) {
        initArray(visited, n+1);
        if (hasLoop(s, fst, lst, visited, i)) {
            has_loop = True;
            break;
        }
    }
    printf("%s", has_loop ? "yes" : "no");
    return 0;
}