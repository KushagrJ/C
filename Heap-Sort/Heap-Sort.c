#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define ARR_SIZE 10000
#define ARR_MIN -10
#define ARR_MAX 10


int rand_int(int, int);

// Unstable sort.
void heap_sort(int*, size_t);
void build_max_heap(int*, size_t);
void max_heapify(int*, size_t, size_t);


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

    heap_sort(arr, ARR_SIZE);

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


void heap_sort(int* arr, size_t arr_size)
{

    size_t heap_size = arr_size;

    build_max_heap(arr, heap_size);

    for (int i = (arr_size - 1); i >= 1; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        (heap_size)--;

        max_heapify(arr, heap_size, 0);
    }

}


void build_max_heap(int* arr, size_t heap_size)
{

    for (int i = ((heap_size / 2) - 1); i >= 0; i--)
        max_heapify(arr, heap_size, i);

}


void max_heapify(int* arr, size_t heap_size, size_t index_of_parent)
{

    size_t index_of_left_child = ((2 * index_of_parent) + 1);
    size_t index_of_right_child = ((2 * index_of_parent) + 2);

    size_t index_of_largest = index_of_parent;

    if ((index_of_left_child < heap_size) &&
            (arr[index_of_left_child] > arr[index_of_largest]))
    {
        index_of_largest = index_of_left_child;
    }

    if ((index_of_right_child < heap_size) &&
            (arr[index_of_right_child] > arr[index_of_largest]))
    {
        index_of_largest = index_of_right_child;
    }

    if (index_of_largest != index_of_parent)
    {
        int temp = arr[index_of_largest];
        arr[index_of_largest] = arr[index_of_parent];
        arr[index_of_parent] = temp;

        max_heapify(arr, heap_size, index_of_largest);
    }

}





/*

 * Iterative Version :-


   Since max_heapify() uses tail recursion, therefore converting this to
   iteration is straightforward.


   void heap_sort(int* arr, size_t arr_size)
   {

       size_t heap_size = arr_size;

       build_max_heap(arr, heap_size);

       for (int i = (arr_size - 1); i >= 1; i--)
       {
           int temp = arr[0];
           arr[0] = arr[i];
           arr[i] = temp;

           (heap_size)--;

           sift_down(arr, heap_size, 0);
       }

   }


   void build_max_heap(int* arr, size_t heap_size)
   {

       for (int i = ((heap_size / 2) - 1); i >= 0; i--)
           sift_down(arr, heap_size, i);

   }


   void sift_down(int* arr, size_t heap_size, size_t index_of_parent)
   {

       while (1)
       {
           size_t index_of_left_child = ((2 * index_of_parent) + 1);
           size_t index_of_right_child = ((2 * index_of_parent) + 2);

           size_t index_of_largest = index_of_parent;

           if ((index_of_left_child < heap_size) &&
                   (arr[index_of_left_child] > arr[index_of_largest]))
           {
               index_of_largest = index_of_left_child;
           }

           if ((index_of_right_child < heap_size) &&
                   (arr[index_of_right_child] > arr[index_of_largest]))
           {
               index_of_largest = index_of_right_child;
           }

           if (index_of_largest == index_of_parent)
               break;

           int temp = arr[index_of_largest];
           arr[index_of_largest] = arr[index_of_parent];
           arr[index_of_parent] = temp;

           index_of_parent = index_of_largest;
       }

   }

*/
