// 有 n 项工作，每项工作分别在 si 时间开始，在 ti 时间结束。对于每项工作，你都可以选择参与
// 与否，如果选择了参与，那么从始至终都必须全程参与，此外，参与工作的时间段不能够重叠（即使是
// 开始的瞬间和结束的瞬间的重叠也是不被允许的）
// 你的目标是参与尽可能多的工作，那么你最多参与多少项工作?
// 限制条件： 1 <= N <= 100000 1 <= si <= ti <= 10 ^ 9

#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100000

typedef struct {
    int s;  // 开始时间
    int t;  // 结束时间
} Event;

// 用于排序的比较函数
int cmp(const void *a, const void *b)
{
    Event *p = (Event *)a;
    Event *q = (Event *)b;
    return (p->t - q->t);   //按照结束时间的升序排列
}

// 对输入的工作集合，返回嘴都参与的工作数
int solve(Event *pEvent, int n)
{
    int i = 0;
    int ret = 0;
    int t = 0; // 上一个工作的结束时间

    qsort(pEvent, n, sizeof(Event), cmp); // 对输入的工作集进行快速排序
    for (i = 0; i < n; ++i) {
        if (pEvent[i].s > t) {
            ret++;
            t = pEvent[i].t;
        }
    }
    return ret;
}

int main()
{
    int n = 0;
    int i = 0;
    int maxEvent = 0;
    Event *pEvent = NULL;

    scanf("%d", &n);
    pEvent = (Event *)malloc(sizeof(Event) * n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &pEvent[i].s);
    }
    for (i = 0; i < n; ++i) {
        scanf("%d", &pEvent[i].t);
    }
    maxEvent = solve(pEvent, n);
    printf("max event: %d\n", maxEvent);

    free(pEvent);
    return 0;
}
