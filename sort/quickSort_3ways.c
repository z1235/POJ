// 三路归并排序
#include <stdio.h>
#include <stdlib.h>

#include "sortHelper.h"
#include "quickSort_2ways.h"


// 将 arr[l, r]划分为 arr[l, lt]  arr[lt + 1, gt - 1] arr[gt, r]
void _quickSort_3ways(int *arr, int l, int r)
{
    int lt = 0, gt = 0;
    int v = 0, e = 0;
    int i = 0;

    if (l >= r)
        return;

    // partiction
    swap(&arr[l], &arr[rand() % (r - l + 1) + l]);
    v = arr[l];
    lt = l;
    gt = r + 1;
    i = l + 1;
    while (i < gt) {
        e = arr[i];
        if (e < v) {
            swap(&arr[lt + 1], &arr[i]);
            lt++;
            i++;
        }
        else if (e > v) {
            swap(&arr[gt - 1], &arr[i]);
            gt--;
        }
        else { // e = v
            i++;
        }
    } // end-while
    swap(&arr[l], &arr[lt]);

    _quickSort_3ways(arr, l, lt - 1);
    _quickSort_3ways(arr, gt, r);
}

void quickSort_3ways(int *arr, int n)
{
    srand(time(NULL));
    _quickSort_3ways(arr, 0, n - 1);
}

int main()
{
    int n = 100000;
    int *arr = generateRandom(n, 0, 10);
    int *arr1 = copyTestCase(arr, n);
    testSortFunction("quicksort_2ways", quicksort_2ways, arr1, n);
    testSortFunction("quickSort_3ways", quickSort_3ways, arr, n);
    return 0;
}
