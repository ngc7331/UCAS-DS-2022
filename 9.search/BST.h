#include "../ds.h"

#ifndef ELEMTYPE
#define ELEMTYPE
typedef int Elem;
#endif

typedef struct __bstnode {
    Elem data;
    int bf;
    struct __bstnode *parent;
    struct __bstnode *left, *right;
} bstnode;