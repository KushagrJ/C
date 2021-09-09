#include <stdio.h>


int main(void)
{

    int size;
    printf("Enter the number of integers: ");
    scanf("%d", &size);

    int arr[size];

    printf("Enter %d integers: \n", size);
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    // Bubble Sort
    int temp;
    for (int i = 1; i < size; i++)
        for (int j = 0; j < size-i; j++)
            if (arr[j] > arr[j+1])
                temp=arr[j], arr[j]=arr[j+1], arr[j+1]=temp;

    int currentInteger;
    int x = 0;

    while (x < size)
    {
        currentInteger = arr[x];
        printf("No. of times %d occurs = ", currentInteger);
        int count = 0;
        while ((x < size) && (arr[x] == currentInteger))
            x++, count++;
        printf("%d\n", count);
    }

    return 0;

}
