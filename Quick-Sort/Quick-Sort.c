// To understand the recursion, first assume that arr is a very large array.
// Now, prove that the quick_sort() function sorts any random 1-element subset
// of arr. Then, prove that it sorts any random 2-element subset of arr.
// Continuing in this manner, you will notice that it sorts any random n-element
// subset of arr.
// For eg., when proving that the function sorts any random 5-element subset of
// arr, you don't have to prove that it sorts the two smaller subsets obtained
// after the pivot has been sorted, as you have already proved that it sorts any
// random subset of arr with less than 5 elements.

// This implementation uses Hoare's partitioning scheme.
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


int main(void)
{

    srand((unsigned) time(NULL));

/*
    int size;
    printf("Enter the no. of integers to be sorted: ");
    scanf("%d", &size);

    int* arr = malloc(size * sizeof (int));
    if (arr == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter %d integers: ", size);
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    quick_sort(arr, 0, size - 1);

    printf("\nSorted array: ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
*/

    int size = 10000;

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


void quick_sort(int* arr, int lowerIndex, int upperIndex)
{
    if (lowerIndex < upperIndex)
    {
        int pivotIndexAfterSortingPivot =
            partition(arr, lowerIndex, upperIndex);

        // quick_sort(arr, lowerIndex, pivotIndexAfterSortingPivot - 1);
        quick_sort(arr, lowerIndex, pivotIndexAfterSortingPivot);

        quick_sort(arr, pivotIndexAfterSortingPivot + 1, upperIndex);
    }
}


/*
// arr[upperIndex] should not be chosen as the pivot with Hoare's partitioning
// scheme, as this scheme fails for a 2-element array with arr[upperIndex] as
// the pivot.

int partition(int* arr, int lowerIndex, int upperIndex)
{
    int temp;

    int pivotIndex = lowerIndex + (rand() % (upperIndex-lowerIndex+1));

    // The randomly chosen pivot is swapped with the first element to ensure
    // that Hoare's scheme works, i.e. arr[lowerIndex] now becomes the pivot.
    temp=arr[lowerIndex], arr[lowerIndex]=arr[pivotIndex], arr[pivotIndex]=temp;

    // If i is initialized to lowerIndex+1, then a 2-element array will not be
    // sorted.
    int i = lowerIndex;
    int j = upperIndex;

    while (i < j)
    {
        // If the condition is arr[i] < arr[lowerIndex] (instead of <=), then it
        // will always fail, since arr[lowerIndex] acts as the pivot.

        while ((i < upperIndex) && (arr[i] <= arr[lowerIndex]))
            i++;

        while ((j > lowerIndex) && (arr[j] >= arr[lowerIndex]))
            j--;

        // At this point, it is ensured that i <= upperIndex and
        // j >= lowerIndex.
        if (i < j)
            temp = arr[i], arr[i] = arr[j], arr[j] = temp;
    }

    // At this point, it is ensured that lowerIndex <= j <= upperIndex.
    temp = arr[lowerIndex], arr[lowerIndex] = arr[j], arr[j] = temp;

    return j;
}
*/


// This is another variation of Hoare's partitioning scheme in which the pivot
// doesn't reach its final position after partitioning.
// Instead, the subarray gets partitioned with respect to the pivot and the
// pivot gets shifted to either of the two partitions.
// Thus, the call to quick_sort() is quick_sort(arr, l, p), instead of
// quick_sort(arr, l, p - 1).

int partition(int* arr, int lower_index, int upper_index)
{
    int temp;

    int pivot_index = lower_index + (rand() % (upper_index - lower_index + 1));

    temp = arr[lower_index];
    arr[lower_index] = arr[pivot_index];
    arr[pivot_index] = temp;

    int pivot = arr[lower_index];

    int i = lower_index;
    int j = upper_index;

    while (1)
    {
        while ((i < upper_index) && (arr[i] < pivot))
            i++;

        while ((j > lower_index) && (arr[j] > pivot))
            j--;

        if (i < j)
            temp = arr[i], arr[i] = arr[j], arr[j] = temp;
        else
            return j;
    }
}
