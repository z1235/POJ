#ifndef SORTHELPER_H
#define SORTHELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// 用于交换两个元素的值
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int min(int a, int b)
{
    return a > b ? b : a;
}

int * generateRandom(int n, int rangeL, int rangeR)
{
    int i = 0;
    int *pArr = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
        pArr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
    }
    return pArr;
}

int * generateOrder(int n, int swapTimes)
{
    int i = 0;
    int *pArr = (int *)malloc(sizeof(int) * n);

    srand(time(NULL));
    for (i = 0; i < n; ++i)
        pArr[i] = i;
    for (i = 0; i < swapTimes; ++i)
        swap(pArr + rand() % n, pArr + rand() % n);
    return pArr;
}

// 测试是否是有序的
int isSorted(int *arr, int n)
{
    int i = 0;
    int ret = 1;
    for (i = 0; i < n - 1; ++i)  {
        if (arr[i] > arr[i + 1])
            ret = 0;
    }
    return ret;
}
int isSorted_2(int *arr, int l, int r)
{
    int i = l;
    int ret = 1;
    for (i = l; i < r; ++i) {
        if (arr[i] > arr[i + 1])
            ret = 0;
    }
    return ret;
}

// 用于测试排序函数
void testSortFunction(char *sortName, void (*sort)(int *, int), int *arr, int n)
{
    clock_t t1 = clock();
    sort(arr, n);
    clock_t t2 = clock();
    assert(isSorted(arr, n)); // 检查是否已经排好序了
    printf("%s: time: %lf\n", sortName, (double)(t2 - t1)/CLOCKS_PER_SEC);
}

void testSortFunction_2(char *sortName, void (*sort)(int *, int, int), int *arr, int l, int r)
{
    clock_t t1 = clock();
    sort(arr, l, r);
    clock_t t2 = clock();
    assert(isSorted_2(arr, l, r));
    printf("%s: time: %lf\n", sortName,(double)(t2 - t1)/CLOCKS_PER_SEC);
}

// 用于打印元素
void printElem(int *arr, int n)
{
    int i = 0;
    for (i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 拷贝测试
int * copyTestCase(int *arr, int n)
{
    int i = 0;
    int *arr2 = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i)
        arr2[i] = arr[i];
    return arr2;
}


#endif
