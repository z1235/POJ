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

// 将邻接矩阵打印出来
void printMatric(DenseGraph *dg)
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

// 将邻接表打印出来
void printTable(DenseGraph *dg)
{
    int i, j;
    int n = dg->n;
    for (i = 0; i < n; ++i) {
        printf("vertrix %d: ", i);
        for (j = 0; j < n; ++j)
            if ((dg->map)[i][j] != 0)
                printf("%d ", j);
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

// 从文件中插入边
void addEdgeFromFile(DenseGraph *dg, char *fileName)
{
    int u, v;
    FILE *fp = NULL;
    fp = fopen(fileName, "r+");
    assert(fp);

    while (fscanf(fp, "%d %d", &u, &v) == 2)
        insertEdge(dg, u, v);
    fclose(fp);
}

// 根据文件中数据初始化一个图

// 求一个图的连通分量
void dfs(DenseGraph *sg, int *visited, int v)
{
    int n = sg->n;
    int i;
    visited[v] = 1;
    // 遍历邻居节点
    for (i = 0; i < n; ++i) {
        if ((sg->map)[v][i] && !visited[i]) { // 邻接边, 没有被访问
            dfs(sg, visited, i);
        }
    } // end-for
}


int getComponent(DenseGraph *sg)
{
    int n = sg->n;
    int *visited = (int *)malloc(sizeof(int) * n);
    int cnt = 0;
    int i;
    for (i = 0; i < n; ++i)
        visited[i] = 0;
    for (i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(sg, visited, i);
            cnt++;
        }
    } // end-for

    free(visited);
    return cnt;
}

int main()
{
    DenseGraph dg;
    int n = 10;
    int directed = 0;
    int ccnt;
    initDenseGraph(&dg, 10, 0);
    addEdgeFromFile(&dg, "map.tb");
    printTable(&dg);
    printMatric(&dg);
    ccnt = getComponent(&dg);
    printf("total component: %d\n", ccnt);
    deleteDenseGraph(&dg);
    return 0;
}
