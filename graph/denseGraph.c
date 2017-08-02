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

int *visited = NULL;
int *id = NULL;
int ccnt = 0;

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
    int i;
    int n = dg->n;
    for (i = 0; i < n; ++i) {
        free((dg->map)[i]);
        (dg->map)[i] = NULL;
    }
    free(dg->map);
    dg->map = NULL;
    if (visited) {
        free(visited);
        visited = NULL;
    }
    if (id) {
        free(id);
        id = NULL;
    }
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
void dfs(DenseGraph *sg, int v)
{
    int n = sg->n;
    int i;
    visited[v] = 1;
    id[v] = ccnt;

    // 遍历邻居节点
    for (i = 0; i < n; ++i) {
        if ((sg->map)[v][i] && !visited[i]) { // 邻接边, 没有被访问
            dfs(sg, i);
        }
    } // end-for
}


void getComponent(DenseGraph *sg)
{
    int n = sg->n;
    int i;
    ccnt = 0; // ccnt中保留的是连通分量的个数
    visited = (int *)malloc(sizeof(int) * n);
    id = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
        visited[i] = 0;
        id[i] = -1;
    }
    for (i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(sg, visited, i);
            ccnt++; //
        }
    } // end-for
}

// 判断两个节点是否在同一个连通分量中,在此之前需要执行 getComponent
void isConnected(DenseGraph *sg, int u, int v)
{
    return id(u) == id(v);
}


int main()
{
    DenseGraph dg;
    int n = 10;
    int directed = 0;
    initDenseGraph(&dg, 10, 0);
    addEdgeFromFile(&dg, "map.tb");
    printTable(&dg);
    printMatric(&dg);
    getComponent(&dg);
    printf("total component: %d\n", ccnt);
    deleteDenseGraph(&dg);
    return 0;
}
