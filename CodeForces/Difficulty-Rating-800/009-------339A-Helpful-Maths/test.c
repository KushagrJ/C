#include <stdio.h>
#include <stdlib.h>


int compare(const void*, const void*);


int main(void)
{

    int c;
    int arr[50];

    int i = 0;

    while (1)
    {
        c = getchar();

        if ((c == '1') || (c == '2') || (c == '3'))
        {
            arr[i] = c - '0';
            i++;
        }

        else if ((c == '\n') || (c == EOF))
        {
            break;
        }
    }

    qsort(arr, i, sizeof (int), compare);

    printf("%d", arr[0]);
    for (int x = 1; x < i; x++)
        printf("+%d", arr[x]);
    printf("\n");

    return 0;

}


int compare(const void* a, const void* b)
{

    return *((const int*) a) - *((const int*) b);

}
