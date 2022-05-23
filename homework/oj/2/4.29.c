/*
# 4.29-串匹配的改进算法
## 描述
假设以结点大小为1（带头结点）的链表结构表示串，则在利用next函数值进行串匹配时，在每个结点中需设三个域：数据域chdata、指针域succ和指针域next。其中chdata域存放一个字符；succ域存放指向同一链表中后继结点的指针；next域在主串中存放指向同一链表中前驱结点的指针；在模式串中，存放指向当该结点的字符与主串中的字符不等时，在模式串中下一个应进行比较的字符结点（即与该字符的next函数值相对应的字符结点）的指针，若该节点字符的next函数值为0，则其next域的值应指向头结点。试按上述定义的结构改写串匹配的改进算法（KMP算法）。

## 输入
输入分为三行，第一行输入两个数，分别为待搜索串的长度和目标串的长度。
第二行表示待搜索串的元素序列。
第三行表示目标串的元素序列。

## 输出
若能在待搜索串中匹配到目标串，则输出目标串的第一个字符在待搜索串中的位置（从0开始）；若不能，则输出-1。

## 样例1
### 输入
7 3
samples
sam

### 输出
0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct __HChar {
    char ch;
    struct __HChar *succ, *next;
} HChar;

typedef struct {
    HChar *head, *tail;
    int length;
} HString;

int StrInit(HString *s) {
    s->head = (HChar *) malloc(sizeof(HChar));
    s->head->succ = NULL;
    s->head->next = NULL;
    s->tail = s->head;
    s->length = 0;
    return 0;
}

int StrAssign(HString *s, char *sc) {
    int len = 0;
    while (sc[len] != '\0' && sc[len] != '\n') len++;
    for (int i=0; i<len; i++) {
        HChar *n = (HChar *) malloc(sizeof(HChar));
        n->ch = sc[i];
        n->next = s->tail;
        n->succ = NULL;
        s->tail->succ = n;
        s->tail = n;
    }
    s->length = len;
    return 0;
}

void GetNext(HString *p) {
    HChar *j = p->head->succ, *k = p->head;
    while (j->succ != NULL) {
        if (k==p->head || j->ch==k->ch) {
            j = j->succ; k = k->succ;
            if (j->ch == k->ch) j->next = k->next;
            else j->next = k;
        }
        else k = k->next;
    }
}

int StrIndexKMP(HString *s, HString *p) {
    GetNext(p);
    int res = -1;
    HChar *i = s->head, *j = p->head->succ;
    while (i!=NULL && j!=NULL) {
        if (j==p->head || i->ch==j->ch) {
            i = i->succ; j = j->succ;
            res ++;
        }
        else j = j->next;
    }
    if (i == NULL && j != NULL) return -1;
    return res - p->length;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    HString s, p;
    char tmp[10000];
    StrInit(&s), StrInit(&p);
    scanf("%s", tmp);
    StrAssign(&s, tmp);
    scanf("%s", tmp);
    StrAssign(&p, tmp);
    int res = StrIndexKMP(&s, &p);
    printf("%d\n", res);
}
