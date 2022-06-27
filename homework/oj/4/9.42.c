#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 10000

typedef struct __trieNode {
    struct __trieNode *next[26];  // a~z
    char *data;
} trieNode, *trieTree;

trieNode *newTrieNode() {
    trieNode *t = (trieNode *) malloc(sizeof(trieNode));
    for (int i = 0; i < 26; i++) t->next[i] = NULL;
    t->data = NULL;
    return t;
}

void insertTrie(trieTree t, char *str) {
    trieNode *p = t;
    char *s = malloc(strlen(str) + 1);
    strcpy(s, str);
    while (*str) {
        if (*str - 'a' < 0 || *str - 'a' >= 26)
            return ;
        if (p->next[*str - 'a'] == NULL) {
            p->next[*str - 'a'] = newTrieNode();
        }
        p = p->next[*str - 'a'];
        str++;
    }
    p->data = str;
}

void removeTrie(trieTree t, char *str) {
    trieNode *p = t;
    while (*str) {
        if (*str - 'a' < 0 || *str - 'a' >= 26)
            return ;
        if (p->next[*str - 'a'] == NULL) return ;
        p = p->next[*str - 'a'];
        str++;
    }
    p->data = NULL;
}

int findTrie(trieTree t, char *str) {
    trieNode *p = t;
    while (*str) {
        if (*str - 'a' < 0 || *str - 'a' >= 26)
            return 0;
        if (p->next[*str - 'a'] == NULL) return 0;
        p = p->next[*str - 'a'];
        str++;
    }
    return p->data != NULL;
}

int main(int argc, char *argv[]) {
    trieTree t = newTrieNode();
    int op;
    char *buffer = malloc(BUFSIZE);
    while (scanf("%d %s", &op, buffer) == 2) {
        switch (op) {
        case 1:
            insertTrie(t, buffer);
            break;
        case 2:
            removeTrie(t, buffer);
            break;
        case 3:
            printf("%s\n", findTrie(t, buffer) ? "True" : "False");
            break;
        }
    }
    return 0;
}