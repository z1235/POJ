#ifndef QUICKSORT_2WAYS_H
#define QUICKSORT_2WAYS_H

#include <time.h>
#include "sortHelper.h"

int _partiction_2ways(int *arr, int l, int r)
{
    int e = 0;
    int i = 0, j = 0;
    swap(&arr[l], &arr[rand() % (r - l + 1) + l]);
    e = arr[l];

    i = l + 1;
    j = r;
    while (1) {
        while (i <= r && arr[i] < e) i++;
        while (j >= l + 1 && arr[j] > e) j--;
        if (i > j) break;
        swap(&arr[i], &arr[j]);
        i++;
        j--;
    }
    swap(&arr[l], &arr[j]);
    return j;
}

void _quicksort_2ways(int *arr, int l, int r)
{
    int p = 0;
    if (l >= r)
        return;
    p = _partiction_2ways(arr, l, r);
    _quicksort_2ways(arr, l, p - 1);
    _quicksort_2ways(arr, p + 1, r);
}

void quicksort_2ways(int *arr, int n)
{
    srand(time(NULL));
    _quicksort_2ways(arr, 0, n - 1);
}

#endif
