#include "../ds.h"
#include <stdlib.h>

#define INITHSSIZE 100

typedef struct {
    char *ch;
    int length, size;
} HString;

// 1.初始化串
Status StrInit(HString *s) {
    s->ch = (char *) malloc(INITHSSIZE * sizeof(char));
    if (s->ch == NULL) return ERROR;
    s->ch[0] = '\0';
    s->length = 0;
    s->size = INITHSSIZE;
    return OK;
}

Status StrResize(HString *s, int size) {
    s->ch = realloc(s, (size + 1) * sizeof(char));
    if (s->ch == NULL) return ERROR;
    s->size = size + 1;
    return OK;
}

// 2. 获取串的长度
int StrLen(HString *s) {
    return s->length;
}

// 3. 比较两个串是否相等
Status IsStrEqual(HString *s, HString *t);
// 4. 比较两个串
int StrComp(HString *s, HString *t);

//5. 将字符串常量sc赋给字符串变量s
Status StrAssign(HString *s, char *sc) {
    int len = 0;
    while (sc[len] != '\0') len++;
    if (len >= s->size)
        if (StrResize(s, len) == ERROR) return ERROR;
    for (int i=0; i<len; i++)
        s->ch[i] = sc[i];
    s->ch[len] = '\0';
    s->length = len;
    return OK;
}

//6. 将s1和 s2拼接成s
Status StrConcat(HString *s,HString *s1, HString *s2); 
//7. 取子串，将s中从第i个字符开始的连续j个字符放到subs
Status StrSubstr(HString *subs, HString *s,int i,int j); 
//8. 在s的第i个字符之前插入字符串t 
Status StrInsert (HString *s,int i,HString *t); 
//9. 删除s的第i个字符开始的连续j个字符
Status StrDelete(HString *s,int i,int j); 
//10. 串替换，将s从第i个字符开始j个连续字符用字符串t替换
Status StrReplace (HString *s,int i,int j,HString *t); 
//11. 将字符串变量的值赋给字符串变量s
Status StrCopy(HString *s,HString *t); 

/*
void prints(HString *s) {
    HChar *p = s->head->succ;
    while (p!=NULL) {
        printf("%c", p->ch);
        p = p->succ;
    }
}

void StrDestroy(HString *s) {
    HChar *p=s->head, *pp;
    while (p!=NULL) {
        pp = p;
        p = p->succ;
        free(pp);
    }
}

void SubStr(HString *s, HString *sub, int a, int b) {
    // sub = s[a:b], from 0, include a, not include b
    StrDestroy(sub); StrInit(sub);
    sub->length = b-a+1;
    int i=0;
    HChar *p = s->head->succ;
    while (i++ < a && p!=NULL) p=p->succ;
    while (i++ <= b && p!=NULL) {
        HChar *n = (HChar *) malloc(sizeof(HChar));
        n->ch = p->ch;
        n->next = sub->tail;
        n->succ = NULL;
        sub->tail->succ = n;
        sub->tail = n;
        p = p->succ;
    }
}
*/
