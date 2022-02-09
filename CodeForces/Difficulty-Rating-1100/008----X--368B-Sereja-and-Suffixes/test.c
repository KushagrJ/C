#include <stdio.h>
#include <stdbool.h>


int main(void)
{

    int n, m;
    scanf("%d %d", &n, &m);

    // a[0] remains unused, since indexing begins from 1.

    // Initially, for 1 <= l <= n, a[l] is equal to the integer at the l-th
    // position in the input.

    // Later, instead of using another array 'b' with b[l] being equal to the
    // number of distinct integers among b[l], b[l + 1], ... , b[n], the original
    // array 'a' is reused.

    int a[100002];
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    a[n + 1] = 0;

    bool integer_has_been_encountered[100001] = { false };
    for (int i = n; i >= 1; i--)
    {
        if (!(integer_has_been_encountered[a[i]]))
        {
            integer_has_been_encountered[a[i]] = true;
            a[i] = 1;
        }

        else
        {
            a[i] = 0;
        }

        a[i] += a[i + 1];
    }

    for (int i = 0; i < m; i++)
    {
        int l;
        scanf("%d", &l);

        printf("%d\n", a[l]);
    }

    return 0;

}
