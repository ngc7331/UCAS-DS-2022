/*
# 4.10-字符串求逆
## 描述
编写对串求逆的递推算法。

## 输入
原始字符串

## 输出
求逆之后的字符串

## 样例1
### 输入
abcde

### 输出
edcba

*/

#include <stdio.h>
#include <string.h>

void swap(char *s, int a, int b) {
    char tmp = s[a];
    s[a] = s[b];
    s[b] = tmp;
}

void reverse(char *s) {
    int len = strlen(s);
    if (s[len-1] == '\n') len--;
    for (int i=0; i<len/2; i++)
        swap(s, i, len-i-1);
}

int main() {
    char s[1000];
    fgets(s, 1000, stdin);
    reverse(s);
    printf("%s", s);
    return 0;
}