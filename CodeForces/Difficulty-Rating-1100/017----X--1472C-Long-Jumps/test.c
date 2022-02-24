#include <stdio.h>
#include <stdlib.h>


int main(void)
{

    // arr[0] remains unused.
    // The same array 'arr' is used for all the test cases, since it is given
    // that the sum of n over all test cases does not exceed 200000.
    int* arr = malloc(200001 * sizeof (int));
    int* a = arr;

    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        // For eg., a == [3, 2, 5, 1, 3, 2, 5, 2, 4, 7] (indexing begins from 1).
        // If i == 1 is chosen, then the sequence will be 3 -> 1 -> 3 -> 2 -> 7,
        // making the score equal to 16.
        // If i == 2 is chosen, then the sequence will be 2 -> 1 -> 3 -> 2 -> 7,
        // making the score equal to 15.
        // The second score is less than the first one.
        // In both the cases, the sequences reach a common index (i.e. i == 4),
        // after which the remaining sequence stays the same.
        // This means that if a sequence begins at some index i, then the score
        // resulting from it will be the largest among the scores resulting from
        // all such sequences which reach a common index and begin at indices
        // greater than i.

        // Thus, upon varying i (i.e. the starting index) from 1 to n, if a
        // sequence reaches a previously visited index, then it is useless to
        // check the score resulting from that sequence.
        // Here, to indicate that an index has been visited, the value at that
        // index is changed to 0.

        unsigned long long maximum_score = 0;

        for (int i = 1; i <= n; i++)
        {
            int j = i;
            unsigned long long current_score = 0;

            while ((j <= n) && (a[j]))
            {
                current_score += a[j];

                int temp = a[j];
                a[j] = 0;
                j += temp;
            }

            if (current_score > maximum_score)
                maximum_score = current_score;
        }

        printf("%llu\n", maximum_score);

        a += n;
    }

    free(arr);

    return 0;

}
