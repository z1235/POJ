#ifndef DENSE_GRAPH_H_
#define DENSE_GRAPH_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n;
    int e;
    int directed;
    int **map;
} Graph;

void printTable(Graph *g)
{
    int i, j;
    int n = g->n;
    for (i = 0; i < n; ++i) {
        printf("vertrix %d: ", i);
        for (j = 0; j < n; ++j)
            if ((g->map)[i][j])
                printf("%d ", j);
        putchar('\n');
    } // end-for
}

void initGraph(Graph *g, int n, int directed)
{
    int i, j;
    (g->map) = (int **)malloc(sizeof(int *) * n);
    for (i = 0; i < n; ++i)
        (g->map)[i] = (int *)malloc(sizeof(int) * n);
    g->n = n;
    g->e = 0;
    g->directed = directed;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            (g->map)[i][j] = 0;
}



void deleteGraph(Graph *g)
{
    int i;
    int n = g->n;
    for (i = 0; i < n; ++i)
        free((g->map)[i]);
    free(g->map);
}

void insertEdge(Graph *g, int u, int v)
{
    assert(u >= 0 && u < g->n);
    assert(v >= 0 && u < g->n);
    assert(u != v); // 无环图
    (g->map)[u][v] = 1;
    if (!g->directed)  // 无向图
        (g->map)[v][u] = 1;
}

Graph * buildGraphFromFile(const char *fileName)
{
    int directed;
    int n;
    int u, v;
    Graph *g = (Graph *)malloc(sizeof(Graph));
    FILE *fp = fopen(fileName, "r+");
    assert(fp);

    if (fscanf(fp, "%d %d", &n, &directed) != 2)
        return NULL;

    initGraph(g, n, directed);
    while (fscanf(fp, "%d %d", &u, &v) == 2)
        insertEdge(g, u, v);
    return g;
}

#endif
