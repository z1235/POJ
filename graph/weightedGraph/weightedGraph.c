#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int n;
    int e;
    int directed;
    double **wMap;
} Graph;

Graph * initGraph(int n, int directed)
{
    int i, j;
    Graph *g = (Graph *)malloc(sizeof(Graph));
    printf("initGraph\n");
    g->n = n;
    g->e = 0;
    g->directed = directed;
    (g->wMap) = (double **)malloc(sizeof(double *) * n);
    for (i = 0; i < n; ++i)
        (g->wMap)[i] = (double *)malloc(sizeof(double) * n);
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            (g->wMap)[i][j] = 0;
        } // end-for
    } // end-for
    printf("init succ\n");
    return g;
}

void deleteGraph(Graph *g)
{
    int i;
    for (i = 0; i < g->n; ++i)
        free((g->wMap)[i]);
    free(g->wMap);
}

void insertEdge(Graph *g, int u, int v, double w)
{
    (g->wMap)[u][v] = w;
    if (!g->directed)
        (g->wMap)[v][u] = w;
}

Graph * buildGraphFromFile(const char *fileName)
{
    int n, directed;
    int u, v;
    double w;
    Graph *g = NULL;

    FILE *fp = fopen("fileName", "r+");
    if (fp = NULL) return NULL;
    if (fscanf(fp, "%d %d", &n, &directed) != 2)
        return NULL;
    g = initGraph(n, directed);
    while (fscanf(fp, "%d %d %lf", &u, &v, &w) == 3) {
        insertEdge(g, u, v, w);
    } // end-while

    fclose(fp);
    return g;
}

void showTable(Graph *g)
{
    int i, j;
    for (i = 0; i < g->n; ++i) {
        printf("vertex %d: ", i);
        for (j = 0; j < g->n; ++j) {
            if ((g->wMap)[i][j])
                printf(" (%d %lf) ", j, (g->wMap)[i][j]);
        } // end-for
        putchar('\n');
    } // end-for
}

int main()
{
    const char *fileName = "testG.txt";
    Graph *g = buildGraphFromFile(fileName);
    // showTable(g);
    // deleteGraph(g);

    return 0;
}
