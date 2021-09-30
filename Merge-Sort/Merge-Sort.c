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





/* Algorithm :-

   // Argument 1: Array into which the two sorted arrays are
   //             to be merged, arr.
   // Argument 2: First sorted array, left.
   // Argument 3: Second sorted array, right.
   // Argument 4: Size of the first sorted array, leftSize.
   // Argument 5: Size of the second sorted array, rightSize.
   // Ensure that arrSize is equal to (leftSize + rightSize).

   merge() -

   1. Take 3 counters, i, j and k, for arr, left and right.
   2. Initialize i, j and k to 0.
   3. While (j is less than leftSize) and (k is less than
      rightSize)
          If (left[j] is less than or equal to right[k])
              Set arr[i] equal to left[j].
              Increment i by 1.
              Increment j by 1.
          Else
              Set arr[i] equal to right[k].
              Increment i by 1.
              Increment k by 1.
      While (j is less than leftSize)
          Set arr[i] equal to left[j].
          Increment i by 1.
          Increment j by 1.
      While (k is less than rightSize)
          Set arr[i] equal to right[k].
          Increment i by 1.
          Increment k by 1.



   // Argument 1: Array to be sorted, arr.
   // Argument 2: Size of the array, arrSize.

   merge_sort() -

   1. If (arrSize is equal to 1)
          Do nothing, as arr is already sorted.
      Else If (arrSize is greater than 1)
          Create two sub-arrays left and right such that
          leftSize is equal to (arrSize / 2) and rightSize is
          equal to (arrSize - leftSize).
          Sort left using merge_sort().
          Sort right using merge_sort().
          Merge left and right into arr using merge().



   main() -

   Sort any array using merge_sort().

*/
