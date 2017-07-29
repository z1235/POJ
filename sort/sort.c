#include <stdio.h>
#include <stdlib.h>

#include "sortHelper.h"
#include "shellSort.h"

void selectSort(int *arr, int n)
{
    int i = 0, j = 0;
    int minIndex = 0;

    for (i = 0; i < n - 1; ++i) {
        minIndex = i;
        for (j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(&arr[i], &arr[minIndex]);
    }
}

void insertSort(int *arr, int n)
{
    int i = 0, j = 0;
    int e = 0;
    for (i = 1; i < n; ++i) {
        e = arr[i];
        for (j = i; j > 0 && e < arr[j - 1]; --j)
            arr[j] = arr[j - 1];
        arr[j] = e;
    }
}

// 对 arr[l, r]进行排序
void insertSort_2(int *arr, int l, int r)
{
    int i = 0, j = 0;
    int e = 0;

    for (i = l + 1; i <= r; ++i) {
        e = arr[i];
        for (j = i; j > l && e < arr[j - 1]; --j)
            arr[j] = arr[j - 1];
        arr[j] = e;
    }
}

void bubbleSort(int *arr, int n)
{
    int i = 0, j = 0;
    for (i = n - 1; i > 0; --i) {
        for (j = 0; j < i; ++j) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

void bubbleSort_2(int *arr, int n)
{
    int i = 0, j = 0;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// 将 arr[l...mid]和arr[mid + 1, r]两部分进行归并
void _merge(int *arr, int l, int mid, int r)
{
    int aux[r - l + 1];
    int i = 0, j = 0, k = 0;
    for (i = l; i <= r; ++i)
        aux[i - l] = arr[i];

    i = l;
    j = mid + 1;
    for (k = l; k <= r; ++k) {
        if (i > mid) {
            arr[k] = aux[j - l];
            j++;
        }
        else if (j > r) {
            arr[k] = aux[i - l];
            i++;
        }
        else if (aux[i - l] < aux[j - l]) {
            arr[k] = aux[i - l];
            i++;
        }
        else {
            arr[k] = aux[j - l];
            j++;
        }
    } // end-for
}
// 对 arr[l...r]范围内的元素进行排序
void _mergeSort(int *arr, int l, int r)
{
    int mid = (l + r)/2;
    if (r - l + 1 <= 16) {
        insertSort_2(arr, l, r);
        return;
    }
    else {
        _mergeSort(arr, l, mid);
        _mergeSort(arr, mid + 1, r);
        if (arr[mid] > arr[mid + 1])
            _merge(arr, l, mid, r);
    }
}

void mergeSort(int *arr, int n)
{
    _mergeSort(arr, 0, n - 1);
}

// mergeSort from bottom to up 适用于链表等数据类型
void mergeSortBU(int *arr, int n)
{
    int sz = 0, i = 0;
    for (sz = 1; sz <= n; sz += sz) { // sz 1->2->4->8->n
        for (i = 0; i + sz < n; i += 2*sz) {
            // printf("%d-%d-%d\n", i, i + sz - 1, min(i + 2 * sz - 1, n - 1));
            _merge(arr, i, i + sz - 1, min(i + 2 * sz - 1, n - 1));
        }
    } // end-for
}

int main()
{
    int n = 100;

    int *arr0 = generateRandom(n, 0, n);
    int *arr1 = generateOrder(n, 10);
    int *arr2 = copyTestCase(arr0, n);
    int *arr3 = copyTestCase(arr1, n);


    // testSortFunction("selectSort", selectSort, arr0, n);
    // testSortFunction("insertSort", insertSort, arr2, n);
    // testSortFunction("insertSort ordered", insertSort, arr1, n);
    // testSortFunction("bubbleSort", bubbleSort, arr3, n);
    // testSortFunction("bubbleSort_2", bubbleSort_2, arr4, n);
    // testSortFunction("mergeSort", mergeSort, arr0, n);
    // testSortFunction_2("insertSort_2", insertSort_2, arr0, 0, n - 1);
    // testSortFunction("mergeSort", mergeSort, arr0, n);
    testSortFunction("mergeSortBU", mergeSortBU, arr0, n);
    testSortFunction("shellSort", shellSort, arr0, n);

    free(arr0);
    free(arr1);
    free(arr2);
    free(arr3);
    return 0;
}
