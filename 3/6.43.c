/*
# 6.43-二叉树左右子树交换
## 描述
编写递归算法，将二叉树中所有节点的左、右子树相互交换。
例如，

*image deleted*
转化为
*image deleted*

## 输入
完整的二叉树，具体表示形式如下：
假定用两个一维数组$L[n+1]$和$R[n+1]$作为有$n$个节点的二叉树的存储结构，$L[i]$和$R[i]$分别指示节点$i(i=1,2,...,n)$的左孩子和右孩子，0表示空。
例如，给定数组
L = 1 2 4 0 0 0
R = 1 3 5 0 0 0
数组表示的二叉树的示意图如下：

*image deleted*


注意：L和R的第一个元素为根节点。上例中，L[0]=R[0]=1，表示根节点为1。

## 输出
输出翻转左右子树后的树，使用输入的格式进行输出。

## 样例1
### 输入
1 2 4 0 0 0
1 3 5 0 0 0

### 输出
1 3 5 0 0 0
1 2 4 0 0 0

## 样例2
### 输入
1 2 3 0
1 0 0 0

### 输出
1 0 0 0
1 2 3 0

*/

#include <stdio.h>

#define TREEMAXNODE 1000
#define CACHESIZE 10000

void swapLR(int *L, int *R, int i) {
    if (i == 0) return ;
    swapLR(L, R, L[i]);
    swapLR(L, R, R[i]);
    int tmp = L[i];
    L[i] = R[i];
    R[i] = tmp;
}

int main(int argc, char *argv[]) {
    int L[TREEMAXNODE], R[TREEMAXNODE];
    char tmp[CACHESIZE], *tmpp = tmp;
    int offset;
    int i = 0, length;
    // input
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &L[i++], &offset) == 1) {
        tmpp += offset;
    }
    length = i-1;
    tmpp = tmp;
    i = 0;
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &R[i++], &offset) == 1) {
        tmpp += offset;
    }

    // swap
    swapLR(L, R, 1);

    // output
    for (i=0; i<length; i++) {
        printf("%d%c", L[i], i==length-1?'\n':' ');
    }
    for (i=0; i<length; i++) {
        printf("%d%c", R[i], i==length-1?'\n':' ');
    }
    return 0;
}