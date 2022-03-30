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


#define ARR_SIZE 100
#define ARR_MIN -10
#define ARR_MAX 10


int rand_int(int, int);

// Unstable sort.
void quick_sort(int*, int, int);
int partition(int*, int, int);


int main(void)
{

    srand((unsigned) time(NULL));

    int* arr = malloc(ARR_SIZE * sizeof (int));
    if (arr == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ARR_SIZE; i++)
        arr[i] = rand_int(ARR_MIN, ARR_MAX);

    quick_sort(arr, 0, (ARR_SIZE - 1));

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

    // n, i.e. the no. of integers in the range, must be <= RAND_MAX.
    int n = (b - a + 1);
    int rem = (RAND_MAX % n);

    int x = rand();
    while (x >= (RAND_MAX - rem))
        x = rand();

    return (a + (x % n));

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


int partition(int* arr, int lower_index, int upper_index)
{

    int pivot = arr[rand_int(lower_index, upper_index)];

    int i = (lower_index );
    int j = (upper_index );

    while (true)
    {
        //do
            //i++;
        while ((i < upper_index) && (arr[i] <= pivot))
            i++;

        //do
            //j--;
        while ((j > lower_index) && (arr[j] >= pivot))
            j--;

        if (i >= j)
            return j;

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

}





// Three widely used schemes of partitioning are -
// (1) Hoare's partitioning scheme 1 (given in CLRS)
// (2) Hoare's partitioning scheme 2
// (3) Lomuto's partitioning

// This program uses Hoare's partitioning scheme 1.
// In this partitioning scheme, the pivot doesn't reach its final position after
// partitioning, as opposed to in 'Hoare's partitioning scheme 2' and 'Lomuto's
// partitioning scheme'.
// Instead, the subarray gets partitioned with respect to the pivot and the
// pivot gets shifted to either of the two partitions, and hence, the final
// position of the pivot can't be predicted.
// Thus, the first inner call to quick_sort() is
// quick_sort(arr, lower_index, partitioning_index), instead of
// quick_sort(arr, lower_index, (partitioning_index - 1)).

// In 'Hoare's partitioning scheme 2' and 'Lomuto's partitioning scheme', a
// randomly chosen pivot can't be used directly and needs to be first swapped
// with arr[lower_index] or arr[upper_index], depending upon the implementation.
// In Hoare's partitioning scheme 1, however, any randomly chosen pivot can be
// used directly.

// At first glance, it may seem that
//
//  ...
//  int i = (lower_index - 1);
//  int j = (upper_index + 1);
//
//  while (true)
//  {
//      do
//          i++;
//      while (arr[i] < pivot);
//
//      do
//          j--;
//      while (arr[j] > pivot);
//  ...
//
// can be simply replaced by
//
//  ...
//  int i = lower_index;
//  int j = upper_index;
//
//  while (true)
//  {
//      while (arr[i] < pivot);
//          i++;
//
//      while (arr[j] > pivot);
//          j--;
//  ...
//
// but, this is not the case.
//
// This is because the 'do-while' version causes i/j to advance to the
// next/previous element in the subarray in every iteration of the outer
// 'while(true)' loop before the condition checking is done, whereas the 'while'
// version causes i/j to remain at its previous position when the condition
// checking is done.
//
// The 'while' version causes an infinite loop in many test cases.
// For eg., arr[] = {0, 3, -1, 0, 2}, with arr[0] as the pivot.

// In Hoare's partitioning scheme 1, while (arr[i] < pivot) and
// while (arr[j] > pivot) automatically ensure that i and j don't run out of
// bounds.
// Thus, extra conditions for bound-checking aren't required.

// Other kinds of conditions, such as while (arr[i] <= pivot) and
// while (arr[j] >= pivot), even with additional bound-checking, don't work with
// Hoare's partitioning scheme 1.
// If these would have worked, then these would've made the partitioning
// procedure faster, as in the case of while (arr[i] <= pivot) and
// while (arr[j] >= pivot), i and j approach each other more quickly.

// After studying all 3 partitioning schemes, post all 3 codes together on
// Code Review Stack Exchange, including trivia.
