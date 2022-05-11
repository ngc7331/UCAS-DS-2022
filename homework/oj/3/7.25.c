#include <stdio.h>

#define MAXNODENUM 1000
#define CACHESIZE 10000

typedef enum {
    False,
    True,
} Bool;

void initArray(int array[], int length) {
    while (length)
        array[--length] = 0;
}

Bool hasLoop(int s[], int fst[], int lst[], int visited[], int n) {
    if (visited[n] == 1) return True;
    visited[n] = 1;
    for (int i=fst[n]; i<lst[n]; i++) {
        if (hasLoop(s, fst, lst, visited, s[i]))
            return True;
    }
    visited[n] = 0; // failed to find loop, release
    return False;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d\n", &n);
    int s[MAXNODENUM], fst[n+1], lst[n+1], visited[n+1];
    char tmp[CACHESIZE], *tmpp=tmp;
    int i=0, offset;
    fgets(tmp, CACHESIZE, stdin);
    while (sscanf(tmpp, "%d%n", &s[i++], &offset) == 1)
        tmpp += offset + 1;
    for (i=0; i<=n; i++)
        scanf("%d", &fst[i]);
    for (i=0; i<=n; i++)
        scanf("%d", &lst[i]);

    Bool has_loop = False;
    for (int i=1; i<=n; i++) {
        initArray(visited, n+1);
        if (hasLoop(s, fst, lst, visited, i)) {
            has_loop = True;
            break;
        }
    }
    printf("%s", has_loop ? "yes" : "no");
    return 0;
}