#include <stdio.h>
#include <string.h>


int main(void)
{

    char arr[256];

    printf("Enter a string: ");
    fgets(arr, 256, stdin);
    int i = strlen(arr);

    for (int j = 0; j < i; j++)
        for (int k = j+1; k < i; k++)
            if (arr[j] == arr[k])
            {
                for (int l = k; l < i; l++)
                    arr[l] = arr[l+1];
                i--;
                k--;
            }

    printf("Duplicates removed: ");
    fputs(arr, stdout);

    return 0;

}
