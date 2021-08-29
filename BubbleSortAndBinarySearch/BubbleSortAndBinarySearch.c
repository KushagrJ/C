#include <stdio.h>


// Stable sort.
void bubble_sort(int *, unsigned);
int binary_search(int *, unsigned, int);


int main(void)
{

    unsigned size;
    printf("Enter the number of integers: ");
    scanf("%u", &size);

    int arr[size];

    printf("Enter %u integers: ", size);
    for (unsigned i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    bubble_sort(arr, size);

    printf("After sorting: ");
    for (unsigned i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n\n");

    int target;
    printf("Enter the integer to be searched: ");
    scanf("%d", &target);

    int indexOfTarget = binary_search(arr, size, target);

    if (indexOfTarget == -1)
        printf("Integer not found!\n");
    else
        printf("Integer found at position no. %d "
               "in the sorted list\n", indexOfTarget + 1);

    return 0;

}


void bubble_sort(int * arr, unsigned size)
{
    int temp;
    for (unsigned i = 1; i < size; i++)
        for (unsigned j = 0; j < size-i; j++)
            if (arr[j] > arr[j+1])
                temp=arr[j], arr[j]=arr[j+1], arr[j+1]=temp;
}


int binary_search(int * arr, unsigned size, int target)
{

    unsigned lowerIndex = 0;
    unsigned middleIndex;
    unsigned upperIndex = size-1;

    while (lowerIndex <= upperIndex)
    {
        middleIndex = (lowerIndex + upperIndex) / 2;

        if (target == arr[middleIndex])
            return middleIndex;

        else if (target > arr[middleIndex])
            lowerIndex = middleIndex + 1;

        else
            upperIndex = middleIndex - 1;
    }

    return -1;

}
