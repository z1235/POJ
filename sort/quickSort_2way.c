// 二路快速排序
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void _partiction(int *arr, int l, int r)
{
    int e = 0;
    int i = 0, j = 0;
    swap(&arr[l], &arr[rand() % (r - l + 1) + l]);
    e = arr[l];

    // arr[l + 1, p] < e < arr[p + 1, r]
    i = l;
    j = r + 1;
    while (i < j) {

    }
}

void _quickSort(int *arr, int l, int r)
{
    int p = 0;
    if (l >= r)
        return;
    p = _partiction(arr, l, r);
    _quickSort(arr, l, p - 1);
    _quickSort(arr, p + 1, r);
}

void quickSort(int *arr, int n)
{
    srand(time(NULL));
    _quickSort(arr, 0, n - 1);
}

int main()
{

    return 0;
}
