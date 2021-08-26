// To be understood.
// If you find more solutions, then add them as well.

int numberOfSetBits(uint32_t);


int ** subsets(int * nums, int numsSize,
               int * returnSize, int ** returnColumnSizes)
{

    *returnSize = 1 << numsSize;

    int** rv = malloc(sizeof(*rv) * *returnSize);

    *returnColumnSizes = malloc(sizeof(**returnColumnSizes) *
                                *returnSize);

    for (int i = 0; i < *returnSize; ++i)
    {
        (*returnColumnSizes)[i] = numberOfSetBits(i);

        rv[i] = malloc(sizeof(*(rv[i])) *
                       (*returnColumnSizes)[i]);

        int rvi_idx = 0;

        for (int idx = 0; idx < numsSize; ++idx)
            if ((1 << idx) & i)
                rv[i][rvi_idx++] = nums[idx];
    }

    return rv;

}


int numberOfSetBits(uint32_t i)
{
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     i = (i + (i >> 4)) & 0x0F0F0F0F;
     return (i * 0x01010101) >> 24;
}
