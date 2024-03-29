#include <stdio.h>


// N is the number of items.
#define N 3

// P[i] is the profit of the i-th item.
const int P[N] = {10, 20, 50};
//                0   1   2

// W[i] is the weight of the i-th item.
const int W[N] = {2, 3, 4};
//                0  1  2

// M is the capacity of the knapsack.
#define M 6


int g_function(int(*)[M+1], int, int);
void print_table(int(*)[M+1]);


int main(void)
{

    int g_table[N+1][M+1];

    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= M; j++)
            g_table[i][j] = -1;

    printf("Max profit: %d\n", g_function(g_table, 0, M));

    printf("Items included: ");

    for (int i = 0, j = M; i < N; i++)
    {
        if (g_table[i][j] != g_table[i+1][j])
        {
            printf("%d ", i);
            j -= W[i];
        }
    }

    putchar('\n');

    return 0;

}


int g_function(int(* g_table)[M+1], int i, int j)
{

    if (g_table[i][j] != -1)
    {
        return g_table[i][j];
    }

    if (i == N)
    {
        g_table[i][j] = 0;

        print_table(g_table);
        putchar('\n');

        return 0;
    }

    // profit_1 is the max total profit including item i.
    int profit_1 = -1;

    if (j >= W[i])
        profit_1 = (g_function(g_table, (i+1), (j - W[i])) + P[i]);

    // profit_2 is the max total profit excluding item i.
    int profit_2 = g_function(g_table, (i+1), j);

    g_table[i][j] = ((profit_1 > profit_2) ? profit_1 : profit_2);

    print_table(g_table);
    putchar('\n');

    return g_table[i][j];

}


void print_table(int(* g_table)[M+1])
{

    printf("  ");
    for (int j = 0; j <= M; j++)
        printf("  %2d ", j);
    printf("\n");

    printf("  ");
    for (int j = 0; j <= M; j++)
        printf(" ----");
    putchar('\n');

    for (int i = 0; i <= N; i++)
    {
        printf("%d |", i);

        for (int j = 0; j <= M; j++)
        {
            if (g_table[i][j] != -1)
                printf(" %2d |", g_table[i][j]);
            else
                printf("    |");
        }
        putchar('\n');

        printf("  ");
        for (int j = 0; j <= M; j++)
            printf(" ----");
        putchar('\n');
    }

}





/*

 * The 0/1 Knapsack Problem :-

   Given a set of n items, with w[i] & p[i] (both integers) being the weight
   (in pounds) and profit (in dollars) of the i-th item, and a knapsack that can
   carry a maximum of m pounds, the aim is to fill the knapsack using a subset
   of the given set of items in a way that maximizes the total profit.

   In other words, given a set of n items, with w[i] & p[i] (both integers)
   being the weight (in pounds) and profit (in dollars) of the i-th item, the
   aim is to select a subset of the given set of items such that the total
   weight is less than or equal to m pounds and the total profit is maximized.

   A common application of the 0/1 knapsack problem is when a thief is robbing a
   store and they can either take an item or leave it behind.


   Now, to solve the 0/1 knapsack problem using dynamic programming, the
   four-step sequence to be followed is described below :-

   (1) The optimal substructure property of this problem is as follows:
       Suppose that after running some algorithm, it is found that for the set
       of items {0, 1, 2, 3, 4, 5, 6}, the subset {0, 2, 5} is an (not 'the')
       optimal selection (i.e. the subset {0, 2, 5} results in the maximum total
       profit) when the maximum allowed total weight is m pounds. Then, for the
       set of items {0, 1, 3, 4, 5, 6}, the subset {0, 5} must be an optimal
       selection when the maximum allowed total weight is (m - w[2]) pounds.
       This is because if there were a different optimal selection for the set
       of items {0, 1, 3, 4, 5, 6} leading to a larger profit when the maximum
       allowed total weight is (m - w[2]) pounds, then that selection could've
       been substituted in the place of {0, 5} in the subset {0, 2, 5} to get a
       larger total profit, which leads to a contradiction.

       According to this algorithm, to find the maximum total profit that can be
       achieved using the set of items {0, 1, ... , (n-1)} when the maximum
       allowed total weight is m pounds, the items are considered one by one
       from item (n-1) to item 0 and using the set of items
       {i, (i+1), ... , (n-1)}, it is checked whether including or excluding the
       i-th item in the selection leads to the maximum total profit.

   (2) Let g[i][j] be the maximum total profit that can be achieved using the
       set of items {i, (i+1), ... , (n-1)} when the maximum allowed total
       weight is j pounds.

       For the full problem, the maximum total profit that can be achieved using
       the set of items {0, 1, ... , (n-1)} when the maximum allowed total
       weight is m pounds is thus g[0][m].

       The recursive definition of the value of an optimal solution to this
       problem is as follows:
       (1) If i == n, i.e. if the set of items is empty, then g[i][j] == 0 for
           all possible values of j (i.e. 0 <= j <= m).
       (2) If i < n, i.e. if the set of items is {i, (i+1), ... , (n-1)}, then
           (i) if w[i] > j, i.e. if the weight of the i-th item is greater than
               the maximum allowed total weight, then g[i][j] == g[i+1][j].
           (ii) else, g[i][j] == max{g[i+1][j], g[i+1][j - w[i]] + p[i]}.

       For eg., let n == 10, i == 4 and w[4] == 3.
       The subproblem of finding an optimal selection from the set of items
       {4, 5, 6, 7, 8, 9} when the maximum allowed total weight is j pounds
       (0 <= j <= m) is solved in the following manner:
       First, it is checked whether the weight of item 4 (i.e. 3 pounds) is
       greater than the maximum allowed total weight (i.e. j pounds).
       If 3 > j, then item 4 cannot be included in the selection and thus, the
       maximum total profit that can be achieved using the set of items
       {4, 5, 6, 7, 8, 9} when the maximum total allowed weight is j pounds is
       equal to the maximum total profit that can be achieved using the set of
       items {5, 6, 7, 8, 9} when the maximum total allowed weight is j pounds.
       Else, i.e. if  3 <= j, then item 4 can either be included in or excluded
       from the selection -
           If item 4 is included, then the maximum total profit that can be
           achieved using the set of items {4, 5, 6, 7, 8, 9} when the maximum
           total allowed weight is j pounds is equal to the maximum total
           profit that can be achieved using the set of items {5, 6, 7, 8, 9}
           when the maximum total allowed weight is (j-3) pounds plus the profit
           of item 4.
           On the other hand, if item 4 is excluded, then the maximum total
           profit that can be achieved using the set of items {4, 5, 6, 7, 8, 9}
           when the maximum total allowed weight is j pounds is equal to the
           maximum total profit that can be achieved using the set of items
           {5, 6, 7, 8, 9} when the maximum total allowed weight is j pounds.

   (3) 0-1-KNAPSACK(n, p, w, m) -----------------------------------------> O(nm)

       1. Let g[n+1][m+1] be a new table
       2. for j = 0 to m
       3.     g[n][j] = 0
       4. for i = (n-1) to 0
       5.     for j = 0 to m
       6.         g[i][j] = g[i+1][j]
       7.         if (j >= w[i]) and (g[i+1][j - w[i]] + p[i] > g[i][j])
       8.             g[i][j] = g[i+1][j - w[i]] + p[i]
       9. return g

       Since to find the value of g[0][m], all the values of the table g aren't
       required to be found, therefore top-down memoization is better than
       bottom-up tabulation in this algorithm.

       According to the optimal substructure property, since an optimal solution
       to a problem always consists of optimal solutions to its subproblems,
       therefore storing only optimal solutions to smaller problems is
       enough to construct optimal solutions to bigger problems, as combining
       non-optimal solutions to smaller problems can never lead to optimal
       solutions to bigger problems.

       When optimal solutions to smaller problems are found, only one of those
       multiple (possibly) optimal solutions having the same value is stored.
       Does the choice of optimal solution matter in this algorithm?
       [To be answered]

   (4) PRINT-SELECTED-ITEMS(g, n, m)

       1. j = m
       2. for i = 0 to (n-1)
       3.     if g[i][j] != g[i+1][j]
       4.         print i
       5.         j = j - W[i]

 */
