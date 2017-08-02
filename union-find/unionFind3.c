#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef struct {
    int *parent; // 指向父节点
    int *cnt;   // 该集合拥有的元素的个数
    int size;
} UnionFind;

void initUnionFind(UnionFind *uf, int n)
{
    int i;
    uf->size = n;
    uf->parent = (int *)malloc(sizeof(int) * n);
    uf->cnt = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
        (uf->parent)[i] = i;
        (uf->cnt)[i] = 1;
    }
}

int find(UnionFind *uf, int i)
{
    assert(i < uf->size && i >= 0);
    while (i != (uf->parent)[i])
        i = (uf->parent)[i];
    return i;
}

int find2(UnionFind *uf, int i)
{
    assert(i < uf->size && i >= 0);
    while (i != (uf->parent)[i]) {
        (uf->parent)[i] = (uf->parent)[(uf->parent)[i]];
        i = (uf->parent)[i];
    }
    return i;
}

void unionElements(UnionFind *uf, int p, int q)
{
    int pID = find(uf, p);
    int qID = find(uf, q);
    if (qID == pID)
        return;
    if ((uf->cnt)[pID] > (uf->cnt)[qID]) {
        (uf->parent)[qID] = pID;
        (uf->cnt)[pID] += (uf->cnt)[qID];
    }
    else {
        (uf->parent)[pID] = qID;
        (uf->cnt)[qID] += (uf->cnt)[pID];
    }
}

int isConnected(UnionFind *uf, int p, int q)
{
    return find(uf, p) == find(uf, q);
}

void testUnionFind(UnionFind *uf, int testSize)
{
    int i;
    int a, b;
    clock_t t1, t2;
    srand(time(NULL));
    t1 = clock();
    for (i = 0; i < testSize; ++i) {
        a = rand() % uf->size;
        b = rand() % uf->size;
        unionElements(uf, a, b);
    }
    for (i = 0; i < testSize; ++i) {
        a = rand() % uf->size;
        b = rand() % uf->size;
        isConnected(uf, a, b);
    }
    t2 = clock();
    printf("used: %lf\n", (double)(t2 - t1)/CLOCKS_PER_SEC);
}
void deleteUnionFind(UnionFind * uf)
{
    if (uf->parent) {
        free(uf->parent);
        free(uf->cnt);
        uf->parent = NULL;
        uf->cnt = NULL;
        uf->size = 0;
    } // end-if
}

int main()
{
    UnionFind uf;
    int n = 100;
    int testSize = 10000000;
    initUnionFind(&uf, n);
    testUnionFind(&uf, testSize);
    deleteUnionFind(&uf);
    return 0;
}
