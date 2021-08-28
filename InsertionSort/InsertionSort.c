// int indices need to be used, instead of unsigned ones.

#include <stdio.h>
#include <stdlib.h>


// Stable sort.
void insertion_sort(int *, int);


int main(void)
{

    int size;
    printf("Enter the no. of integers to be sorted: ");
    scanf("%d", &size);

    int * arr = (int *) malloc(size * sizeof(int));
    if (arr == NULL)
        exit(EXIT_FAILURE);
    printf("Enter %d integers: ", size);
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    insertion_sort(arr, size);

    printf("\nSorted array: ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);

    return EXIT_SUCCESS;

}


void insertion_sort(int * arr, int size)
{

    int temp;
    int j;

    for (int i = 1; i < size; i++)
    {
        temp = arr[i];
        for (j = i-1; (j >= 0) && (temp < arr[j]); j--)
            arr[j+1] = arr[j];
        arr[j+1] = temp;
    }

}
