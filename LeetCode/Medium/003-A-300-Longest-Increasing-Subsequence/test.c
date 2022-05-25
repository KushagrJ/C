int lengthOfLIS(int* nums, int nums_size)
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

        for (int j = 0; j < i; j++)
        {
            if ((nums[i] > nums[j]) && (ans[i] <= ans[j]))
                ans[i] = (ans[j] + 1);
        }

        if (max_length < ans[i])
            max_length = (ans[i]);
    }

    free(ans);

    return max_length;

}
