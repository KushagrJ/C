#include <stdio.h>


int main(void)
{

    int n;
    scanf("%d", &n);

    int sum_a = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);

        sum_a += x;
    }

    int sum_b = 0;
    for (int j = 0; j < n - 1; j++)
    {
        int y;
        scanf("%d", &y);

        sum_b += y;
    }

    int sum_c = 0;
    for (int k = 0; k < n - 2; k++)
    {
        int z;
        scanf("%d", &z);

        sum_c += z;
    }

    printf("%d\n%d\n", sum_a - sum_b, sum_b - sum_c);

    return 0;

}
