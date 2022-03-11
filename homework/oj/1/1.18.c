#include <stdio.h>

typedef struct {
    char prj, gender, school;
    int score;
} Line;

typedef struct {
    int score[2];
} School;

int parseline(Line *l) {
    char tmp[100];
    if (fgets(tmp, 100, stdin) == NULL) return -1;
    sscanf(tmp, "%c %c %c %d", &l->prj, &l->gender, &l->school, &l->score);
    return 0;
}

int main() {
    Line l;
    School s[5], *ps;
    for (int i=0; i<5; i++)
        s[i].score[0] = s[i].score[1] = 0;
    while(parseline(&l) == 0)
        s[l.school-'A'].score[l.gender=='F'] += l.score;
    for (int i=0; i<5; i++) {
        if (s[i].score[0])
            printf("%c M %d\n", i+'A', s[i].score[0]);
        if (s[i].score[1])
            printf("%c F %d\n", i+'A', s[i].score[1]);
        if (s[i].score[0]+s[i].score[1])
            printf("%c %d\n", i+'A', s[i].score[0]+s[i].score[1]);
    }
    return 0;
}