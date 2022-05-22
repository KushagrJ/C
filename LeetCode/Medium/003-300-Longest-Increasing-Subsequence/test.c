// This is a proper example of dynamic programming.

// ans[i] is the length of a longest increasing subsequence in the range
// 0-th integer to i-th integer, under the constraint that nums[i] is the last
// element of that subsequence.

int length_of_longest_increasing_subsequence(int* nums, int nums_size)
{

    int* ans = malloc(nums_size * sizeof (int));
    if (ans == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    ans[0] = 1;
    int max_length = 1;

    for (int i = 1; i < nums_size; i++)
    {
        ans[i] = 1;

        for (int j = (i - 1); j >= 0; j--)
        {
            if ((nums[i] > nums[j]) && (ans[i] < (ans[j] + 1)))
                ans[i] = (ans[j] + 1);
        }

        if (max_length < ans[i])
            max_length = (ans[i]);
    }

    free(ans);

    return max_length;

}
