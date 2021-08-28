#include <stdio.h>
#include <stdlib.h>


// Stable sort.
void insertion_sort(int *, unsigned);


int main(void)
{

    unsigned size;
    printf("Enter the no. of integers to be sorted: ");
    scanf("%u", &size);

    int * arr = (int *) malloc(size * sizeof(int));
    if (arr == NULL)
        exit(EXIT_FAILURE);
    printf("Enter %u integers: ", size);
    for (unsigned i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    insertion_sort(arr, size);

    printf("\nSorted array: ");
    for (unsigned i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);

    return EXIT_SUCCESS;

}


void insertion_sort(int * arr, unsigned size)
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
