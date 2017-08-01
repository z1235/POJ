#ifndef HEAPTESTHELP_H
#define HEAPTESTHELP_H

#include <stdlib.h>
#include <time.h>

int *generateRandom(int n, int rangeL, int rangeR)
{
    int i;
    int *arr = malloc(sizeof(int) * n);
    srand(time(NULL));
    for (i = 0; i < n; ++i) {
        arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
    }
    return arr;
}

void swap (int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
#endif
