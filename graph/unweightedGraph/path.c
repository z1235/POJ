#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "stack.h"

typedef struct {
    int n;
    int e;
    int directed;
    int **map;
} Graph;

int *visited = NULL;
int *from = NULL;

void initGraph(Graph *g, int n, int directed)
{
    int i, j;
    (g->map) = (int **)malloc(sizeof(int *) * n);
    for (i = 0; i < n; ++i) {
        (g->map)[i] = (int *)malloc(sizeof(int) * n);
    } // end-for
    g->n = n;
    g->e = 0;
    g->directed = directed;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            (g->map)[i][j] = 0;
    visited = (int *)malloc(sizeof(int) * n);
    from = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
        visited[i] = 0;
        from[i] = 0;
    } // end-for
}

void printTable(Graph *g)
{
    int i, j;
    int n = g->n;
    for (i = 0; i < n; ++i) {
        printf("vertrix %d: ", i);
        for (j = 0; j < n; ++j)
            if ((g->map)[i][j] != 0)
                printf("%d ", j);
        putchar('\n');
    } // end-for
}

void deleteGraph(Graph *g)
{
    int i;
    int n = g->n;
    for (i = 0; i < n; ++i)
        free((g->map)[i]);
    free(g->map);
    free(visited);
    free(from);
}

void insertEdge(Graph *g, int u, int v)
{
    assert(u >= 0 && u < g->n);
    assert(v >= 0 && v < g->n);
    assert(u != v); // 无环图
    (g->map)[u][v] = 1;
    if (!g->directed) // 无向图
        (g->map)[v][u] = 1;
}

Graph * buildGraphFromFile(char *fileName)
{
    FILE *fp;
    int n, e;
    int u, v;
    Graph *g;

    fp = fopen(fileName, "r+");
    assert(fp);
    if (fscanf(fp, "%d %d", &n, &e) != 2)
        return NULL;
    g = (Graph *)malloc(sizeof(Graph));
    initGraph(g, n, 0); // 初始化无向图
    while (fscanf(fp, "%d %d", &u, &v) == 2)
        insertEdge(g, u, v);
    return g;
}

void dfs(Graph *g, int v)
{
    int i;
    int n = g->n;
    visited[v] = 1;
    for (i = 0; i < n; ++i) {
        if (!visited[i] && (g->map)[v][i]) { // 遍历没有访问到的邻接点
            from[i] = v;
            dfs(g, i);
        } // end-if
    } // end-for
}

// 从 s 出发深度优先遍历
void path(Graph *g, int s)
{
    int n = g->n;
    assert(s >= 0 && s < n);
    dfs(g, s);
}

void printPath(Graph *g, int s, int u)
{
    int curV;
    SqStack *stack;
    initStack(&stack, g->n);
    path(g, s); // 从s开始深度优先遍历, 填充了from数组

    curV = u;
    push(stack, curV);
    while (curV != s) {
        curV = from[curV];
        push(stack, curV);
    }

    while (!isEmpty(stack)) {
        printf("%d", top(stack));
        if (stack->top)
            printf("%s", " -> ");
        else
            putchar('\n');
        pop(stack);
    }
    destoryStack(stack);
}

int main()
{
    Graph *g = buildGraphFromFile("map2.tb");
    if (!g) return -1;
    printTable(g);
    path(g, 0);

    printPath(g, 0, 2); // 打印出从节点 0 到节点 2 的路径
    deleteGraph(g);
    return 0;
}
