// The array must contain unique elements.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int ** subsets(int *, int, int *, int **);


int main(void)
{

    int arr[] = {1,2,3,4,5};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int numberOfSubsets;
    int * sizesOfSubsets;

    int ** subs = subsets(arr, arrSize, &numberOfSubsets,
                          &sizesOfSubsets);

    for (int i = 0; i < numberOfSubsets; i++)
    {
        if (sizesOfSubsets[i] == 0)
            printf("[]\n");

        else
        {
            printf("[");
            for (int j = 0; j < sizesOfSubsets[i]; j++)
                printf("%d,", subs[i][j]);
            printf("\b]\n");
        }
    }

    free(sizesOfSubsets);
    for (int i = 0; i < numberOfSubsets; i++)
        free(subs[i]);
    free(subs);

    return 0;

}


int ** subsets(int * arr, int arrSize,
               int * ptr_numberOfSubsets,
               int ** ptr_sizesOfSubsets)
{

    *ptr_numberOfSubsets = (1 << arrSize);
    // Same as *ptr_numberOfSubsets = pow(2, arrSize);

    *ptr_sizesOfSubsets = (int *)
        malloc(*ptr_numberOfSubsets*sizeof(int));
    if (*ptr_sizesOfSubsets == NULL)
        exit(EXIT_FAILURE);

    (*ptr_sizesOfSubsets)[0] = 0; // First subset is phi.

    int ** subs = (int **)
        malloc(*ptr_numberOfSubsets*sizeof(int *));
    if (subs == NULL)
        exit(EXIT_FAILURE);

    subs[0] = NULL; // First subset is phi.
    // malloc(0); is implementation-defined.

    for (int i = 0, k = 1; i < arrSize; i++)
        for (int j = 0; j < (1 << i); j++, k++)
        {
            (*ptr_sizesOfSubsets)[k] =
                (*ptr_sizesOfSubsets)[j] + 1;

            subs[k] = (int *)
                malloc((*ptr_sizesOfSubsets)[k]*sizeof(int));
            if (subs[k] == NULL)
                exit(EXIT_FAILURE);

            if (j > 0)
                memcpy(subs[k], subs[j],
                       (*ptr_sizesOfSubsets)[j]*sizeof(int));

            subs[k][(*ptr_sizesOfSubsets)[k] - 1] = arr[i];
        }

    return subs;

}





/*

 * Algorithm :-

   1. Start with phi as the first subset.
   2. For every new element in the array, append it to every
      existing subset.

*/
