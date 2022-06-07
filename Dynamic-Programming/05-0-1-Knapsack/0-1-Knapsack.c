#include <stdio.h>
#include <stdbool.h>
#include <limits.h>


#define N 3
const int w[N] = {2, 3, 4};
const int p[N] = {1, 2, 5};

#define M 6


int knapsack(bool*, int(*)[M + 1], int, int);


int main(void)
{

    printf("  Item: ");
    for (int i = 0; i < N; i++)
        printf("%d ", (i + 1));
    putchar('\n');

    printf("Weight: ");
    for (int i = 0; i < N; i++)
        printf("%d ", w[i]);
    putchar('\n');

    printf("Profit: ");
    for (int i = 0; i < N; i++)
        printf("%d ", p[i]);
    putchar('\n');

    bool is_included[N] = {false};

    int g[N + 1][M + 1];
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= M; j++)
            g[i][j] = -1;
    for (int j = 0; j <= M; j++)
        g[N][j] = 0;

    printf("\nKnapsack capacity: %d\n", M);

    printf("Max profit = %d\n", knapsack(is_included, g, 0, M));

    printf("Items included: ");
    for (int i = 0; i < N; i++)
        if (is_included[i])
            printf("%d ", (i + 1));
    putchar('\n');

    return 0;

}


int knapsack(bool* is_included, int(* g)[M + 1], int j, int y)
{

    if (j < N)
    {
        int max_profit_excluding_j;

        if (g[j + 1][y] != -1)
            max_profit_excluding_j = g[j + 1][y];
        else
            max_profit_excluding_j = knapsack(is_included, g, (j + 1), y);


        int max_profit_including_j = INT_MIN;

        if (y >= w[j])
        {
            if (g[j + 1][y - w[j]] != -1)
                max_profit_including_j = g[j + 1][y - w[j]];
            else
                max_profit_including_j = knapsack(is_included, g, (j + 1),
                                                  (y - w[j]));
            max_profit_including_j += p[j];
        }


        if (max_profit_excluding_j > max_profit_including_j)
        {
            g[j][y] = max_profit_excluding_j;
        }

        else
        {
            g[j][y] = max_profit_including_j;
            is_included[j] = true;
        }

        return g[j][y];
    }

    return 0;

}
