#include <stdio.h>
#include <stdlib.h>

#define CACHESIZE 10000

typedef struct __node {
    int data;
    struct __node *parent, *left, *right;
    int bf;
} node, *AVL;

node *newNode(int x) {
    node *n = (node *) malloc(sizeof(node));
    n->data = x;
    n->parent = n->left = n->right = NULL;
    n->bf = 0;
    return n;
}

void LRotate(AVL t) {
    AVL p = t->right;
    t->right = p->left;
    if (p->left != NULL)
        p->left->parent = t;
    p->left = t;
    p->parent = t->parent;
    t->parent = p;
    if (p->parent != NULL) {
        if (p->parent->left == t)
            p->parent->left = p;
        else
            p->parent->right = p;
    }
}

void RRotate(AVL t) {
    AVL p = t->left;
    t->left = p->right;
    p->right->parent = t;
    p->right = t;
    p->parent = t->parent;
    t->parent = p;
    if (p->parent != NULL) {
        if (p->parent->left == t)
            p->parent->left = p;
        else
            p->parent->right = p;
    }
}

AVL balance(AVL t) {
    AVL p = t->parent;
    while (p != NULL) {
        if (t == p->left)
            p->bf ++;
        else
            p->bf --;

        if (p->bf == 0)
            break ;
        else if (p->bf == -2) {
            if (t->bf == 1) {
                RRotate(t);
                t->bf = 0;
                t->parent->bf = 1;
            }
            LRotate(p);
            p->bf = 0;
            p->parent->bf = 0;
            break ;
        }
        else if (p->bf == 2) {
            if (t->bf == -1) {
                LRotate(t);
                t->bf = 0;
                t->parent->bf = -1;
            }
            RRotate(p);
            p->bf = 0;
            p->parent->bf = 0;
            break ;
        }
        p = p->parent;
        t = t->parent;
    }
    while (t->parent != NULL)
        t = t->parent;
    return t;
}

void insertBST(AVL *tp, int x) {
    if (*tp == NULL)
        *tp = newNode(x);
    else {
        AVL t = *tp;
        while (x < t->data && t->left != NULL && (t = t->left) ||
               x > t->data && t->right != NULL && (t = t->right));
        if (x < t->data) {
            t->left = newNode(x);
            t->left->parent = t;
            *tp = balance(t->left);
        }
        else {
            t->right = newNode(x);
            t->right->parent = t;
            *tp = balance(t->right);
        }
    }
}

void search(AVL t, int a, int b) {
    if (t == NULL) return ;
    if (t->data <= a)
        search(t->right, a, b);
    else if (t->data >= b)
        search(t->left, a, b);
    else {
        search(t->left, a, b);
        printf("%d ", t->data);
        search(t->right, a, b);
    }
}

int main(int argc, char *argv[]) {
    AVL t;
    char tmp[CACHESIZE], *tmpp = tmp;
    int x, offset;
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &x, &offset) == 1) {
        tmpp += offset;
        insertBST(&t, x);
    }
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    search(t, a, b);
    return 0;
}