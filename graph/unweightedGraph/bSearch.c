// 对图进行广度优先遍历
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "DenseGraph.h"
#include "stack.h"

int *inQueue = NULL;    // 表示已经存放到队列中的元素
int *from = NULL;       // 记录当前结点是从那个结点访问过来的
int *ord = NULL;        // 记录从 结点s 到各个结点的最短距离

void bfs(Graph *g, int s)
{
    int i;
    int frontV;
    int n = g->n; // 结点的个数
    Queue *q = initQueue(n + 1);
    inQueue = (int *)malloc(sizeof(int) * n);   // 记录已经加入到队列中的元素
    from = (int *)malloc(sizeof(int) * n);      // 记录当前节点放入队列中的前置节点
    ord = (int *)malloc(sizeof(int) * n);       // 记录广度优先搜索,结点所处的层数
    // init
    for (i = 0; i < n; ++i) {
        inQueue[i] = 0;
        from[i] = -1;
        ord[i] = 0;
    }
    pushQueue(q, s);
    inQueue[s] = 1;

    while (!isEmpty(q)) {
        getFront(q, &frontV); // 得到当前的访问的结点
        // printf("%d ", frontV);
        popQueue(q);
        for (i = 0; i < n; ++i)
            if (!inQueue[i] && (g->map)[frontV][i]) {
                pushQueue(q, i);
                inQueue[i] = 1;
                from[i] = frontV;
                ord[i] = ord[frontV] + 1;
                printf("inQueue %d from %d ord %d\n", i, frontV, ord[i]);
            }
    } // end-while
    putchar('\n');
    deleteQueue(q);
    free(inQueue);
    inQueue = NULL;
}

// 计算图g中从s到d的最短路径,并打印出来
// 在运行这个函数之前保障已经进行了宽度优先遍历,填充了fron和ord数组
int getMinPath(Graph *g, int s, int d)
{
    int tmp;
    int des = d;
    SqStack *stack;

    initStack(&stack, (g->n) + 1);
    assert(from && ord);

    while (d != s) {
        pushStack(stack, d);
        d = from[d];
    }
    pushStack(stack, s);
    while(!isEmptyStack(stack)) {
        tmp = top(stack);
        printf("%d", tmp);
        if (stack->top != 0)
            printf(" --> ");
        else
            printf("\n");
        popStack(stack);
    }

    destoryStack(stack);
    return ord[des];
}

void deleteTrash()
{
    if (from) {
        free(from);
        from = NULL;
    }
    if (ord) {
        free(ord);
        ord = NULL;
    }
}

int main()
{
    const char *fileName = "map2.tb";
    int minDis;
    Graph *g = buildGraphFromFile(fileName);
    assert(g != NULL);
    bfs(g, 0);
    minDis = getMinPath(g, 0, 5);
    printf("the minDis from 0 to 5 = %d\n", minDis);
    deleteGraph(g);
    deleteTrash();
    return 0;
}
