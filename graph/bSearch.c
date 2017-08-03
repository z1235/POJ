// 对图进行广度优先遍历
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "DenseGraph.h"

int *inQueue = NULL; // 表示已经存放到队列中的元素

void bfs(Graph *g, int s)
{
    int i;
    int frontV;
    int n = g->n; // 结点的个数
    Queue *q = initQueue(n + 1);
    inQueue = (int *)malloc(sizeof(int) * n); // 访问数组
    // init
    for (i = 0; i < n; ++i)
        inQueue[i] = 0;
    pushQueue(q, s);
    inQueue[s] = 1;

    while (!isEmpty(q)) {
        getFront(q, &frontV); // 得到当前的访问的结点
        printf("%d ", frontV);
        popQueue(q);
        for (i = 0; i < n; ++i)
            if (!inQueue[i] && (g->map)[frontV][i]) {
                pushQueue(q, i);
                inQueue[i] = 1;
            }
    } // end-while
    putchar('\n');
    deleteQueue(q);
    free(inQueue);
    inQueue = NULL;
}

int main()
{
    const char *fileName = "map2.tb";
    Graph *g = buildGraphFromFile(fileName);
    assert(g != NULL);
    bfs(g, 0);
    deleteGraph(g);
    return 0;
}
