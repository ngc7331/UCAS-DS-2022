#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHESIZE 10000

typedef char AtomType;
typedef enum {ATOM, LIST} ElemTag;
typedef struct __GLNode {
    ElemTag tag;
    union {
        AtomType atom;
        struct {
            struct __GLNode *hp, *tp;
        } ptr;
    };
} GLNode, *Glist;

char *subStr(char *src, int a, int b) {
    char *dst = (char *) malloc(b-a+1);
    for (int i=a, j=0; i<b; i++, j++)
        dst[j] = src[i];
    dst[b-a] = '\0';
    return dst;
}

void InitGlist(Glist *l) {
    *l = (Glist) malloc(sizeof(GLNode));
    (*l)->tag = LIST;
    (*l)->ptr.hp = (*l)->ptr.tp = NULL;
}

void InputGlist(char *input, Glist l) {
    if (strlen(input) == 0) {
        l->tag = LIST;
        l->ptr.hp = l->ptr.tp = NULL;
        return ;
    }
    ElemTag tp = ATOM;
    int s = 0;
    int b = 0;
    GLNode *p = l;
    for (int i=0; i<strlen(input); i++) {
        if (input[i] == '(') {
            if (tp == ATOM) {
                s = i;
                tp = LIST;
            }
            b++;
        }
        else if (input[i] == ')') {
            b--;
            if (!b) {
                char *sub = subStr(input, s+1, i);
                GLNode *n; InitGlist(&n);
                InputGlist(sub, n);
                p->ptr.hp = n;
                free(sub);
                tp = ATOM;
            }
        }
        else if (input[i] == ',' && !b) {
            GLNode *n; InitGlist(&n);
            p->ptr.tp = n;
            p = n;
        }
        else if (tp == ATOM) {
            GLNode *n; InitGlist(&n);
            n->tag = ATOM;
            n->atom = input[i];
            p->ptr.hp = n;
        }
    }
    if (tp == LIST) {
        char *sub = subStr(input, s+1, strlen(input)-1);
        GLNode *n; InitGlist(&n);
        InputGlist(sub, n);
        p->ptr.hp = n;
        free(sub);
    }
}

int isEmpty(Glist l) {
    if (l == NULL)
        return 1;
    if (l->tag == ATOM)
        return 0;
    int is_empty = 1;
    GLNode *p = l;
    while (p != NULL) {
        if (!isEmpty(p->ptr.hp))
            is_empty = 0;
        p = p->ptr.tp;
    }
    return is_empty;
}

Glist GlistDel(Glist l, char del) {
    if (l == NULL || l->tag == ATOM && l->atom == del)
        return NULL;
    if (l->tag == LIST) {
        l->ptr.hp = GlistDel(l->ptr.hp, del);
        l->ptr.tp = GlistDel(l->ptr.tp, del);
    }
    return l;
}

int PrintGlist(Glist l) {
    if (isEmpty(l))
        return 1;
    int is_empty = 0;
    if (l->tag == ATOM)
        printf("%c", l->atom);
    else {
        printf("(");
        GLNode *p = l;
        while (p != NULL) {
            is_empty = PrintGlist(p->ptr.hp);
            p = p->ptr.tp;
            if (!is_empty && !isEmpty(p))
                printf(",");
        }
        printf(")");
    }
    return 0;
}

int main() {
    char tmp[CACHESIZE];
    char del;
    scanf("%s %c", tmp, &del);
    Glist l; InitGlist(&l);
    InputGlist(subStr(tmp, 1, strlen(tmp)-1), l);
    GlistDel(l, del);
    if (PrintGlist(l))
        printf("-1\n");
    return 0;
}