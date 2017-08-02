// 稀疏图 使用邻接表的形式进行组织
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int n;
    int e;
    int directed;
    int **map;
} SparseGraph;

void initSparseGraph(SparseGraph *sg, int n, int directed)
{
    int i, j;
    sg->n = n;
    sg->directed = directed;
    sg->e = 0;
    // 分配存储空间
    sg->map = (int **)malloc(sizeof(int *) * n);
    for (i = 0; i < n; ++i) {
        (sg->map)[i] = (int *)malloc(sizeof(int) * (n + 1)); // 第0个元素表示边的个数
    }
    // 初始化邻接表
    for (i = 0; i < n; ++i) {
        for (j = 0; j <= n; ++j) {
            (sg->map)[i][j] = 0;
        } // end-for
    } // end-for
}

int dispSparseGraph(SparseGraph *sg)
{
    int i, j;
    int cnt;
    int n = sg->n;

    for (i = 0; i < n; ++i) {
        cnt = (sg->map)[i][0];
        printf("node %d cnt %d to : ", i, (sg->map)[i][0]);
        for (j = 1; j <= cnt; ++j) {
            printf("%d ", (sg->map)[i][j]);
        } // end-for
        putchar('\n');
    } // end-for
}



void deleteSparseGraph(SparseGraph *sg)
{
    int i;
    for (i = 0; i < sg->n; ++i) {
        free((sg->map)[i]);
    }
    free(sg->map);
}

void insertEdge(SparseGraph *sg, int u, int v)
{
    int n = sg->n;
    assert(u >= 0 && u < n);
    assert(v >= 0 && v < n);
    sg->e++;
    (sg->map)[u][(sg->map)[u][0] + 1] = v;
    (sg->map)[u][0]++;
    if (!sg->directed) { // 无向图
        (sg->map)[v][(sg->map)[v][0] + 1] = u;
        (sg->map)[v][0]++;
    }
}


int main()
{
    SparseGraph sg;
    int n = 10;
    int directed = 0;
    initSparseGraph(&sg, n, directed);
    insertEdge(&sg, 1, 2);
    insertEdge(&sg, 1, 3);
    insertEdge(&sg, 1, 4);
    insertEdge(&sg, 2, 9);

    dispSparseGraph(&sg);
    deleteSparseGraph(&sg);
    return 0;
}
