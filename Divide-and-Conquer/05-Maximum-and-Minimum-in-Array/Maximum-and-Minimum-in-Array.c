#include <stdio.h>
#include <stdlib.h>


void find_max_and_min(int*, int, int*, int*);


int main(void)
{

    int arr_size;
    printf("Enter the no. of integers: ");
    scanf("%d", &(arr_size));

    int* arr = malloc(arr_size * sizeof (int));

    printf("Enter %d integers: ", arr_size);
    for (int i = 0; i < arr_size; i++)
        scanf("%d", &(arr[i]));

    int max, min;
    find_max_and_min(arr, arr_size, &(max), &(min));

    printf("Maximum integer: %d\n", max);
    printf("Minimum integer: %d\n", min);

    free(arr);

    return 0;

}


void find_max_and_min(int* arr, int arr_size, int* ptr_max, int* ptr_min)
{

    if (arr_size == 1)
    {
        *ptr_max = *ptr_min = arr[0];
        return;
    }

    int left_size = (arr_size / 2);
    int* left = arr;

    int left_max, left_min;
    find_max_and_min(left, left_size, &(left_max), &(left_min));

    int right_size = (arr_size - left_size);
    int* right = (arr + left_size);

    int right_max, right_min;
    find_max_and_min(right, right_size, &(right_max), &(right_min));

    if (left_max > right_max)
        *ptr_max = left_max;
    else
        *ptr_max = right_max;

    if (left_min < right_min)
        *ptr_min = left_min;
    else
        *ptr_min = right_min;

}
