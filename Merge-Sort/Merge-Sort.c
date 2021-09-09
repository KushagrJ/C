// Study another implementation of Merge Sort where the left
// & right arays are created inside the merge() function, and
// the merging process gets done using a single loop, by
// setting the extra last elements of left & right to INT_MAX

#include <stdio.h>
#include <stdlib.h>


// Stable sort.
void merge_sort(int *, unsigned);
void merge(int *, int *, int *, unsigned, unsigned);


int main(void)
{

    unsigned size;
    printf("Enter the no. of integers to be sorted: ");
    scanf("%u", &size);

    int * arr = (int *) malloc(size*sizeof(int));
    if (arr == NULL)
        exit(EXIT_FAILURE);
    printf("Enter %u integers: ", size);
    for (unsigned i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    merge_sort(arr, size);

    printf("\nSorted array: ");
    for (unsigned i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);

    return EXIT_SUCCESS;

}


void merge_sort(int * arr, unsigned size)
{

    if (size > 1)
    {
        unsigned leftSize = size / 2;
        int * left = (int *) malloc(leftSize*sizeof(int));
        if (left == NULL)
            exit(EXIT_FAILURE);
        for (unsigned i = 0; i < leftSize; i++)
            left[i] = arr[i];

        unsigned rightSize = size - leftSize;
        int * right = (int *) malloc(rightSize*sizeof(int));
        if (right == NULL)
            exit(EXIT_FAILURE);
        for (unsigned i = 0; i < rightSize; i++)
            right[i] = arr[i + leftSize];

        merge_sort(left, leftSize);
        merge_sort(right, rightSize);
        merge(arr, left, right, leftSize, rightSize);

        free(left);
        free(right);
    }

}


void merge(int * arr, int * left, int * right,
           unsigned leftSize, unsigned rightSize)
{

    unsigned i = 0, j = 0, k = 0;

    while ((i < leftSize) && (j < rightSize))
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < leftSize)
        arr[k++] = left[i++];

    while (j < rightSize)
        arr[k++] = right[j++];

}





/* Alternative :-

#include <stdio.h>
#include <stdlib.h>


// Stable sort.
void merge_sort(int *, unsigned);
void merge(int *, int *, int *, unsigned, unsigned);


int main(void)
{

    unsigned size;
    printf("Enter the no. of integers to be sorted: ");
    scanf("%u", &size);

    int * arr = (int *) malloc(size*sizeof(int));
    if (arr == NULL)
        exit(EXIT_FAILURE);
    printf("Enter %u integers: ", size);
    for (unsigned i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    merge_sort(arr, size);

    printf("\nSorted array: ");
    for (unsigned i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);

    return EXIT_SUCCESS;

}


void merge_sort(int * arr, unsigned size)
{

    if (size > 1)
    {
        unsigned leftSize = size / 2;
        int * left = (int *) malloc(size*sizeof(int));
        if (left == NULL)
            exit(EXIT_FAILURE);
        for (unsigned i = 0; i < size; i++)
            left[i] = arr[i];

        unsigned rightSize = size - leftSize;
        int * right = left + leftSize;

        merge_sort(left, leftSize);
        merge_sort(right, rightSize);
        merge(arr, left, right, leftSize, rightSize);

        free(left);
    }

}


void merge(int * arr, int * left, int * right,
           unsigned leftSize, unsigned rightSize)
{

    unsigned i = 0, j = 0, k = 0;

    while ((i < leftSize) && (j < rightSize))
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < leftSize)
        arr[k++] = left[i++];

    while (j < rightSize)
        arr[k++] = right[j++];

}

*/
