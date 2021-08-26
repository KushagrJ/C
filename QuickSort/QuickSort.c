// This implementation uses Hoare's partitioning scheme.
// Study Lomuto's partitioning scheme as well.

// The recursion stops for either a 1-element array or a
// 0-element array.
// For a 0-element array, the upperIndex will be less than
// the lowerIndex.
// When the lowerIndex happens to be 0, then the upperIndex
// will be -1.
// This is why int indices are used in this program, instead
// of unsigned ones.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Unstable sort.
void quick_sort(int *, int, int);
int partition(int *, int, int);


int main(void)
{

    srand((unsigned) time(NULL));

    int size;
    printf("Enter the no. of integers to be sorted: ");
    scanf("%u", &size);

    int * arr = (int *) malloc(size * sizeof(int));
    if (arr == NULL)
        exit(EXIT_FAILURE);
    printf("Enter %u integers: ", size);
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    quick_sort(arr, 0, size - 1);

    printf("\nSorted array: ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);

    return EXIT_SUCCESS;

}


void quick_sort(int * arr, int lowerIndex, int upperIndex)
{

    if (lowerIndex < upperIndex)
    {
        int pivotIndexAfterSortingPivot =
            partition(arr, lowerIndex, upperIndex);

        quick_sort(arr, lowerIndex,
                   pivotIndexAfterSortingPivot - 1);

        quick_sort(arr, pivotIndexAfterSortingPivot + 1,
                   upperIndex);
    }

}


// Hoare's partitioning scheme fails for pivots other than
// arr[lowerIndex].
// The most apparent failure can be seen for an already
// sorted 2-element array with the pivot as arr[upperIndex].

int partition(int * arr, int lowerIndex, int upperIndex)
{

    int temp;

    // The chosen pivot is swapped with the first element, as
    // Hoare's scheme wouldn't work otherwise.
    // The function now works on arr[lowerIndex] instead of
    // arr[pivotIndex].

    int pivotIndex =
        lowerIndex + (rand() % (upperIndex-lowerIndex+1));

    temp = arr[lowerIndex];
    arr[lowerIndex] = arr[pivotIndex];
    arr[pivotIndex] = temp;

    // If i is initialized to lowerIndex+1, then a 2-element
    // array will not be sorted.
    int i = lowerIndex;
    int j = upperIndex;

    while (i < j)
    {
        // If the condition is arr[i] < arr[lowerIndex]
        // (instead of <=), then it will always fail, since
        // the pivot is arr[lowerIndex].

        while ((i < upperIndex) &&
               (arr[i] <= arr[lowerIndex]))
            i++;

        while ((j > lowerIndex) &&
               (arr[j] >= arr[lowerIndex]))
            j--;

        // Automatically means that i <= upperIndex and
        // j >= lowerIndex.
        if (i < j)
            temp = arr[i], arr[i] = arr[j], arr[j] = temp;
    }

    // At this point, lowerIndex <= j <= upperIndex is
    // ensured.
    temp = arr[lowerIndex];
    arr[lowerIndex] = arr[j];
    arr[j] = temp;

    return j;

}
