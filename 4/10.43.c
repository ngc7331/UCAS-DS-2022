/*
# 10.43-计数排序
## 描述
已知记录序列a[1..n]中的关键字各不相同，可按如下所述实现计数排序：另设数组c[1..n]，对每个记录a[i]，统计序列中关键字比它小的记录个数存于c[i]，则c[i]=0的记录必为关键字最小的记录，然后依c[i]值的大小对a中的记录进行重新排列，试编写算法实现上述排序方法。

## 输入
输入记录序列a

## 输出
输出c中每个元素

## 样例1
### 输入
4 3 10 2 1

### 输出
3 2 4 1 0

*/

#include <stdio.h>

#define MAXLENGTH 10000

int main(int argc, char *argv[]) {
    int a[MAXLENGTH], c[MAXLENGTH], len=0;
    while (scanf("%d", &a[len]) == 1) len ++;
    for (int i=0; i<len; i++) {
        c[i] = 0;
        for (int j=0; j<len; j++)
            if (a[j] < a[i]) c[i] ++;
        printf("%d ", c[i]);
    }
    return 0;
}