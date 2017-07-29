#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "sortHelper.h"

// 返回 p 使得 arr[0..p - 1] < arr[p] <= arr[p + 1... r]
int _partiction(int *arr, int l, int r)
{
    int i = 0, j = 0;

    i = l;
    for (j = l + 1; j <= r; ++j) {
        if(arr[j] < arr[l]) {
            swap(&arr[i + 1], &arr[j]);
            i++;
        }
    } // end-for
    swap(&arr[i], &arr[l]);
    return i;
}


// 对 arr [l.. r]部分进行快速排序
void _quickSort(int *arr, int l, int r)
{
    int p = 0;
    if (l >= r)
        return;
    else {
        p = _partiction(arr, l, r);
        _quickSort(arr, l, p - 1);
        _quickSort(arr, p + 1, r);
    }
}

void quickSort(int *arr, int n)
{
    _quickSort(arr, 0, n - 1);
}


int _partiction_rand(int *arr, int l, int r)
{
    int i = 0, j = 0;

    i = l;
    swap(&arr[l], &arr[rand() % (r - l + 1) + l]);
    for (j = l + 1; j <= r; ++j) {
        if (arr[j] < arr[l]) {
            i++;
            swap(&arr[j], &arr[i]);
        }
    } // end-for
    swap(&arr[l], &arr[i]);
    return i;
}

void _quickSort_rand(int *arr, int l, int r)
{
    int p = 0;
    if (l >= r)
        return;
    else {
        p = _partiction_rand(arr, l, r);
        _quickSort_rand(arr, l, p - 1);
        _quickSort_rand(arr, p + 1, r);
    }
}

void quickSort_rand(int *arr, int n)
{
    srand(time(NULL));
    _quickSort_rand(arr, 0, n - 1);
}

#endif
