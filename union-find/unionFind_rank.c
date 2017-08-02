#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef struct {
    int *parent;
    int *rank;
    int size;
} UnionFind;


void initUnionFind(UnionFind *uf, int n)
{
    int i;
    uf->size = n;
    uf->parent = (int *)malloc(sizeof(int) * n);
    uf->rank = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
        (uf->rank)[i] = i;
    }
}

int find(UnionFind *uf, int p)
{
    assert(p >= 0 && p < uf->size);
    while (p != (uf->parent)[p])
        p = (uf->parent)[p];
    return p;
}

int isConnected(UnionFind *uf, int p, int q)
{
    return find(uf, p) == find(uf, q);
}

void unionElements(UnionFind *uf, int p, int q)
{
    int pRoot = find(uf, p);
    int qRoot = find(uf, q);
    if (pRoot == qRoot)
        return;
    if ((uf->rank)[pRoot] > (uf->rank)[qRoot]) {
        (uf->parent)[qRoot] = pRoot;
    }
    else if ((uf->rank)[pRoot] < (uf->rank)[qRoot]) {
        (uf->parent)[pRoot] = qRoot;
    }
    else {
        (uf->parent)[pRoot] = qRoot;
        (uf->rank)[qRoot]++;
    }
}

void testUnionFind(UnionFind *uf, int testSize)
{
    clock_t t1, t2;
    int a, b;
    int i;
    srand(time(NULL));
    t1 = clock();
    for (i = 0; i < testSize; ++i) {
        a = rand() % (uf->size);
        b = rand() % (uf->size);
        unionElements(uf, a, b);
    }
    for (i = 0; i < testSize; ++i) {
        a = rand() % (uf->size);
        b = rand() % (uf->size);
        isConnected(uf, a, b);
    }
    t2 = clock();
    printf("used: %lf\n", (double)(t2 - t1)/CLOCKS_PER_SEC);
}

void deleteUnionFind(UnionFind *uf)
{
    if (uf->parent) {
        free(uf->parent);
        free(uf->rank);
        uf->parent = NULL;
        uf->parent = NULL;
        uf->size = 0;
    } // end-if
}

int main()
{
    int n = 100;
    int testSize = 10000000;
    UnionFind uf;
    initUnionFind(&uf, n);
    testUnionFind(&uf, testSize);
    deleteUnionFind(&uf);
    return 0;
}
