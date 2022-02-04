#include <stdio.h>


int main(void)
{

    int n, k;
    scanf("%d %d", &n, &k);

    int a[150000];
    int current_sum = 0;

    for (int i = 0; i < k; i++)
    {
        scanf("%d", &a[i]);
        current_sum += a[i];
    }

    int minimum_sum = current_sum;

    int j = 1;

    for (int i = 0; i < n - k; i++)
    {
        current_sum -= a[i];
        scanf("%d", &a[i + k]);
        current_sum += a[i + k];

        if (current_sum < minimum_sum)
        {
            minimum_sum = current_sum;
            j = i + 2;
        }
    }

    printf("%d\n", j);

    return 0;

}
