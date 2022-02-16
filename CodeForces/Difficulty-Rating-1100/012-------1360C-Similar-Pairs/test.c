#include <stdio.h>
#include <stdbool.h>


int main(void)
{

    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n;
        scanf("%d", &n);

        int number_of_odd_integers = 0;

        int a[101] = { 0 };

        for (int i = 0; i < n; i++)
        {
            int x;
            scanf("%d", &x);

            if (x & 1)
                (number_of_odd_integers)++;

            (a[x])++;
        }

        bool at_least_one_pair_of_consecutive_integers_exists = false;

        for (int i = 1; i < 100; i++)
        {
            if (a[i] && a[i + 1])
            {
                at_least_one_pair_of_consecutive_integers_exists = true;
                break;
            }
        }

        if (number_of_odd_integers & 1)
        {
            if (at_least_one_pair_of_consecutive_integers_exists)
                printf("YES\n");
            else
                printf("NO\n");
        }

        else
        {
            printf("YES\n");
        }
    }

    return 0;

}
