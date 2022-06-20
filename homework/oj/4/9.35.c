#include <stdio.h>
#include <stdlib.h>

#define CACHESIZE 10000

typedef enum {
    False,
    True,
} Bool;

typedef struct __node {
    int data;
    struct __node *parent, *left, *right;
    int bf;
    Bool prev, succ;
} node, *AVL;

node *newNode(int x) {
    node *n = (node *) malloc(sizeof(node));
    n->data = x;
    n->parent = n->left = n->right = NULL;
    n->bf = 0;
    n->prev = n->succ = False;
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

void inorderSuccThreading(AVL t) {
    if (t == NULL || t->left == NULL) return ;
    AVL p = t->left;
    while (p->right != NULL) p = p->right;
    p->right = t;
    p->succ = True;
    inorderSuccThreading(t->left);
    if (!t->succ)
        inorderSuccThreading(t->right);
}

void search(AVL t, int a, int b) {
    if (t == NULL) return ;
    while (t->left != NULL) t = t->left;
    while (t->right != NULL) {
        if (t->data >= b) break;
        if (t->data > a)
            printf("%d ", t->data);
        if (t->succ)
            t = t->right;
        else {
            t = t->right;
            while (t->left != NULL) t = t->left;
        }
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
    inorderSuccThreading(t);
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    search(t, a, b);
    return 0;
}