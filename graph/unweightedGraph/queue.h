#ifndef QUEUE_H_
#define QUEUE_H_

// 环形队列的相关算法
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int ElemType;
typedef struct {
    ElemType *data;
    int capacity;
    int front, rear; // 队首 队尾指针
} Queue;

Queue * initQueue(int capacity)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (ElemType *)malloc(sizeof(ElemType) * (capacity));
    q->capacity = capacity;
    q->front = q->rear = 0;
    return q;
}

void deleteQueue(Queue *q)
{
    if (!q) return;
    if (q->data) {
        free(q->data);
        q->data = NULL;
    }
    free(q);
    q = NULL;
}

int isEmpty(Queue *q)
{
    return q->rear == q->front;
}

void pushQueue(Queue *q, ElemType e)
{
    assert((q->rear + 1) % (q->capacity) != q->front);
    q->rear = (q->rear + 1) % (q->capacity);
    (q->data)[q->rear] = e;
}

void getFront(Queue *q, ElemType *e)
{
    assert(q->front != q->rear);
    *e =  (q->data)[q->front + 1];
}

void popQueue(Queue *q)
{
    assert(q->front != q->rear);
    q->front = (q->front + 1) % (q->capacity);
}


#endif
