#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sortHelper.h"

int _partition(int *arr, int l, int r)
{
    int e = 0;
    int i = 0, j = 0;

    swap(&arr[l], &arr[rand() % (r - l + 1) + l]);
    e = arr[l];
    i = l; // i 指向最后一个小于 e 的元素
    for (j = l + 1; j <= r; ++j) {
        if (arr[j] < e) {
            swap(&arr[i + 1], &arr[j]);
            i++;
        }
    } // end-for
    swap(&arr[l], &arr[i]);
    return i;
}
// 求解数组中第 k 大的元素
int _getMaxK(int *arr, int l, int r, int k)
{
    int pivot = 0;
    if (l >= r)
        return arr[l];
    else {
        pivot = _partition(arr, l, r);
        if (pivot == k)
            return arr[pivot];
        else if (pivot > k)
            return _getMaxK(arr, l, pivot - 1, k);
        else
            return _getMaxK(arr, pivot + 1, r, k - pivot);
    }
}

// 对求解第 k 的的元素的一个封装
int getMaxK(int *arr, int n, int k)
{
    return _getMaxK(arr, 0, n - 1, k);
}

int cmp(const void *a, const void *b)
{
    int *p = (int *)a;
    int *q = (int *)b;
    return -(*p - *q);
}

int forceGetMaxK(int *arr, int n, int k)
{
    qsort(arr, n, sizeof(int), cmp); // 倒序排列
    return arr[k];
}

// 用于测试性能
void testFunctionMaxK(char *funcName, int (*maxK)(int *, int, int), int *arr, int n, int k)
{
    int result = 0;
    clock_t t1 = clock();
    result = maxK(arr, n, k);
    clock_t t2 = clock();
    printf("%s: the %dth max is %d, used %lf s\n", funcName, k, result, (double)(t2 - t1)/CLOCKS_PER_SEC);
}

int main()
{
    int n = 100;
    int *arr = generateRandom(n, 1, n);
    int *arr1 = copyTestCase(arr, n);
    int k = 5;

    testFunctionMaxK("quick sort like", getMaxK, arr, n, k);
    testFunctionMaxK("forceGetMaxK", forceGetMaxK, arr1, n, k);
    printElem(arr1, n);

    free(arr);
    free(arr1);
    return 0;
}
