// Algorithm :-
//
//
// For eg., 0 1 2 3 (no. of elements, n = 4).
//
//
// Start with 0 1 2 3 as the first permutation.
//
//
// In the first iteration, make (n-1) copies of all existing permutations, and
// swap a[0] with a[1] in the first copy, a[0] with a[2] in the second copy, and
// so on -
//
// First copy of 0 1 2 3 -> 1 0 2 3
// Second copy of 0 1 2 3 -> 2 1 0 3
// Third copy of 0 1 2 3 -> 3 1 2 0
//
// So, after the first iteration,
// First permutation - 0 1 2 3
// Second permutation - 1 0 2 3
// Third permutation - 2 1 0 3
// Fourth permutation - 3 1 2 0
//
//
// In the second iteration, make (n-2) copies of all existing permutations, and
// swap a[1] with a[2] in the first copy, a[1] with a[3] in the second copy, and
// so on -
//
// First copy of 0 1 2 3 -> 0 2 1 3
// Second copy of 0 1 2 3 -> 0 3 2 1
//
// First copy of 1 0 2 3 -> 1 2 0 3
// Second copy of 1 0 2 3 -> 1 3 2 0
//
// First copy of 2 1 0 3 -> 2 0 1 3
// Second copy of 2 1 0 3 -> 2 3 0 1
//
// First copy of 3 1 2 0 -> 3 2 1 0
// Second copy of 3 1 2 0 -> 3 0 2 1
//
// So, after the second iteration,
// First permutation - 0 1 2 3
// Second permutation - 1 0 2 3
// Third permutation - 2 1 0 3
// Fourth permutation - 3 1 2 0
// Fifth permutation - 0 2 1 3
// Sixth permutation - 0 3 2 1
// Seventh permutation - 1 2 0 3
// Eighth permutation - 1 3 2 0
// Ninth permutation - 2 0 1 3
// Tenth permutation - 2 3 0 1
// Eleventh permutation - 3 2 1 0
// Twelfth permutation - 3 0 2 1
//
//
// In the third iteration, make (n-3) copies of all existing permutations, and
// swap a[2] with a[3] in the first copy, a[2] with a[4] in the second copy, and
// so on.
//
//
// Continue this process until the number of copies to be made becomes zero.





#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define ARR_MIN 0
#define ARR_MAX 9


int rand_int(int, int);
size_t factorial(size_t);
void permute(int*, size_t, int**);
void generate_permutations(size_t, int**, size_t*, size_t);


int main(void)
{

    srand((unsigned) time(NULL));


    size_t arr_size = 4;


    int* arr = malloc(arr_size * sizeof (int));

    if (arr == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        return EXIT_FAILURE;
    }


    for (size_t i = 0; i < arr_size; i++)
        // arr[i] = rand_int(ARR_MIN, ARR_MAX);
        arr[i] = i;


    size_t number_of_permutations = factorial(arr_size);


    int** permutations = malloc(number_of_permutations * sizeof (int*));

    if (permutations == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        return EXIT_FAILURE;
    }


    for (size_t i = 0; i < number_of_permutations; i++)
    {
        permutations[i] = malloc(arr_size * sizeof (int));

        if (permutations[i] == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            return EXIT_FAILURE;
        }
    }


    permute(arr, arr_size, permutations);


    for (size_t i = 0; i < number_of_permutations; i++)
    {
        for (size_t j = 0; j < arr_size; j++)
        {
            printf("%d ", permutations[i][j]);
        }

        putchar('\n');
    }


    free(arr);

    for (size_t i = 0; i < number_of_permutations; i++)
        free(permutations[i]);

    free(permutations);


    return 0;

}


int rand_int(int a, int b)
{

    size_t n = ((size_t) b - (size_t) a + (size_t) 1);
    size_t rem = (((size_t) RAND_MAX + (size_t) 1) % n);

    size_t x;
    do
    {
        x = (size_t) rand();
    }
    while (x >= (((size_t) RAND_MAX + (size_t) 1) - rem));

    return (int) ((size_t) a + (x % n));

}


size_t factorial(size_t n)
{

    size_t factorial_of_n = 1;

    for (size_t i = n; i > 1; i--)
        factorial_of_n *= i;

    return factorial_of_n;

}


void permute(int* arr, size_t arr_size, int** permutations)
{

    // cnp == current number of permutations;
    size_t cnp = 0;

    for (size_t i = 0; i < arr_size; i++)
        permutations[cnp][i] = arr[i];

    (cnp)++;

    generate_permutations(arr_size, permutations, &(cnp), (arr_size - 1));

}


void generate_permutations(size_t arr_size, int** permutations, size_t* ptr_cnp,
                           size_t number_of_copies_to_be_made)
{

    if (number_of_copies_to_be_made)
    {
        // pnp == previous number of permutations.
        size_t pnp = (*ptr_cnp);

        for (size_t i = 0; i < pnp; i++)
        {
            for (size_t j = 0; j < number_of_copies_to_be_made; j++)
            {
                for (size_t k = 0; k < arr_size; k++)
                    permutations[*ptr_cnp][k] = permutations[i][k];

                size_t x = (arr_size - number_of_copies_to_be_made - 1);
                size_t y = (x + j + 1);

                int temp = permutations[*ptr_cnp][x];
                permutations[*ptr_cnp][x] = permutations[*ptr_cnp][y];
                permutations[*ptr_cnp][y] = temp;

                (*ptr_cnp)++;
            }
        }

        generate_permutations(arr_size, permutations, ptr_cnp,
                              (number_of_copies_to_be_made - 1));
    }

}
