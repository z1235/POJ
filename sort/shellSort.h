#ifndef SHELLSHORT_H
#define SHELLSHORT_H

void shellInsert(int *arr, int n, int d)
{
    int i = 0, j = 0;
    int e = 0;

    for (i = d; i < n; ++i) {
        e = arr[i];
        for (j = i; j - d >= 0 && e < arr[j - d]; j -= d)
            arr[j] = arr[j - d];
        arr[j] = e;
    }

}

void shellSort(int *arr, int n)
{
    int d = n;
    while (d >= 1) {
        shellInsert(arr, n, d);
        d /= 2;
    }
}

#endif
