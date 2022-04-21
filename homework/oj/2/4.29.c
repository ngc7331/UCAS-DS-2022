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
