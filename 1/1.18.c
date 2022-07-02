/*
# 1.18-田径对抗赛
## 描述
假设有A,B,C,D,E 五个高等院校进行田径对抗赛，各院校的单项成绩均已存入计算机，并构成一张表，表中每一行的形式为
项目名称 - 性别 - 校名 - 成绩
编写算法，处理上述表格，以统计个院校的男、女总分和团体总分，并输出

## 输入
输入包含多行，每行代表表格中的一行，每个字段以空格分隔
M代表男生，F代表女生

## 输出
输出每个学校的男，女总分和团体总分，按如下顺序
第一行输出学校A的男生总分
第二行输出学校A的女生总分
第三行输出学校A的团体总分
第四行输出学校B的男生总分
...
如果某个学校没有男生或女生，则跳过对应的行数（如学校A没有女生，则跳过第二行）

## 样例1
### 输入
X M A 3
Z M A 4
Y F B 30

### 输出
A M 7
A 7
B F 30
B 30

*/

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