#include <stdio.h>
#include <stdlib.h>


int main(void)
{

    // arr[0] remains unused.
    // The same array 'arr' is used for all the test cases, since it is given
    // that the sum of n over all test cases does not exceed 200000.
    int* arr = calloc(200001, sizeof (int));
    int* a = arr;

    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 1; i <= n; i++)
        {
            int p;
            scanf("%d", &p);

            (a[p])++;
        }

        int number_of_distinct_integers = 0;

        // highest_frequency is the number of times the most-occurring integer
        // occurs.
        int highest_frequency = 0;

        for (int i = 1; i <= n; i++)
        {
            if (a[i] > 0)
                (number_of_distinct_integers)++;

            if (a[i] > highest_frequency)
                highest_frequency = a[i];
        }

        int x;

        if (n == 1)
            x = 0;
        else if (highest_frequency > number_of_distinct_integers)
            x = number_of_distinct_integers;
        else if (highest_frequency == number_of_distinct_integers)
            x = number_of_distinct_integers - 1; // i.e. (highest_frequency - 1)
        else
            x = highest_frequency;

        printf("%d\n", x);

        a += n;
    }

    free(arr);

    return 0;

}
