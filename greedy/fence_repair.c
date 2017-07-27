// Description POJ 3253
// Farmer John wants to repair a small length of the length of the fence arount
// the pasture. He measures the fense and finds that he needs N (1 <= N <= 20000)
// planks of wood, each having some interger length Li (1 <= Li <= 50000) units.
// He then purchase a single long board just long enought to saw into the N planks
// (i.e., whose length is the sum of the length Li), FJ is ignoring the "kerf", the
// extra length lost to sawdust when a sawcut is made; you should ignore it, too.
// FJ sadly realizes that he doesn't own a saw with which to cut the wood, so he mosies
// over to Farmer Don's Farm with this long board and politely asks if he may borrow a
// saw
// Famer Don, a closet capitalist, doesn't lead FJ a saw but instead offers to charge
// Farmer John for each if the N - 1 cuts in the plank. The charge to cut a piece of
// wood is exactly equal to its length. Cutting a plank of length 21 const 21 cents
// Famer Don then lets Farmer John decide the order and location to cut the plank.
// Help Farmer John determine the minimum amount of money he can spend to create the N
// planks. FJ knows that he can cut the board in various different orders which will
// result in different charges since that resulting intermediate planks are of different
// lengths.
// Input:
// Line1: One interger N, the numbers of planks
// Line2: N + 1: Each line contains a single interger describing the length of a needed plank
// Output:
// One interger: the minimum amount of money he must spend to make N - 1 cuts
// Sample Input:
// 3
// 8
// 5
// 8
// 34
// Hint:
// He wants to cut a board of length 21 into pieces of length 8, 5 and 8.
// The oroginal board measures 8 + 5 + 8 = 21. The first cut will cost 21, and should
// used to cut the board into pieces measuring 13 and 8. The second cut will cost
// 13, and should be used to cut the 13 into 8 and 5. This would cost 21 + 13 = 34. If
// the 21 was cut into 16 and 5 instead, the second cut would const 16 for a total of 37
// which is more than 34.
#include <stdio.h>
#include <stdlib.h>

#define N_MAX 20000
int L[N_MAX]; // store the length of planks

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

long long solve(int *L, int n)
{
    long long ret = 0;
    int m1 = 0, m2 = 0;
    int t = 0;
    int i = 0;

    while (n > 1) {
        m1 = 0;
        m2 = 1;                // m1 point to the min, m2 point to the second min
        if (L[m1] > L[m2]) {  // reverse the assumption
            swap(&m1, &m2);
        }
        for (i = 2; i < n; ++i) {
            if (L[i] < L[m1]) {
                m2 = m1;
                m1 = i;
            }
            else if (L[i] < L[m2]) {
                m2 = i;
            }
        } // end-for

        t = L[m1] + L[m2]; // make a big plank
        ret += t;
        if (m1 == n - 1) {
            swap(&m1, &m2);
        }
        L[m1] = t;
        L[m2] = L[n - 1];
        n--;
    }// end-while
    return ret;
}

int main()
{
    int n = 0, i = 0;

    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &L[i]);
    }
    printf("%lld\n", solve(L, n));
    return 0;
}
