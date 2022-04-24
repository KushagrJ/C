#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define ARR_SIZE 10000
#define ARR_MIN -10
#define ARR_MAX 10


int rand_int(int, int);

// Stable sort.
void bubble_sort(int*, size_t);


int main(void)
{

    srand((unsigned) time(NULL));

    int* arr = malloc(ARR_SIZE * sizeof (int));
    if (arr == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < ARR_SIZE; i++)
        arr[i] = rand_int(ARR_MIN, ARR_MAX);

    bubble_sort(arr, ARR_SIZE);

    bool sorting_is_successful = true;

    for (int i = 0; i < (ARR_SIZE - 1); i++)
    {
        if (arr[i] > arr[i + 1])
        {
            sorting_is_successful = false;
            break;
        }
    }

    if (sorting_is_successful)
        printf("Success\n");
    else
        printf("Failure\n");

    free(arr);

    return EXIT_SUCCESS;

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


void bubble_sort(int* arr, size_t size)
{

    int temp;

    bool array_is_already_sorted = true;

    for (size_t i = 1; i < size; i++)
    {
        for (size_t j = 0; j < size - i; j++)
        {
            if (arr[j] > arr[j+1])
            {
                array_is_already_sorted = false;
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }

        if (array_is_already_sorted)
            break;
    }

}
