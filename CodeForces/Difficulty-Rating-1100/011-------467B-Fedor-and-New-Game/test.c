#include <stdio.h>


int main(void)
{

    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int players[1002];

    for (int i = 1; i <= m + 1; i++)
        scanf("%d", &players[i]);

    int number_of_potential_friends = 0;

    for (int i = 1; i < m + 1; i++)
    {
        int number_of_different_bits = 0;

        int a = players[i];
        int b = players[m + 1];

        while (a || b)
        {
            if ((a & 1) != (b & 1))
                (number_of_different_bits)++;

            a /= 2;
            b /= 2;
        }

        if (number_of_different_bits <= k)
            (number_of_potential_friends)++;
    }

    printf("%d\n", number_of_potential_friends);

    return 0;

}
