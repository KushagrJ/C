// Modify this so that the input is taken from the user at runtime.

#include <stdio.h>
#include <limits.h>


const int p[] = {30, 35, 15, 5, 10, 20, 25};
const int n = ((sizeof p / sizeof p[0]) - 1);


// Set this at least as big as the width of the largest integer in the m matrix.
#define PRINTING_WIDTH 5


// Using int*[N+1], instead of int(*)[N+1], is incorrect, obviously.
void matrix_chain_order(int(*)[n+1], int(*)[n+1]);
void print_auxiliary_table(int(*)[n+1]);
void print_optimal_parentheses(int(*)[n+1], int, int);


int main(void)
{

    int m[n+1][n+1], s[n+1][n+1];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            m[i][j] = s[i][j] = -1;

    matrix_chain_order(m, s);

    print_auxiliary_table(m);
    putchar('\n');

    print_auxiliary_table(s);
    putchar('\n');

    print_optimal_parentheses(s, 1, n);
    putchar('\n');

    printf("\nOptimal cost = %d scalar multiplications\n", m[1][n]);

    return 0;

}


void matrix_chain_order(int(* m)[n+1], int(* s)[n+1])
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


void print_auxiliary_table(int(* m)[n+1])
{

    for (int j = 0; j < n; j++)
    {
        putchar(' ');

        for (int k = 0; k < (PRINTING_WIDTH + 2); k++)
            putchar('-');
    }

    putchar('\n');


    for (int i = 1; i <= n; i++)
    {
        putchar('|');

        for (int j = 1; j <= n; j++)
        {
            if (m[i][j] == -1)
                printf(" %-*c ", PRINTING_WIDTH, '-');
            else
                printf(" %-*d ", PRINTING_WIDTH, m[i][j]);
            putchar('|');
        }

        putchar('\n');


        for (int j = 0; j < n; j++)
        {
            putchar(' ');

            for (int k = 0; k < (PRINTING_WIDTH + 2); k++)
                putchar('-');
        }

        putchar('\n');
    }

}


void print_optimal_parentheses(int(* s)[n+1], int i, int j)
{

    if (i == j)
    {
        printf("A%d", i);
    }

    else
    {
        printf("(");
        print_optimal_parentheses(s, i, s[i][j]);
        print_optimal_parentheses(s, s[i][j] + 1, j);
        printf(")");
    }

}
