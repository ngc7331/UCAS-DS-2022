#include <stdio.h>
#include <stdlib.h>

// NOT FINISHED

typedef struct {
    int a, e;
} PolyTerm;

typedef struct PolyNode {
  PolyTerm data;
  struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;

LinkedPoly InitPoly() {
    LinkedPoly p = (LinkedPoly) malloc(sizeof(PolyNode));
    p->next = NULL;
    return p;
}

void input(LinkedPoly p) {
    int c, e;
    char tmp;
    char *line = (char *) malloc(1000 * sizeof(char));
    int offset_c, offset_e;
    fgets(line, 1000, stdin);
    while (1) {
        int sign = 1, offset=0;
        if (sscanf(line, "%d%n", &c, &offset_c) != 1) {
            sscanf(line, "%c", &tmp);
            if (tmp == '-') {
                sign = -1;
            }
            else if (tmp == '\0' || tmp == '\n') {
                printf("EOF\n"); break;
            }
            else printf("char:%c\n", tmp);
        }
        else {
            line += offset_c;
            if (line[1] == '^') {
                sscanf(line+2, "%d%n", &e, &offset_e);
                offset = 2;
            }
            else {
                offset_e = 0;
                offset = 1;
                e = 1;
            }
        }
        printf("p: %d %d\n", c, e);
        line += offset + offset_e;
    }
}

int main() {
    LinkedPoly p = InitPoly();
    input(p);
}