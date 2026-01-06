#include <stdio.h>

#define LEN 20

struct student

{

    char no[LEN];
    float average;
};

void input(struct student s[], int n); /*输入n个学生的情况*/

float average1(struct student s[], int n); /*求学生的平均分*/

float average(struct student s[], int n); /*求三门课的总平均分*/

int max(struct student s[], int n); /*返回最高分学生的序号*/

float maxScore(struct student s[], int n); /*返回最高分*/

int main()

{

    struct student stu[10];

    int n;

    float aver;

    ……

        input(stu, n);

    ……

        return 0;
}