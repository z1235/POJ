#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef struct {
    int *id;
    int cnt;
} Union;

// 初始化一个 Union
void initUnion(Union * u, int n)
{
    int i;
    u->id = (int *)malloc(sizeof(int) * n);
    u->cnt = n;
    for (i = 0; i < n; ++i) {
        (u->id)[i] = i;
    }
}

// 查找对应的序号值
int find(Union *u, int p)
{
    assert(p < u->cnt && p >= 0);
    return (u->id)[p];
}

// 判断是否是连接的状态
int isConnected(Union *u, int p, int q)
{
    return find(u, p) == find(u, q);
}

// 将两个元素划到同一个 union中去
void unionElements(Union *u, int p, int q)
{
    int i;
    int pID = find(u, p);
    int qID = find(u, q);
    if (pID == qID)
        return;

    for (i = 0; i < u->cnt; ++i) {
        if ((u->id)[i] == pID)
            (u->id)[i] = qID;
    }
}

// 回收 Union 的空间
void deleteUnion(Union *u)
{
    if (u->id) {
        free(u->id);
        u->id = 0;
        u->cnt = 0;
    } // end-if
}

// 打印 id 元素
void printElem(Union *u)
{
    int i;
    for (i = 0; i < u->cnt; ++i) {
        printf("%d ", (u->id)[i]);
    }
    putchar('\n');
}

// 使用 n 规模的随机数据进行测试
void testUnionFind(Union *u, int n)
{
    int i;
    int a, b;
    clock_t t1, t2;
    srand(time(NULL));
    t1 = clock();
    for (i = 0; i < n; ++i) {
        a = rand() % u->cnt;
        b = rand() % u->cnt;
        unionElements(u, a, b);
    }
    for (i = 0; i < n; ++i) {
        a = rand() % u->cnt;
        b = rand() % u->cnt;
        isConnected(u, a, b);
    }
    t2 = clock();
    printf("used: %lf s\n", (double)(t2 - t1)/CLOCKS_PER_SEC);
}

int main()
{
    Union u;
    int n = 100;
    int testSize = 10000000;

    initUnion(&u, n);
    testUnionFind(&u, testSize);
    deleteUnion(&u);
}
