// 稠密图 使用矩阵形式进行存储
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int n;          // 节点的数目
    int e;          // 边的数目
    int directed;   // 是否是有向边
    int **map;      // 指向邻接矩阵
} DenseGraph;

void initDenseGraph(DenseGraph * dg, int n, int directed)
{
    int i, j;
    dg->map = (int **)malloc(sizeof(int *) * n); // 指向指针数组的指针
    for (i = 0; i < n; ++i) {
        (dg->map)[i] = (int *)malloc(sizeof(int) * n);
    }
    // init
    dg->n = n;
    dg->e = 0;
    dg->directed = directed;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            (dg->map)[i][j] = 0;
        } // end-for
    } // end-for
}

void printDenseGraph(DenseGraph *dg)
{
    int i, j;
    int n = dg->n;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%d ", (dg->map)[i][j]);
        } // end-for
        putchar('\n');
    } // end-for
}

// 释放稠密图的堆空间
void deleteDenseGraph(DenseGraph *dg)
{
    int i, j;
    int n = dg->n;
    for (i = 0; i < n; ++i) {
        free((dg->map)[i]);
    }
    free(dg->map);
    dg->e = 0;
    dg->n = 0;
}

// 插入一条边
void insertEdge(DenseGraph *dg, int u, int v)
{
    assert(u >= 0 && u < dg->n);
    assert(v >= 0 && v < dg->n);
    dg->e++;
    (dg->map)[u][v] = 1;
    if (!dg->directed) // 无向图
        (dg->map)[v][u] = 1;
}


int main()
{
    DenseGraph dg;
    int n = 10;
    int directed = 0;
    initDenseGraph(&dg, 10, 0);
    insertEdge(&dg, 1, 2);
    insertEdge(&dg, 1, 3);
    insertEdge(&dg, 1, 4);
    insertEdge(&dg, 2, 9);
    insertEdge(&dg, 3, 2);

    printDenseGraph(&dg);
    deleteDenseGraph(&dg);
    return 0;
}
