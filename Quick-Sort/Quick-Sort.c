// To understand the recursion, first assume that arr is a very large array.
// Now, prove that the quick_sort() function sorts any random 1-element subset
// of arr. Then, prove that it sorts any random 2-element subset of arr.
// Continuing in this manner, you will notice that it sorts any random n-element
// subset of arr.
// For eg., when proving that the function sorts any random 5-element subset of
// arr, you don't have to prove that it sorts the two smaller subsets obtained
// after the pivot has been sorted, as you have already proved that it sorts any
// random subset of arr with less than 5 elements.

// This implementation uses Hoare's partitioning scheme as given in CLRS.
// Study Lomuto's partitioning scheme as well.

// The recursion stops for either a 1-element array or a 0-element array.
// For a 0-element array, the upperIndex will be less than the lowerIndex.
// When the lowerIndex happens to be 0, then the upperIndex will be -1.
// This is why int indices are used in this program, instead of unsigned ones.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


// Unstable sort.
void quick_sort(int*, int, int);
int partition(int*, int, int);
int rand_int(int, int);


int main(void)
{

    srand((unsigned) time(NULL));

    int size = 100000;

    int* arr = malloc(size * sizeof (int));
    if (arr == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
        arr[i] = rand();

    quick_sort(arr, 0, size - 1);

    bool sorting_is_successful = true;

    for (int i = 0; i < (size - 1); i++)
    {
        if (arr[i] > arr[i + 1])
        {
            sorting_is_successful = false;
            break;
        }
    }

    if (sorting_is_successful)
        printf("Congratulations\n");
    else
        printf("Try again\n");

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


// In this partitioning scheme, the pivot doesn't reach its final position after
// partitioning, as opposed to in Lomuto's scheme.
// Instead, the subarray gets partitioned with respect to the pivot and the
// pivot gets shifted to either of the two partitions.
// Thus, the call to quick_sort() is quick_sort(arr, l_i, p_i), instead of
// quick_sort(arr, l_i, (p_i - 1)).

// Also, in Lomuto's scheme, when pivot_index is generated randomly, then
// arr[pivot_index] is swapped with either arr[lower_index] or arr[upper_index],
// depending upon the implementation, as Lomuto's scheme doesn't work on random
// pivots.
// But, in Hoare's scheme, any random pivot can be chosen.

int partition(int* arr, int lower_index, int upper_index)
{

    int pivot = arr[rand_int(lower_index, upper_index)];

    int i = lower_index;
    int j = upper_index;

    while (1)
    {
        // or while ((i < upper_index) && (arr[i] <= pivot))
        while (arr[i] < pivot) // (i < upper_index) is not required. Why?
            i++;

        // or while ((j > lower_index) && (arr[j] >= pivot))
        while (arr[j] > pivot) // (j > lower_inded) is not required. Why?
            j--;

        if (i < j)
        {
            int temp = arr[i];
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
