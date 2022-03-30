#include <stdio.h>
#include <stdbool.h>


// Stable sort.
void bubble_sort(int*, size_t);

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

    bubble_sort(arr, size);

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


void bubble_sort(int* arr, size_t size)
{

    int temp;

    // To make the best case time complexity equal to O(n).
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
