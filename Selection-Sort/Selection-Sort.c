#include <stdio.h>
#include <stdlib.h>


// Unstable sort.
void selection_sort(int *, unsigned);


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

    selection_sort(arr, size);

    printf("\nSorted array: ");
    for (unsigned i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);

    return EXIT_SUCCESS;

}


void selection_sort(int * arr, unsigned size)
{

    int temp;
    unsigned min;

    for (unsigned i = 0; i < size; i++)
    {
        min = i;

        for (unsigned j = i+1; j < size; j++)
            if (arr[j] < arr[min])
                min = j;

        if (min != i)
            temp=arr[i], arr[i]=arr[min], arr[min]=temp;
    }

}
