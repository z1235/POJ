#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int cnt;
} MaxHeap;

// 初始化一个大顶堆, 可以容纳的元素个数最多为 n 个
void initMaxHeap(MaxHeap *heap, int n)
{
    heap->data = (int *)malloc(sizeof(int) * (n + 1));
    heap->cnt = 0;
}

void insert(MaxHeap *heap, int elem)
{
    
}

int main()
{
    MaxHeap maxHeap;
    initMaxHeap(&maxHeap, 100);

    return 0;
}
