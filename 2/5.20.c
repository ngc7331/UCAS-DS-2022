/*
# 5.20-将数组表示的多项式的形式输出
## 描述
试编写一个算法将ｍ维数组表示的ｍ元多项式以常规表示的形式(按降幂顺序)输出。可将其中一项$c_kx^{e_1}_1x^{e_2}_2\cdots x^{e_m}_m$印成$c_kx_1Ee_1x_2Ee_2\cdots x_mEe_m$(其中ｍ,$c_k$和$e_j$(j=1,2,...,m)印出它们具体的值)，当$c_k$或$e_j$为１时，<span style="color: rgb(51, 51, 51);">$c_k$的值或“E”和$e_j$<span style="color: rgb(51, 51, 51);">的值可省略不印。</span></span>
<span style="color: rgb(51, 51, 51);"><span style="color: rgb(51, 51, 51);">提示: 本题假设输入的数组的维数为二维，且以x,y顺次为主序，即本题的多项式形式为二元多次。<span style="color: rgb(51, 51, 51);">当$e_j$为１时，“E”和$e_j$的值是打印出来的，<span style="color: rgb(51, 51, 51);">当$c_k$为０时，即系数为零，这一项是不需要打印出来的，每一项之间都通过"+"相连，具体<span style="color: rgb(51, 51, 51);">以样例为准。</span></span></span></span></span>

## 输入
输入为两部分:
第一部分在第一行，输入二维数组的行数与列数，其中行数代表x的指数，列数则比代表ｙ的指数
第二部分是从第二行起逐行读入二维数组中各个元素的值，代表各个项前的系数

## 输出
输出：将二元多次多项式按样例显示的形式输出

## 样例1
### 输入
3 3
2 0 4
-1 3 0
1 0 0

### 输出
xE2+3xE1yE1+-1xE1+4yE2+2

*/

#include <stdio.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int P[m][n];
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            scanf("%d", &P[i][j]);
    for (int i=m-1; i>=0; i--) {
        for (int j=n-1; j>=0; j--) {
            if (!P[i][j]) continue;
            if (P[i][j] != 1) printf("%d", P[i][j]);
            if (i) printf("xE%d", i);
            if (j) printf("yE%d", j);
            if (i || j) printf("+");
        }
    }
    return 0;
}