int get_value_of_k(int* c, int upper_index, int x)
{

    int lower_index = 0;

    while (lower_index <= upper_index)
    {
        int middle_index = (lower_index + ((upper_index - lower_index) / 2));

        if ((c[middle_index] < x) &&
               ((middle_index == upper_index) || (c[middle_index + 1] >= x)))
        {
            return middle_index;
        }

        else if ((c[middle_index] < x) && (c[middle_index + 1] < x))
        {
            lower_index = (middle_index + 1);
        }

        else
        {
            upper_index = (middle_index - 1);
        }
    }

    // This function will never return -1, as c[0] == INT_MIN.
    return -1;

}


int lengthOfLIS(int* nums, int nums_size)
{

    int* c = malloc((nums_size + 1) * sizeof (int));
    if (c == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    c[0] = INT_MIN;
    int length_of_current_LIS = 0;

    for (int i = 0; i < nums_size; i++)
    {
        int x = nums[i];

        int k = get_value_of_k(c, length_of_current_LIS, x);
        c[k + 1] = x;

        if (k == length_of_current_LIS)
            (length_of_current_LIS)++;
    }

    free(c);

    return length_of_current_LIS;

}
