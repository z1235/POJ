#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef struct {
    int *parent;
    int size;
} QuickUnion;

void initQuickUnion(QuickUnion *qu, int n)
{
    int i;
    qu->size = n;
    qu->parent = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i)
        (qu->parent)[i] = i;
}

int find(QuickUnion *qu, int p)
{
    assert(p >= 0 && p < qu->size);
    while (p != (qu->parent)[p])
        p = (qu->parent)[p];
    return p;
}

void unionElements(QuickUnion *qu, int p, int q)
{
    int pID = find(qu, p);
    int qID = find(qu, q);
    if (pID == qID)
        return;
    (qu->parent)[pID] = qID;
}

int isConnected(QuickUnion *qu, int p, int q)
{
    return find(qu, p) == find(qu, q);
}

void deleteQuickUnion(QuickUnion *qu)
{
    if (qu->parent) {
        free(qu->parent);
        qu->size = 0;
        qu->parent = NULL;
    } // end-if
}

void testUnionFind(QuickUnion *qu, int n)
{
    int i;
    int a, b;
    clock_t t1, t2;
    srand(time(NULL));
    t1 = clock();
    for (i = 0; i < n; ++i) {
        a = rand() % qu->size;
        b = rand() % qu->size;
        unionElements(qu, a, b);
    }
    for (i = 0; i < n; ++i) {
        a = rand() % qu->size;
        b = rand() % qu->size;
        isConnected(qu, a, b);
    }
    t2 = clock();
    printf("used %lf s\n", (double)(t2 - t1)/CLOCKS_PER_SEC);
}

int main()
{
    QuickUnion qu;
    int n = 100;
    int testSize = 10000;
    initQuickUnion(&qu, n);
    testUnionFind(&qu, testSize);
    deleteQuickUnion(&qu);
    return 0;
}
