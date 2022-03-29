#include <stdio.h>
#include <string.h>

void swap(char *s, int a, int b) {
    char tmp = s[a];
    s[a] = s[b];
    s[b] = tmp;
}

void reverse(char *s) {
    int len = strlen(s);
    if (s[len-1] == '\n') len--;
    for (int i=0; i<len/2; i++)
        swap(s, i, len-i-1);
}

int main() {
    char s[1000];
    fgets(s, 1000, stdin);
    reverse(s);
    printf("%s", s);
    return 0;
}