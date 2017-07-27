// Description POJ
// Saruman the white must lead his army along a straight path from Isengard to Helm's Deep.
// To keep track of his forces, Saruman distributes seeing stones, known as palantirs, among
// the troops. Each palantir has a maximum effictive range of R units, and must be carried by
// troop in the army (ie. palantirs are not allowed to "free float" in mid-air). Help Sarunman
// take control of Middle Earch by determining the minumum number of palantirs needed for Saruman
// to ensure that each of his minions is within R units of some palantri
// Input:
// The input test file will contain multiple cases. Each test case begins with single line
// containing an interger R, the maximum effictive range of all palantris (where 0 <= R <= 1000),
// and an integer n, the number of tropps in Saruman's army (where 1 <= n <= 1000). The next line
// contain n interger, indicating the positions x1, x2, ...xn of each troop(where 0 <= xi << 1000)
// The end-of-file is marked by a test case with R = n = -1
// output:
// For each test case, print a single interger indicating the minimum number of palantris needed
// Sample input:
// 0 3
// 10 20 20
// 10 7
// 70 30 1 7 15 20 50
// -1 -1
// Sample output:
// 2
// 4
// Hint:
// In the first test case, Saruman may place a palantris at Position 10 and 20
// Here, note that a single palantri with range 0 can cover both of the troops
// at position 20
// In the second test case, Saruman can place palantris at position 7 (covering troops
// at 1, 7, and 15), positin 20 (covering positions 20 and 30), position 50, and
// position 70. Here note tha palantris must be distributes among troops and are
// not allowed to "free float". Thus, Saruman cannot place a palantir and are not
// allowed to "free float". Thus, Saruman cannot place a palantir at position 60
// to cover the troops at positions 50 and 70.
#include <stdio.h>
#include <stdlib.h>

#define N_MAX 1000
int pos[N_MAX];

int cmp(const void *a, const void *b)
{
    int *p = (int *)a;
    int *q = (int *)b;
    return *p - *q;
}

int solve(int *pos, int n, int r)
{
    int i = 0;
    int s = 0, t = 0;
    int ret = 0;

    qsort(pos, n, sizeof(int), cmp);
    while (i < n) {
        s = pos[i];
        i++;
        while (i < n && pos[i] <= s + r)
            i++;
        t = pos[i - 1];
        ret++;
        while (i < n && pos[i] <= t + r)
            i++;
    } // end-while
    return ret;
}

int main()
{
    int r = 0, n = 0;
    int i = 0;

    scanf("%d %d", &r, &n);
    while (r != -1) {
        for (i = 0; i < n; ++i) {
            scanf("%d", &pos[i]);
        }
        printf("%d\n", solve(pos, n, r));
        scanf("%d %d", &r, &n);
    }
    return 0;
}
