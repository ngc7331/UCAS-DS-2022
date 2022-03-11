// 括号配对示例
#include <stdio.h>
#include "../ds.h"

#define __ELEMTYPE_DEF
typedef char ElemType;

/* 动态顺序栈 */
// #include "SqStack.c"
// SqStack s;

/* 静态顺序栈 */
#include "SSqStack.c"
SSqStack s;

int main() {
    char c, tmp;
    int flag = TRUE;
    InitStack(&s);
    while ((c=getchar())!=EOF && c!='\n') {
        if (c=='(') {
            if (Push(&s, c) == ERROR) {
                printf("Push failed");
                flag = FALSE;
                break;
            }
        }
        else if (c!=')' || Pop(&s, &tmp) == ERROR) {
            flag = FALSE;
            break;
        }
    }
    if (IsStackEmpty(&s) && flag) printf("\nOK\n");
    else printf("\nERROR\n");
    return 0;
}
