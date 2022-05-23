#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CACHESIZE 10000

typedef enum {
    FREE,
    USED
} TAG;

#define M 16
typedef struct __word {
    struct __word *llink;  // 前驱
    TAG tag;               // 占用标识
    int k;                 // 块大小，2的指数
    int start;             // 起始地址
    struct __word *rlink;  // 后继
} WORD;
typedef struct {
    int nodesize;
    WORD *first;
} FreeList[M+1];

WORD *newWord(TAG tag, int k, int start) {
    WORD *p = (WORD *) malloc(sizeof(WORD));
    p->llink = p->rlink = NULL;
    p->tag = tag;
    p->k = k;
    p->start = start;
    return p;
}

void initFreeList(FreeList l) {
    for (int i=1; i<=M; i++) {
        l[i].first = NULL;
        l[i].nodesize = 0;
    }
}

void createFreeSpace(FreeList l, int k, int start) {
    WORD *p = newWord(FREE, k, start);
    l[k].nodesize ++;
    WORD *pp = l[k].first;
    while (pp != NULL && pp->start < start) pp = pp->rlink;
    if (pp == NULL) {
        if (pp == l[k].first)
            l[k].first = p;
        else {
            pp = l[k].first;
            while (pp->rlink != NULL) pp = pp->rlink;  // find the last node
            pp->rlink = p;
            p->llink = pp;
        }
    } else {
        p->rlink = pp;
        if (pp == l[k].first)
            l[k].first = p;
        else {
            p->llink = pp->llink;
            pp->llink->rlink = p;
        }
        pp->llink = p;
    }
}

int getBuddy(int k, int start) {
    int size = pow(2, k);
    return start % (size*2) == 0 ? start+size : start-size;
}

void freeBlock(FreeList l, int k, int start) {
    WORD *pp = l[k].first;
    while (pp != NULL && pp->start < start) pp = pp->rlink;
    if (pp == NULL) {
        if (pp == l[k].first)
            l[k].first = newWord(FREE, k, start);
        else {
            pp = l[k].first;
            while (pp->rlink != NULL) pp = pp->rlink;  // find the last node
            if (getBuddy(k, pp->start) == start) {
                // merge block
                start = pp->start;
                if (pp->llink == NULL)
                    l[k].first = NULL;
                else
                    pp->llink->rlink = NULL;
                free(pp);
                freeBlock(l, k+1, start);
            } else {
                WORD *p = newWord(FREE, k, start);
                pp->rlink = p;
                p->llink = pp;
            }
        }
    } else {
        int buddy = getBuddy(k, start);
        if (buddy == pp->start) {
            // merge p and pp
            if (pp->llink == NULL)
                l[k].first = pp->rlink;
            else
                pp->llink->rlink = pp->rlink;
            if (pp->rlink != NULL)
                pp->rlink->llink = pp->llink;
            free(pp);
            freeBlock(l, k+1, start);
        } else if (pp->llink != NULL && buddy == pp->llink->start) {
            // merge p and pp->llink
            WORD *ppp = pp->llink;
            start = ppp->start;
            if (ppp->llink == NULL)
                l[k].first = pp;
            else
                ppp->llink->rlink = pp;
            pp->llink = ppp->llink;
            free(ppp);
            freeBlock(l, k+1, start);
        } else {
            WORD *p = newWord(FREE, k, start);
            p->rlink = pp;
            if (pp == l[k].first)
                l[k].first = p;
            else {
                p->llink = pp->llink;
                pp->llink->rlink = p;
            }
            pp->llink = p;
        }
    }
}

int main(int argc, char *argv[]) {
    char tmp[CACHESIZE], *tmpp = tmp;
    int offset;
    int k, start;
    FreeList l;
    initFreeList(l);
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmp, "%d%n", &k, &offset) == 1) {
        tmpp += offset;
        while (sscanf(tmpp, "%d%n", &start, &offset) == 1) {
            tmpp += offset;
            createFreeSpace(l, k, start);
        }
        fgets(tmp, CACHESIZE, stdin);
        tmpp = tmp;
    }
    while (scanf("%d %d", &k, &start) == 2) {
        freeBlock(l, k, start);
    }
    for (int i=1; i<=M; i++) {
        WORD *p = l[i].first;
        if (p == NULL) continue;
        printf("%d ", i);
        while (p != NULL) {
            printf("%d%c", p->start, p->rlink==NULL ? '\n' : ' ');
            p = p->rlink;
        }
    }
    return 0;
}