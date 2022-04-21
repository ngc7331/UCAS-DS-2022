#include <stdio.h>
#include "../3.string/HString.c"

void GetNext(HString *p, int next[]) {
    int j = 0, k = -1;
    next[0] = -1;
    while (j < p->length) {
        if (k==-1 || p->ch[j]==p->ch[k]) {
            j++; k++;
            if (p->ch[j] == p->ch[k]) next[j] = next[k];
            else next[j] = k;
        }
        else k = next[k];
    }
}

int StrIndexKMP(HString *s, HString *p, int start) {
    int next[p->length];
    GetNext(p, next);
    int i = start, j = 0;
    while (i < s->length && j < p->length) {
        if (j==-1 || s->ch[i]==p->ch[j]) {
            i++; j++;
        }
        else j = next[j];
    }
    if (i == s->length && j != p->length) return -1;
    else return i - p->length;
}

int main() {
    HString s, p;
    StrInit(&s), StrInit(&p);
    StrAssign(&s, "abcaabcabdab");
    StrAssign(&p, "abc");
    int res = StrIndexKMP(&s, &p, 0);
    printf("%d\n", res);
}
