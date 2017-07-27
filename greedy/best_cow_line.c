// 给定长度为 N 的字符串 S,要构造一个长度为 N 的字符串 T，起初 T 是一个空串，随后反复进行
// 下列的任意操作。
// 从 S 的头部删除一个字符，加到 T 的尾部
// 从 S 的尾部删除一个字符，加到 T 的尾部
// 目标是构造字典序尽可能小的字符串 T
// 限制条件：
// 1 <= N <= 2000
// 字符串 S 只包含大写的英文字母
#include <stdio.h>
#include <stdlib.h>


void solve(char *pA, int n, char *pResult)
{
    int a = 0, b = n - 1; // 用于表示界桩
    int k = 0;
    int i = 0; // 游标
    int left = 0;

    while (a <= b) { // 每次循环向量减少一个，输出向量增加一个
        left = 0;   // 默认从右边取数
        for (i = 0; a + i < b - i; i++) {
            if (pA[a + i] < pA[b - i]) {
                left = 1;
                break;
            }
            else if (pA[a + i] > pA[b - i]) {
                left = 0;
                break;
            }
        } // end-for
        if (left)
            pResult[k++] = pA[a++];
        else
            pResult[k++] = pA[b--];
    }// end-while
}

int main()
{
    int n = 0;
    char *pA  = NULL;
    char *pResult = NULL; // 结果字符串
    int i = 0;

    scanf("%d", &n);
    getchar();
    pA = (char *)malloc(sizeof(char) * n);
    pResult = (char *)malloc(sizeof(char) * n);
    for (i = 0; i < n; ++i) {
        scanf("%c", &pA[i]);
        getchar();
    }
    solve(pA, n, pResult);
    for (i = 0; i < n; ++i) {
        putchar(pResult[i]);
        if ((i + 1) % 80 == 0) // 80的倍数
            putchar('\n');
    }
    putchar('\n');

    free(pA);
    free(pResult);
    return 0;
}
