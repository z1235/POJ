// 硬币问题
// 有 1元 5元 10元 50元 100元 500元的硬币各 C1 C5 C10 C50 C100 C500枚， 现在要用这些硬币支付A元，最少需要多少枚硬币
// 假设本题至少有一种支付方案
// 0 <= C1 C5 C10 C100 C500 <= 10^9
// 0 <= A <= 10^9

#include <stdio.h>
#include <stdlib.h>

#define COIN_KIND_MAX 6
const int COIN_VALUE[COIN_KIND_MAX] = {1, 5, 10, 50, 100, 500};

// C[0, n-1]存储了每种币值的硬币的数量， target表示最终的要求， solution中返回了每种币种使用的数量
int solve(const int *C, int n, int target, int *solution)
{
    int i = n - 1;
    int ret = 0; // 返回最少的硬币数
    while (i >= 0 && target) {
        solution[i] = target / COIN_VALUE[i];
        if (solution[i] > C[i]) // 根据实际拥有的硬币数量进行修正
            solution[i] = C[i];
        target -= COIN_VALUE[i] * solution[i];
        ret += solution[i];
        i--;
    }
    printf("total: %d\n", ret);
    return ret;
}

int main()
{
    int target = 0;
    int C[COIN_KIND_MAX] = {};
    int i = 0;
    int S[COIN_KIND_MAX] = {};      // 记录最优方案的硬币使用情况

    scanf("%d", &target);
    getchar();
    for (i = 0; i < COIN_KIND_MAX; ++i)
        scanf("%d", C + i);
    solve(C, COIN_KIND_MAX, target, S);

    return 0;
}
