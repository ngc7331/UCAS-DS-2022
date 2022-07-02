/*
# 9.42-9.43 Trie 树插入删除和查找
## 描述
**假设Trie树上同义词放在同一叶子结点中，请实现 Trie 树的插入、删除、查找功能**

## 输入
输入为若干行，每行包括一个数字和一个字符串(只包含小写字母)，数字 1、2、3 分别表示插入、删除、查找。如果删除的元素不存在，则不作任何操作。查找的元素存在输出为 True, 不存在输出为 False.

## 输出
输出的行数为查找操作的次数，若查找的元素存在输出为 True, 不存在输出为 False。

## 样例1
### 输入
1 apple
1 app
1 at
2 app
3 apple
2 apple
3 apple

### 输出
True
False

## 样例2
### 输入
1 a
1 b
1 c
1 ab
1 acd
2 ac
3 ac
3 abc
3 ab

### 输出
False
False
True

*/

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