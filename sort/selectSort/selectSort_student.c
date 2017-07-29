#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    int score;
} Student;

void swap(Student *a, Student *b)
{
    Student tmp = *a;
    *a = *b;
    *b = tmp;
}

void selectSort(Student *pA, int n)
{
    int i = 0, j = 0;
    int minIndex = 0;

    for (i = 0; i < n; ++i) {
        minIndex = i;
        for (j = i + 1; j < n; ++j) {
            if (pA[j].score < pA[minIndex].score)
                minIndex = j;
        }
        swap(&pA[minIndex], &pA[i]);
    }
}

int main()
{
    int i = 0;
    Student pStuArray[4] = {{"AB", 100}, {"BC", 200}, {"CD", 20}, {"Ed", 90}};
    selectSort(pStuArray, 4);

    for (i = 0; i < 4; ++i) {
        printf("%s %d\n", pStuArray[i].name, pStuArray[i].score);
    }
    return 0;
}
