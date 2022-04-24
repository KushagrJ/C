#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>


// The first row (i.e. row 0) and the first column (i.e. column 0) of m and n are
// unused to make it seem as though the indexing of m and n starts from 1, not 0.


void matrix_chain_order(int, const int*, int**, int**);
void print_auxiliary_table(int, int**);
void print_optimal_parentheses(int, int**, int, int);


int main(void)
{

    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int* p = malloc((n+1) * sizeof (int));

    printf("Enter the dimensions: ");
    for (int i = 0; i <= n; i++)
        scanf("%d", &(p[i]));

    int** m = malloc((n+1) * sizeof (int*));
    int** s = malloc((n+1) * sizeof (int*));

    m[0] = NULL;
    s[0] = NULL;

    for (int i = 1; i <= n; i++)
    {
        m[i] = malloc((n+1) * sizeof (int));
        s[i] = malloc((n+1) * sizeof (int));
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            m[i][j] = s[i][j] = -1;

    matrix_chain_order(n, p, m, s);

    putchar('\n');
    print_auxiliary_table(n, m);
    putchar('\n');

    print_auxiliary_table(n, s);
    putchar('\n');

    print_optimal_parentheses(n, s, 1, n);
    putchar('\n');

    printf("\nOptimal cost = %d scalar multiplications\n", m[1][n]);

    free(p);

    for (int i = 1; i <= n; i++)
    {
        free(m[i]);
        free(s[i]);
    }

    free(m);
    free(s);

    return 0;

}


void matrix_chain_order(int n, const int* p, int** m, int** s)
{

    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= (n - l + 1); i++)
        {
            int j = (i + l - 1);
            m[i][j] = INT_MAX;

            for (int k = i; k <= (j - 1); k++)
            {
                long long q = ((long long) (m[i][k]) +
                                   (long long) (m[k+1][j]) +
                                       (long long) (p[i-1] * p[k] * p[j]));
                if (q < (long long) (m[i][j]))
                {
                    m[i][j] = (int) q;
                    s[i][j] = k;
                }
            }
        }
    }

}


void print_auxiliary_table(int n, int** table)
{

    int printing_width = (log10(table[1][n]) + 2);

    for (int j = 0; j < n; j++)
    {
        putchar(' ');

        for (int k = 0; k < (printing_width + 2); k++)
            putchar('-');
    }

    putchar('\n');


    for (int i = 1; i <= n; i++)
    {
        putchar('|');

        for (int j = 1; j <= n; j++)
        {
            if (table[i][j] == -1)
                printf(" %-*c ", printing_width, '-');
            else
                printf(" %-*d ", printing_width, table[i][j]);
            putchar('|');
        }

        putchar('\n');


        for (int j = 0; j < n; j++)
        {
            putchar(' ');

            for (int k = 0; k < (printing_width + 2); k++)
                putchar('-');
        }

        putchar('\n');
    }

}


void print_optimal_parentheses(int n, int** s, int i, int j)
{

    if (i == j)
    {
        printf("A%d", i);
    }

    else
    {
        printf("(");
        print_optimal_parentheses(n, s, i, s[i][j]);
        print_optimal_parentheses(n, s, s[i][j] + 1, j);
        printf(")");
    }

}
