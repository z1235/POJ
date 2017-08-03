#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


typedef int ElemType;
typedef struct {
    ElemType *data;
    int top;
    int capacity;
} SqStack;

// 初始化一个栈
void initStack(SqStack **s, int capacity)
{
    (*s) = (SqStack *)malloc(sizeof(SqStack));
    (*s)->data = (ElemType *)malloc(sizeof(ElemType) * capacity);
    (*s)->top = -1; // 栈顶指针设置为 -1
    (*s)->capacity = capacity;
}

// 销毁栈
void destoryStack(SqStack *s)
{
    free(s->data);
    free(s);
}

// 判断栈空
int isEmpty(SqStack *s)
{
    return (s->top == -1);
}

// 进栈
void push(SqStack *s, ElemType e)
{
    assert(s->top < s->capacity - 1);
    s->top++;
    (s->data)[s->top] = e;
}

// 返回栈顶元素
ElemType top(SqStack *s)
{
    assert(s->top != -1);
    return (s->data)[s->top];
}

// 出栈
void pop(SqStack *s)
{
    if (s->top == -1)
        return;
    s->top--;
}

#endif
