#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int qsort_compare(const void*, const void*);

int binary_search(int*, size_t, int);


int main(void)
{

    size_t size;
    printf("Enter the number of integers: ");
    scanf("%zu", &(size));

    int arr[size];

    printf("Enter %zu integers: ", size);
    for (size_t i = 0; i < size; i++)
        scanf("%d", &(arr[i]));

    qsort(arr, size, sizeof (int), qsort_compare);

    printf("After sorting: ");
    for (size_t i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n\n");

    int target;
    printf("Enter the integer to be searched: ");
    scanf("%d", &target);

    int index_of_target = binary_search(arr, size, target);

    if (index_of_target == -1)
    {
        printf("Integer not found!\n");
    }

    else
    {
        printf("Integer found at position no. %d in the sorted list\n",
               (index_of_target + 1));
    }

    return 0;

}


int qsort_compare(const void* a, const void* b)
{

    int x = *((const int*) a);
    int y = *((const int*) b);

    if (x > y)
        return 1;
    else if (x == y)
        return 0;
    else
        return -1;

}


int binary_search(int* arr, size_t size, int target)
{

    size_t lower_index = 0;
    size_t upper_index = (size - 1);

    while (lower_index <= upper_index)
    {
        // ((lower_index + upper_index) / 2) may cause overflow.
        size_t middle_index = (lower_index + (upper_index - lower_index) / 2);

        if (target == arr[middle_index])
            return middle_index;

        else if (target > arr[middle_index])
            lower_index = (middle_index + 1);

        else
            upper_index = (middle_index - 1);
    }

    return -1;

}
