// 有 n 个重量和价值为 wi和 vi的物品，从这些物品中挑选出总重量不超过 w 的物品， 求所有挑选方案
// 中价价值综合最大值
// 限制条件:
// 1 <= n <= 100
// 1 <= wi, vi <= 100
// 1 <= W <= 10000
// Sample Input:
// n = 4
// (w, v) = {{2, 3}, {1, 2}, {3, 4}, {2, 2}}
// W = 5
// Output: 7 (0, 1, 3物品)

#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100
int w[N_MAX] = {};
int v[N_MAX] = {};
int n = 0;

inline int max(int a, int b)
{
    return a > b ? a : b;
}

// 穷竭搜索
int solve(int x, int y)
{
    int ret = 0;

    if (x == n)  // 没有可以使用的商品
        ret = 0;
    else if (y < w[x]) //无法装下商品 x
        ret =
}



int main()
{
    int i = 0;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &w[i]);
    }
    for (i = 0; i < n; ++i) {
        scanf("%d", &v[i]);
    }

    printf("max value: %d\n", solve());
    return 0;
}
