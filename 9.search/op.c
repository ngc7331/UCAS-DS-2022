#include "op.h"

// these won't maintain (*root)->parent->left/right field
Status Rrotate(tnode **root) {
    tnode *r = *root;
    *root = r->left;
    r->left = (*root)->right;
    (*root)->right = r;
    (*root)->parent = r->parent;
    r->parent = *root;
    return OK;
}

Status Lrotate(tnode **root) {
    tnode *r = *root;
    return OK;
}
