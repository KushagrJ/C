// The return values of all mallocs should be checked.


// cnp == current no. of permutations.

void generate_permutations(int* arr, int lower_index, int nums_size,
                           int** permutations, int* ptr_cnp)
{

    if (lower_index == (nums_size - 1))
    {
        permutations[(*ptr_cnp)++] = arr;

        return;
    }

    generate_permutations(arr, (lower_index + 1), nums_size, permutations,
                          ptr_cnp);

    for (int i = (lower_index + 1); i < nums_size; i++)
    {
        // new_arr is a copy of arr.
        int* new_arr = malloc(nums_size * sizeof (int));
        memmove(new_arr, arr, (nums_size * sizeof (int)));

        int temp = new_arr[lower_index];
        new_arr[lower_index] = new_arr[i];
        new_arr[i] = temp;

        // To generate the permutations in lexicographic order :-
        // qsort((new_arr + (lower_index + 1)), (nums_size - (lower_index + 1)),
        //       sizeof (int), qsort_compare);

        generate_permutations(new_arr, (lower_index + 1), nums_size,
                              permutations, ptr_cnp);
    }

}


// nop == number of permutations.
// sop == sizes of permutations.

int** permute(int* nums, int nums_size, int* ptr_nop, int** ptr_sop)
{

    // nop == factorial of nums_size.
    *ptr_nop = 1;
    for (int i = 2; i <= nums_size; i++)
        *ptr_nop *= i;

    // Having to create a new array to store the sizes of the permutations is
    // redundant, as the size of every permutation is the same as the size of
    // the nums array.
    *ptr_sop = malloc(*ptr_nop * sizeof (int));
    for (int i = 0; i < *ptr_nop; i++)
        (*ptr_sop)[i] = nums_size;

    int** permutations = malloc(*ptr_nop * sizeof (int*));

    // arr is a copy of nums.
    int* arr = malloc(nums_size * sizeof (int));
    memmove(arr, nums, (nums_size * sizeof (int)));

    // To generate the permutations in lexicographic order :-
    // qsort(arr, arr_size, sizeof (int), qsort_compare);

    // cnp == current no. of permutations.
    int cnp = 0;

    generate_permutations(arr, 0, nums_size, permutations, &(cnp));

    return permutations;

}
