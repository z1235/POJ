#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100
int pA[N_MAX];

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void selectSort(int pA[], int n)
{
    int i = 0, j = 0;
    int minIndex = 0;

    for (i = 0; i < n; ++i) {
        minIndex = i;
        for (j = i + 1; j < n; ++j) {
            if (pA[j] < pA[minIndex])
                minIndex = j;
        }
        swap(&pA[minIndex], &pA[i]);
    }
}

int main()
{
    int n = 0;
    int i = 0;
    scanf("%d", &n);

    for (i = 0; i < n; ++i) {
        scanf("%d", &pA[i]);
    }
    selectSort(pA, n);
    for (i = 0; i < n; ++i) {
        printf("%d ", pA[i]);
    }
    printf("\n");

    return 0;
}
