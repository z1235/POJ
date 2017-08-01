#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heapTestHelper.h"

typedef struct {
    int *arr;       // 第一个元素不使用
    int cnt;        // 堆中最后一个元素的位置
    int capacity;
} MaxHeap;


// 初始化一个大顶堆
void initMaxHeap(MaxHeap *heap, int n)
{
    heap->arr = (int *)malloc(sizeof(int) * (n + 1)); // 第一个元素没有使用
    heap->cnt = 0;
    heap->capacity = n;
}

// 将堆中的 index 位置的元素向上进行调整
void shiftUp(MaxHeap *heap, int index)
{
    while (index >= 2 && (heap->arr)[index] > (heap->arr)[index/2]) {
        // printf("swap %d %d\n", index, index/2);
        swap(heap->arr + index, heap->arr + index/2);
        index /= 2;
    } // end-while
}

// 将堆中的 index 位置的元素向下进行调整
void shiftDown(MaxHeap *heap, int index)
{
    int size = heap->cnt;
    int indexL = 2 * index;
    int indexR = indexL + 1;
    while (indexL <= size) {
        if (indexR <= size) {
            if ((heap->arr)[indexL] > (heap->arr)[indexR]) {
                swap((heap->arr) + indexL, (heap->arr) + index);
                index = indexL;
                indexL = 2 * index;
                indexR = indexL + 1;
            }
            else {
                swap((heap->arr) + indexR, (heap->arr) + index);
                index = indexR;
                indexL = 2 * index;
                indexR = indexL + 1;
            }
        }
        else {
            swap((heap->arr) + indexL, (heap->arr) + index);
            index = indexL;
            indexL = 2 * index;
            indexR = indexL + 1;
        }
    } // end-while
}

// 向最大堆中插入一个元素
void insert(MaxHeap *heap, int value)
{
    heap->cnt++;
    (heap->arr)[heap->cnt] = value;
    shiftUp(heap, heap->cnt);
}

// 从最大堆中取出一个元素
int extractElem(MaxHeap *heap)
{
    int e;
    assert(heap->cnt > 0);
    e = (heap->arr)[1]; // 堆顶元素
    (heap->arr)[1] = (heap->arr)[heap->cnt];
    heap->cnt--;
    shiftDown(heap, 1);
    return e;
}

int isEmpty(MaxHeap *heap)
{
    return heap->cnt == 0;
}

// 按照元素的顺序打印出来
 void printAsOrder(MaxHeap *heap)
 {
     int e;
     while (!isEmpty(heap)) {
         e = extractElem(heap);
         printf("%d ", e);
     }
     putchar('\n');
 }


// 释放堆空间
void deleteHeap(MaxHeap *heap)
{
    if (heap->arr) {
        free(heap->arr);
        heap->arr = NULL;
        heap->cnt = heap->capacity = 0;
    } // end-if
}


int main()
{
    MaxHeap heap;
    int n = 10;
    int *arr = generateRandom(n, 1, n);
    int i;
    int e;


// 插入数据
    initMaxHeap(&heap, n);
    for (i = 0; i < n; ++i) {
        insert(&heap, arr[i]);
    }

    printAsOrder(&heap);

// 收尾
    deleteHeap(&heap);
    free(arr);
    return 0;
}
