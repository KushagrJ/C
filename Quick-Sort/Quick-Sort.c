// To understand the recursion, first assume that arr is a very large array.
// Now, prove that the quick_sort() function sorts any random 1-element subset
// of arr. Then, prove that it sorts any random 2-element subset of arr.
// Continuing in this manner, you will notice that it sorts any random n-element
// subset of arr.
// For eg., when proving that the function sorts any random 5-element subset of
// arr, you don't have to prove that it sorts the two smaller subsets obtained
// after the pivot has been sorted, as you have already proved that it sorts any
// random subset of arr with less than 5 elements.

// The recursion stops for either a 1-element array or a 0-element array.
// For a 0-element array, upper_index will be less than lower_index.
// When lower_index happens to be 0, then upper_index will be -1.
// This is why signed indices are used in this program, instead of unsigned ones.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define SIZE 100


int rand_int(int, int);

// Unstable sort.
void quick_sort(int*, int, int);
int partition(int*, int, int);


int main(void)
{

    srand((unsigned) time(NULL));

    int* arr = malloc(SIZE * sizeof (int));
    if (arr == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < SIZE; i++)
        arr[i] = rand_int(-100, 100);

    quick_sort(arr, 0, (SIZE - 1));

    bool sorting_is_successful = true;

    for (int i = 0; i < (SIZE - 1); i++)
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


void quick_sort(int* arr, int lower_index, int upper_index)
{

    if (lower_index < upper_index)
    {
        int partitioning_index = partition(arr, lower_index, upper_index);

        quick_sort(arr, lower_index, partitioning_index);
        quick_sort(arr, (partitioning_index + 1), upper_index);
    }

}


// Study Lomuto's partitioning scheme as well.

// In this partitioning scheme (Hoare's), the pivot doesn't reach its final
// position after partitioning, as opposed to in Lomuto's scheme.
// Instead, the subarray gets partitioned with respect to the pivot and the
// pivot gets shifted to either of the two partitions.
// Thus, the first inner call to quick_sort() is
// quick_sort(arr, lower_index, partitioning_index), instead of
// quick_sort(arr, lower_index, (partitioning_index - 1)).

// Choosing arr[upper_index] as the pivot doesn't work. Why?
// Thus, arr[lower_index] or arr[lower_index + (upper_index - lower_index) / 2]
// should be chosen as the pivot.

// while (arr[i] < pivot) and while (arr[j] > pivot) don't work. Why?
// [Note that (i < upper_index) and (j > lower_index) don't need to be checked
//  when while (arr[i] < pivot) and while (arr[j] > pivot) are used, as these
//  automatically ensure that i and j don't run out of bounds]

// Hence, while ((i < upper_index) && (arr[i] <= pivot)) and
// while ((j > lower_index) && (arr[j] >= pivot)) need to be used.

int partition(int* arr, int lower_index, int upper_index)
{

    int pivot_index = rand_int(lower_index, upper_index);

    int temp = arr[lower_index];
    arr[lower_index] = arr[pivot_index];
    arr[pivot_index] = temp;

    int pivot = arr[lower_index];

    int i = lower_index;
    int j = upper_index;

    while (1)
    {
        while ((i < upper_index) && (arr[i] <= pivot))
            i++;

        while ((j > lower_index) && (arr[j] >= pivot))
            j--;

        if (i < j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

        else
        {
            return j;
        }
    }

}


int rand_int(int a, int b)
{

    int n = (b - a + 1);
    int rem = (RAND_MAX % n);

    int x = rand();
    while (x >= (RAND_MAX - rem))
        x = rand();

    return (a + (x % n));

}
