#include <stdio.h>

typedef enum {
    NORMAL,
    COMMENTARY,
    STRING
} State;

int main() {
    char c;
    State s = NORMAL;
    while ((c=getchar()) != EOF) {
        switch (s) {
            case NORMAL:
                if (c == '/') {
                    if ((c=getchar()) == '*')
                        s = COMMENTARY;
                    else {
                        putchar('/');
                        putchar(c);
                    }
                }
                else {
                    if (c == '"')
                        s = STRING;
                    putchar(c);
                }
                break;
            case COMMENTARY:
                if (c == '*' && getchar() == '/')
                    s = NORMAL;
                break;
            case STRING:
                if (c == '"')
                    s = NORMAL;
                putchar(c);
                break;
        }
    }
}