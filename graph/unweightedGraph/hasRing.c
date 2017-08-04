// 判断一个图中是否有环,有几个环

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "DenseGraph.h"

int main()
{
    char *fileName = "map2.tb";
    Graph *g = buildGraphFromFile(fileName);
    assert(g);

    printTable(g);
    deleteGraph(g);
    return 0;
}
