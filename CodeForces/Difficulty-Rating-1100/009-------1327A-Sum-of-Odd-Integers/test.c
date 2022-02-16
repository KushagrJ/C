#include <stdio.h>


int main(void)
{

    int t;
    scanf("%d", &t);

    while (t--)
    {
        long long n, k;
        scanf("%lld %lld", &n, &k);

        if (((n - k) & 1) || (n < (k * k)))
            printf("NO\n");
        else
            printf("YES\n");
    }

    return 0;

}
