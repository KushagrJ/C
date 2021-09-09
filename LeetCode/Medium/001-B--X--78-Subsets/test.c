// The array must contain unique elements.

// The number of arguments to generateSubsets() can be
// reduced by declaring arr, arrSize, numberOfSubsets,
// sizesOfSubsets, subs and currentSubsetIndex as global.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int ** subsets(int *, int, int *, int **);
void generate_subsets(int *, int, int **, int **, int *,
                      int *, int, int);


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

    *ptr_sizesOfSubsets = (int *)
        malloc(*ptr_numberOfSubsets * sizeof(int));
    if (*ptr_sizesOfSubsets == NULL)
        exit(EXIT_FAILURE);

    int ** subs = (int **)
        malloc(*ptr_numberOfSubsets * sizeof(int *));
    if (subs == NULL)
        exit(EXIT_FAILURE);

    int currentSubsetIndex = 0;

    generate_subsets(arr, arrSize, ptr_sizesOfSubsets,
                     subs, &currentSubsetIndex,
                     NULL, 0, 0);

    return subs;

}


void generate_subsets(int * arr, int arrSize,
                      int ** ptr_sizesOfSubsets, int ** subs,
                      int * ptr_currentSubsetIndex,
                      int * currentSubset,
                     int currentSubsetSize, int arrIndex)
{

    if (arrIndex == arrSize)
    {
        if (currentSubsetSize)
        {
            subs[*ptr_currentSubsetIndex] = (int *)
                malloc(currentSubsetSize * sizeof(int));
            if (subs[*ptr_currentSubsetIndex] == NULL)
                exit(EXIT_FAILURE);

            memcpy(subs[*ptr_currentSubsetIndex],
                   currentSubset,
                   currentSubsetSize * sizeof(int));
        }

        else
            subs[*ptr_currentSubsetIndex] = NULL;

        (*ptr_sizesOfSubsets)[*ptr_currentSubsetIndex] =
            currentSubsetSize;

        (*ptr_currentSubsetIndex)++;
    }

    else
    {
        // Case 1: Excluding arr[arrIndex]

        generate_subsets(arr, arrSize, ptr_sizesOfSubsets,
                        subs, ptr_currentSubsetIndex,
                        currentSubset, currentSubsetSize,
                        arrIndex + 1);


        // Case 2: Including arr[arrIndex]

        int newSubsetSize = currentSubsetSize + 1;

        // Checking for newSubsetSize > 0 is redundant, since
        // newSubsetSize will always be greater than zero.
        int * newSubset = (int *)
            malloc(newSubsetSize * sizeof(int));
        if (newSubset == NULL)
            exit(EXIT_FAILURE);

        if (currentSubsetSize)
            memcpy(newSubset, currentSubset,
                   currentSubsetSize * sizeof(int));

        newSubset[newSubsetSize - 1] = arr[arrIndex];

        generate_subsets(arr, arrSize, ptr_sizesOfSubsets,
                        subs, ptr_currentSubsetIndex,
                        newSubset, newSubsetSize,
                        arrIndex + 1);

        free(newSubset);
    }

}





/*

 * Algorithm :-

   For every new element in the array, there are 2 choices -
   either include it in the subset, or exclude it.

   [The recursion terminates when there are no more elements
    available in the array to include/exclude]

*/





/*

arr - [1,2]

aS - arrSize = 2
aI - arrIndex

cS - currentSubset
cSS - currentSubsetSize

nS - newSubset
nSS - newSubsetSize

gS() - generateSubsets()



gS()--------> cS - []
              cSS = 0
              aI = 0

              aI != aS

              gS()--------> cS - []
                            cSS = 0
                            aI = 1

                            aI != aS

                            gS()--------> cS - []
                                          cSS = 0
                                          aI = 2

                                          aI == aS

                                          subs[0] - []

                            nS - [2]
                            nSS = 1

                            gS()--------> cS - [2]
                                          cSS = 1
                                          aI = 2

                                          aI == aS

                                          subs[1] - [2]

                            free(nS)

              nS - [1]
              nSS - 1

              gS()--------> cS - [1]
                            cSS = 1
                            aI = 1

                            aI != aS

                            gS()--------> cS - [1]
                                          cSS = 1
                                          aI = 2

                                          aI == aS

                                          subs[2] - [1]

                            nS - [1,2]
                            nSS = 2

                            gS()--------> cS - [1,2]
                                          cSS = 2
                                          aI = 2

                                          aI == aS

                                          subs[3] - [1,2]

                            free(nS)

              free(nS)



subs - [ [],
         [2],
         [1],
         [1,2] ]

*/
