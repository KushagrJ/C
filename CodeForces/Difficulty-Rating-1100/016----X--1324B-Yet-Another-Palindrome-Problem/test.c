#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(void)
{

    // arr_a[0] and arr_b[0] remain unused.
    // The same arrays 'arr_a' and 'arr_b' are used for all the test cases, since
    // it is given that the sum of n over all test cases does not exceed 5000.

    int* arr_a = calloc(5001, sizeof (int));
    int* a = arr_a;

    int* arr_b = calloc(5001, sizeof (int));
    int* b = arr_b;

    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n;
        scanf("%d", &n);

        // It is given that for all the test cases, the input integers will lie
        // between 1 and n, both inclusive.

        // arr_a[i] is the number of times 'i' occurs in the input array.

        // arr_b[i] is the number of times 'i' occurs in the input array such
        // that the integer scanned immediately after it is a different integer,
        // or there are no more integers left to be scanned.

        int second;
        scanf("%d", &second);

        for (int i = 1; i < n; i++)
        {
            int first = second;
            scanf("%d", &second);

            (a[first])++;

            if (first != second)
                (b[first])++;
        }

        (a[second])++;
        (b[second])++;

        // For a palindromic subsequence to exist, either the same integer must
        // occur at least thrice (not necessarily consecutively), or at least two
        // occurrences of the same integer must be there such that there is
        // at least one different integer between them.

        bool palindromic_subsequence_exists = false;

        for (int i = 1; i <= n; i++)
        {
            if ((a[i] >= 3) || (b[i] >= 2))
            {
                palindromic_subsequence_exists = true;
                break;
            }
        }

        if (palindromic_subsequence_exists)
            printf("YES\n");
        else
            printf("NO\n");

        a += n;
        b += n;
    }

    free(arr_a);
    free(arr_b);

    return 0;

}
