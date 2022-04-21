#include <stdio.h>
#include <stdlib.h>

#define INITHSSIZE 100

typedef struct {
    char *ch;
    int length, size;
} HString;

int StrInit(HString *s) {
    s->ch = (char *) malloc(INITHSSIZE * sizeof(char));
    if (s->ch == NULL) return 1;
    s->ch[0] = '\0';
    s->length = 0;
    s->size = INITHSSIZE;
    return 0;
}

int StrResize(HString *s, int size) {
    if (size < s->size) return 0;
    s->ch = realloc(s, (size + 1) * sizeof(char));
    if (s->ch == NULL) return 1;
    s->size = size + 1;
    return 0;
}

int StrAssign(HString *s, char *sc) {
    int len = 0;
    while (sc[len] != '\0') len++;
    if (len >= s->size)
        if (StrResize(s, len) == 1) return 1;
    for (int i=0; i<len; i++)
        s->ch[i] = sc[i];
    s->ch[len] = '\0';
    s->length = len;
    return 0;
}

void StrDestroy(HString *s) {
    free(s->ch);
    s->length = s->size = 0;
}

void SubStr(HString *s, HString *sub, int a, int b) {
    // sub = s[a:b], from 0, include a, not include b
    StrDestroy(sub); StrInit(sub);
    StrResize(sub, b-a);
    sub->length = b-a;
    for (int i=a, j=0; i<b; i++, j++) {
        sub->ch[j] = s->ch[i];
    }
}

/* START KMP */
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
    return i - p->length;
}
/* END KMP */

int main() {
    HString s, sub;
    char tmp[10000];
    int found=0;
    StrInit(&s);
    scanf("%s", tmp);
    StrAssign(&s, tmp);
    int i, j;
    for (i=s.length-1; i>0; i--) { // i: length
        for (j=0; j<s.length-i; j++) { // j: start of the substr
            SubStr(&s, &sub, j, i+j);
            if (StrIndexKMP(&s, &sub, j+1) != -1) {
                found = 1;
                break;
            }
        }
        if (found) break;
    }
    if (i==0) printf("-1");
    else printf("%s %d", sub.ch, j);
}
