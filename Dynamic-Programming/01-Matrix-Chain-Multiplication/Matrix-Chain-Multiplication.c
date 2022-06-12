// 30 35 15 5 10 20 25

#include <stdio.h>
#include <stdlib.h>


void matrix_chain_order(size_t*, size_t, size_t**, size_t**);
void print_optimal_parenthesization(size_t**, size_t, size_t);


int main(void)
{

    size_t n;
    printf("Enter the number of matrices: ");
    scanf("%zu", &n);

    size_t* p = malloc((n+1) * sizeof (size_t));
    if (p == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        return EXIT_FAILURE;
    }

    printf("Enter the dimensions: ");
    for (size_t i = 0; i <= n; i++)
        scanf("%zu", &(p[i]));

    size_t** m = malloc(n * sizeof(size_t*));
    if (m == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        return EXIT_FAILURE;
    }

    size_t** s = malloc(n * sizeof(size_t*));
    if (s == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; i++)
    {
        m[i] = malloc(n * sizeof (size_t));
        if (m[i] == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            return EXIT_FAILURE;
        }

        s[i] = malloc(n * sizeof (size_t));
        if (s[i] == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            return EXIT_FAILURE;
        }
    }

    matrix_chain_order(p, n, m, s);

    printf("\nMinimum no. of scalar multiplications = %zu\n", m[0][n-1]);

    print_optimal_parenthesization(s, 0, (n-1));
    putchar('\n');

    free(p);

    for (size_t i = 0; i < n; i++)
    {
        free(m[i]);
        free(s[i]);
    }

    free(m);
    free(s);

    return EXIT_SUCCESS;

}


void matrix_chain_order(size_t* p, size_t n, size_t** m, size_t** s)
{

    for (size_t i = 0; i <= (n-1); i++)
        m[i][i] = (size_t) 0;

    for (size_t l = 2; l <= n; l++)
    {
        for (size_t i = 0; i <= (n-l); i++)
        {
            size_t j = (i + l - 1);

            m[i][j] = (size_t) -1; // -1 gets wrapped to size_t's max value.

            for (size_t k = i; k <= (j-1); k++)
            {
                size_t q = (m[i][k] + m[k+1][j] + (p[i] * p[k+1] * p[j+1]));

                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

}


void print_optimal_parenthesization(size_t** s, size_t i, size_t j)
{

    if (i == j)
    {
        printf("A%zu", i);
    }

    else
    {
        printf("(");
        print_optimal_parenthesization(s, i, s[i][j]);
        print_optimal_parenthesization(s, (s[i][j] + 1), j);
        printf(")");
    }

}





/*

 * Dynamic programming, like divide-and-conquer, is a strategy to solve a
   problem by combining the solutions to its subproblems.
 * Both approaches may use either recursion or iteration to solve problems.
 * While divide-and-conquer may be applied to problems whose respective
   algorithm encounters overlapping or non-overlapping subproblems, dynamic
   programming can only be applied to problems whose corresponding algorithm
   encounters overlapping subproblems.
 * The technique called 'memoization' refers to storing the answers to the
   subproblems in a table when solving a problem in a 'top-down' fashion,
   whereas the technique called 'tabulation' refers to storing the answers to
   the subproblems in a table when solving a problem in a 'bottom-up' fashion.
   Both of these techniques are discussed below to solve the problem of
   finding the n-th fibonacci number using divide-and-conquer.
 * To solve a problem whose respective algorithm encounters overlapping
   subproblems, dynamic programming always uses memoization/tabulation, whereas
   divide-and-conquer may or may not use memoization/tabulation.

 * The corresponding algorithm encountering overlapping subproblems is not
   sufficient for dynamic programming to be applicable for a problem.
   In addition to the corresponding algorithm encountering overlapping
   subproblems, a problem must also have the optimal substructure property.
 * This means that the problem must be of an optimization type, i.e. the problem
   must have multiple possible solutions, out of which one or more solutions
   must be the optimal ones, and, more importantly, the optimal solution to the
   problem must be composed of the optimal solutions to its subproblems.


 * Problems which have the overlapping subproblems property, but not the optimal
   substructure property, are technically not examples of dynamic programming,
   and are actually examples of divide-and-conquer.

 * For eg., the problem of finding the n-th fibonacci number (n >= 1) can be
   solved in many different ways using divide-and-conquer :-

   (1) Recursion -

       def fibonacci(n):
           if (n == 1) or (n == 2):
               return (n-1)
           return (fibonacci(n-1) + fibonacci(n-2))

   (2) Memoization (top-down) (better than method (1)) -

       fib_dict = {}
       def fibonacci(n):
           if n in fib_dict:
               return fib_dict[n]
           if (n == 1) or (n == 2):
               fib_dict[n] = (n-1)
               return (n-1)
           fib_dict[n] = (fibonacci(n-1) + fibonacci(n-2))
           return fib_dict[n]

   (3) Tabulation (bottom-up) (better than method (2)) -

       fib_dict = {}
       def fibonacci(n):
           fib_dict[1] = 0
           fib_dict[2] = 1
           for i in range(3, (n+1)):
               fib_dict[i] = (fib_dict[i-1] + fib_dict[i-2])
           return fib_dict[n]

       or

       def fibonacci(n):
           if (n == 1) or (n == 2):
               return (n-1)
           fib_i_minus_1 = 1
           fib_i_minus_2 = 0
           for i in range(3, (n+1)):
               fib_i = (fib_i_minus_1 + fib_i_minus_2)
               fib_i_minus_1, fib_i_minus_2 = fib_i, fib_i_minus_1
           return fib_i

 * In method (1), the overlapping subproblems are calculated again and again,
   whereas in methods (2) and (3), the overlapping subproblems are calculated
   just once and stored in a table for future use.
 * Thus, the problem of finding the n-th fibonacci number is not a dynamic
   programming problem, as it doesn't have the optimal substructure property.

 * Memoization usually requires more code and is less straightforward, but has
   computational advantages in some problems, mainly those in which all the
   values for the whole matrix aren't required to be computed in order to reach
   the final answer.
 * Tabulation, on the other hand, is more straightforward, but may compute
   unnecessary values.
   If it is required for a program to compute all the values, then this method
   is usually faster, because of the smaller overhead.


 * When developing a dynamic programming algorithm, a sequence of four steps
   needs to be followed -
   (1) Characterize the structure of an optimal solution (and identify the
       optimal substructure).
   (2) Recursively define the value of an optimal solution (and identify the
       overlapping subproblems which would be encountered by the corresponding
       algorithm).
   (3) Compute the value of an optimal solution, typically in a bottom-up
       fashion.
   (4) Construct an optimal solution from the computed information.
 * Steps 1-3 form the basis of a dynamic programming solution to a problem.
   If only the value of an optimal solution is needed, and not the solution
   itself, then step 4 can be omitted.
 * When step 4 is required to be performed, additional information is sometimes
   maintained during step 3 to simplify step 4.

 */





 /*

 * The Matrix Chain Multiplication Problem :-

   Given a chain A_0, A_1, ... , A_(n-1) of n matrices, where for i = 0, 1, ...,
   (n-1), matrix A_i has dimensions p[i] * p[i+1], the aim is to fully
   parenthesize the product (A_0 A_1 ... A_(n-1)) in a way that minimizes the
   total number of scalar multiplications.

   If a matrix A has dimensions (p * q), and another matrix B has dimensions
   (q * r), then the number of scalar multiplications required to compute the
   product (A * B) is equal to (p * q * r).


   As an aside, the following function performs the operation c = (c + (a * b)),
   where a, b and c are three matrices (2-D arrays) having dimensions (p * q),
   (q * r) and (p * r), respectively.
   To perform c = (a * b), c can be initially initialized to 0.

   void matrix_multiply(int** a, int** b, int** c, int p, int q, int r)
   {
       for (int i = 0; i < p; i++)
           for (int j = 0; j < r; j++)
               for (int k = 0; k < q; k++)
                   c[i][j] += (a[i][k] * b[k][j]);
   }


   Matrix multiplication is associative (although not commutative), and so all
   parenthesizations yield the same product.

   How a chain of matrices to be multiplied is parenthesized can have a dramatic
   impact on the cost of evaluating the product.
   For eg., let the dimensions of the matrices A, B and C be (10 * 100),
   (100 * 5) and (5 * 50), respectively.
   Then, to compute the product ((A * B) * C), the total number of scalar
   multiplications to be done is 7500, whereas to compute the product
   (A * (B * C)), the total number of scalar multiplications to be done is
   75000.
   Thus, computing the product according to the first parenthesization is 10
   times faster.

   It should be noted that the matrix chain multiplication problem does not
   entail actually multiplying the matrices. The goal is only to determine an
   order for multiplying the matrices that has the lowest cost.
   Typically, the time invested in determining this optimal order is more than
   paid for by the time saved later when actually performing the matrix
   multiplications (such as performing only 7500 scalar multiplications instead
   of 75000).


   Let P(n) denote the number of alternative parenthesizations of a chain of n
   matrices.

   When n == 1, the chain consists of just one matrix, and therefore there is
   only one way to fully parenthesize the matrix product. So, P(1) == 1.

   Now, let the chain of matrices be A_0, A_1, ... , A_(n-1).

   If the product is split as (A_0) (A_1 A_2 ... A_(n-1)), then the total number
   of ways to fully parenthesize this entire product is equal to the total
   number of ways to fully parenthesize the product (A_0) multiplied by the
   total number of ways to fully parenthesize the product (A_1 A_2 ... A_(n-1)),
   which is equal to P(1) * P(n-1).

   Moving on, if the product is split as (A_0 A_1) (A_2 A_3 ... A_(n-1)), then
   the total number of ways to fully parenthesize this entire product is equal
   to the total number of ways to fully parenthesize the product (A_0 A_1)
   multiplied by the total number of ways to fully parenthesize the product
   (A_2 A_3 ... A_(n-1)), which is equal to P(2) * P(n-2).

   Continuing in this manner, it can be seen that when n >= 2, the total number
   of ways to fully parenthesize the product (A_0 A_1 A_2 ... A_(n-1)) is equal
   to the summation of (P(k) * P(n-k)), with k varying from 1 to (n-1).


   Now, to solve the matrix chain multiplication problem using dynamic
   programming, the four-step sequence to be followed is described below :-

   (1) Let A_(i:j), where i <= j, denote the matrix that results from evaluating
       the product (A_i A_(i+1) ... A_j).

       If i == j, then the chain consists of just one matrix, and therefore no
       scalar multiplications need to be done to compute the product.

       If i < j, then to compute A_(i:j), the product (A_i A_(i+1) ... A_j)
       must be split between A_k and A_(k+1) for some integer k in the range
       i <= k < j, i.e. for some value of k, the matrices A_(i:k) and
       A_((k+1):j) must be computed first, and then they must be multiplied
       together to produce the final matrix A_(i:j).

       The optimal substructure property of this problem is as follows:
       Suppose that after running some algorithm, it is found that splitting the
       product (A_i A_(i+1) ... A_j) between A_k and A_(k+1) (i <= k < j)
       results in an optimal parenthesization.
       Then, the way in which the product (A_i A_(i+1) ... A_k) is parenthesized
       within this optimal parenthesization of (A_i A_(i+1) ... A_j) must also
       be an optimal parenthesization of (A_i A_(i+1) ... A_k).
       This is because if there were a less costly way to parenthesize
       (A_i A_(i+1) ... A_k), then that parenthesization could've been
       substituted in the optimal parenthesization of (A_i A_(i+1) ... A_j) to
       produce another way to parenthesize (A_i A_(i+1) ... A_j) whose cost
       would be lower than the optimal cost, which leads to a contradiction.
       Similarly, the way in which the product (A_(k+1) A_(k+2) ... A_j) is
       parenthesized must also be its optimal parenthesization.

       Now, to find an optimal way to parenthesize the product,
       (1) the product (A_i A_(i+1) ... A_j) must be split into two subproducts,
           i.e. (A_i A_(i+1) ... A_k) and (A_(k+1) A_(k+2) ... A_j),
       (2) optimal ways to parenthesize each of these two subproducts must be
           found, and
       (3) optimal parenthesizations of these two subproducts must be combined
           to get an optimal parenthesization of the entire product
           (A_i A_(i+1) ... A_j).
       [The algorithm used to find an optimal solution to a dynamic programming
        problem is easier to understand when that algorithm has been
        implemented in a bottom-up fashion]

       To ensure that the split that has been chosen is optimal, all possible
       splits (i.e. all possible values of k) need to be considered.

   (2) Given the input dimensions p[0], p[1], ... , p[n], an index pair (i, j)
       specifies a subproblem.

       Let m[i][j] be the value of an optimal solution to the subproblem (i, j),
       i.e. let m[i][j] be the minimum number of scalar multiplications required
       to compute A_(i:j).

       For the full problem, the minimum number of scalar multiplications
       required to compute A_(0:(n-1)) is thus m[0][n-1].

       Suppose that splitting the product (A_i A_(i+1) ... A_j) between A_k and
       A_(k+1) (i <= k < j) results in an optimal parenthesization.
       Then, m[i][j] equals the minimum number of scalar multiplications
       required to compute A_(i:k) (i.e. m[i][k]), plus the minimum number of
       scalar multiplications required to compute A_((k+1):j) (i.e. m[k+1][j]),
       plus the number of scalar multiplications required to compute the product
       A_(i:k) * A_((k+1):j) (i.e. p[i] * p[k+1] * p[j+1]).

       The recursive definition of the value of an optimal solution to this
       problem is as follows:
       (1) If i == j, then m[i][j] == 0, as no scalar multiplications need to be
           done to compute A_(i:i).
           Thus, m[i][i] == 0 for i == 0, 1, ... , (n-1).
       (2) If i < j, then m[i][j] == the minimum value of
           m[i][k] + m[k+1][j] + (p[i] * p[k+1] * p[j+1]) over all possible
           values of k (i.e. i <= k < j).
       (3) If i > j, then m[i][j] == NIL, as i > j means an invalid subproblem.

       The overlapping subproblems property of this problem is as follows:
       According to the above definition of the value of an optimal solution,
       to calculate the minimum number of scalar multiplications required to
       compute the product of a chain of length l >= 2, the minimum number of
       scalar multiplications required to compute each and every chain of
       lengths 1 to (l-1) in that range need to be known.
       Now, to compute a chain of length (l+1), again the minimum number of
       scalar multiplications required to compute each and every chain of
       lengths 1 to l in that range need to be known.
       As l tends to n, the number of times the same optimal values of the
       solutions to the subproblems are used increases.

       To help construct an optimal solution during step 4, let s[i][j] be the
       value of k at which the product (A_i A_(i+1) ... A_j) is split in an
       optimal parenthesization.

   (3) MATRIX-CHAIN-ORDER(p, n) ----------------------------------------> O(n^3)

       01. Let m[n][n] and s[n][n] be new tables
       02. for i = 0 to (n-1) ------------------------------------------> O(n)
       03.     m[i][i] = 0
       04. for l = 2 to n ----------------------------------------------> O(n^3)
       05.     for i = 0 to (n-l)
       06.         j = i + l - 1
       07.         m[i][j] = infinity
       08.         for k = i to (j-1)
       09.             q = m[i][k] + m[k+1][j] + (p[i] * p[k+1] * p[j+1])
       10.             if q < m[i][j]
       11.                 m[i][j] = q
       12.                 s[i][j] = k
       13. return m and s

       After every iteration of the for loop of line 04, an optimal solution to
       each and every subproblem of size l is found.

       According to the optimal substructure property, since an optimal solution
       to a problem always consists of optimal solutions to its subproblems,
       therefore storing only optimal solutions to smaller problems is
       enough to construct optimal solutions to bigger problems, as combining
       non-optimal solutions to smaller problems can never lead to optimal
       solutions to bigger problems.

       When optimal solutions to smaller problems are found, only one of those
       multiple (possibly) optimal solutions having the same value is stored.
       But, for this algorithm, it doesn't matter which optimal solution to a
       smaller problem is stored.
       For eg., if (A_0 A_1 ... A_k) (A_(k+1) A_(k+2) ... A_(n-1)) is an optimal
       parenthesization, then which optimal parenthesization is used for
       (A_0 A_1 ... A_k) doesn't matter, as any optimal parenthesization of
       (A_0 A_1 ... A_k) will lead to the same value of an optimal solution to
       the bigger problem.

   (4) PRINT-OPTIMAL-PARENTHESIZATION(s, i, j)

       1. if i == j
       2.     print "A"i
       3. else
       4.     print "("
       5.     PRINT-OPTIMAL-PARENTHESIZATION(s, i, s[i][j])
       6.     PRINT-OPTIMAL-PARENTHESIZATION(s, (s[i][j] + 1), j)
       7.     print ")"

 */
