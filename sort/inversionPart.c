// 参考 mergeSort 计算出一个数组中的逆序对的对数

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sortHelper.h"

// 暴力求解数组中的逆序对的个数
long long forceInversionPart(int *arr, int n)
{
    int i = 0, j = 0;
    long long ret = 0;
    // 二元组 {i, j}
    for (i = 0; i < n - 1; ++i) {
        for (j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j])
                ret++;
        } // end-for
    } // end-for
    return ret;
}

// 对数组元素 [l, mid] [mid + 1, r] 进行归并，并返回逆序对的个数
long long _merge(int *arr, int l, int mid, int r)
{
    int i = 0, j = 0, k = 0;
    long long ret = 0;
    int aux[r - l + 1];
    for (i = l; i <= r; ++i)
        aux[i - l] = arr[i];

    // 对 [l, mid] [mid + 1, r]进行归并，并求出逆序对的对数
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
        else if (aux[i - l] <= aux[j - l]) {
            arr[k] = aux[i - l];
            i++;
        }
        else {
            arr[k] = aux[j - l];
            j++;
            ret += mid - i + 1; // 逆序元素
        }
    } // end-for
    return ret;
}

// 递归调用，Up to Bottom
long long _inversionPart(int *arr, int l, int r)
{
    int mid = (l + r)/2;
    long long ret = 0;

    if (l >= r)
        return 0;
    else {
        ret = _inversionPart(arr, l, mid);       // 获得左边的逆序对的对数， 并对左边部分进行排序
        ret += _inversionPart(arr, mid + 1, r);    // 获得右边逆序对的对数， 并对右边部分进行排序
        ret += _merge(arr, l, mid, r);         // 获得跨越左右两边的逆序对的对数， 并排序所有的元素
        return ret;
    }
}

long long  inversionPart(int *arr, int n)
{
    return _inversionPart(arr, 0, n - 1);
}

void testFunction(char *funcName, long long (*getInversionPart)(int *, int), int *arr, int n)
{
    long long cnt = 0;
    clock_t t1 = clock();
    cnt = getInversionPart(arr, n);
    clock_t t2 = clock();
    printf("%s times: %lf s | result = %lld\n", funcName, (double)(t2 - t1)/CLOCKS_PER_SEC, cnt);
}



int main()
{
    int i = 0;

    int n = 200000;
    int *arr1 = generateRandom(n, 1, 100);
    int *arr2 = copyTestCase(arr1, n);

    testFunction("inversionPart", inversionPart, arr1, n);
    testFunction("forceInversionPart", forceInversionPart, arr2, n);

    free(arr1);
    free(arr2);
    return 0;
}
