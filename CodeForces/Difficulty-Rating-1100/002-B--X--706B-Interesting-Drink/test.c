#include <stdio.h>


int main(void)
{

    // a[0] will remain unused.
    // a[1] will be equal to the no. of shops in which the price of the drink is
    // less than or equal to 1 coin.
    // a[2] will be equal to the no. of shops in which the price of the drink is
    // less than or equal to 2 coins.
    // and so on.
    int a[100001] = { 0 };

    // For eg., let n be equal to 5 and let the x's be equal to 100, 1000, 10,
    // 100 & 10000.

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);

        (a[x])++;
    }

    // At this stage, a[10] is equal to 1, a[100] is equal to 2, a[1000] is equal
    // to 1 and a[10000] is equal to 1.
    // All other a's are equal to 0.

    for (int i = 2; i < 100001; i++)
        a[i] += a[i - 1];

    // At this stage,
    // a[1], a[2], ... , a[9] are each equal to 0.
    // a[10], a[11], ... , a[99] are each equal to 1.
    // a[100], a[101], ... , a[999] are each equal to 3.
    // a[1000], a[1001], ... , a[9999] are each equal to 4.
    // a[10000], a[10001], ... , a[100000] are each equal to 5.

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++)
    {
        int m;
        scanf("%d", &m);

        // The value of m (i.e. the number of coins Vasiliy can spend) can go up
        // to 1000000000, but since the maximum price of the drink is 100000
        // coins, therefore the following conditional expression is used.
        printf("%d\n", a[(m < 100000) ? m : 100000]);
    }

    return 0;

}
