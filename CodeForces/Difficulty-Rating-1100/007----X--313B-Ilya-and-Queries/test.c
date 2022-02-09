#include <stdio.h>


int main(void)
{

    // According to the problem, the indexing in the input string starts from 1.

    // First, an array is created such that
    // (1) arr[0] is equal to 0,
    // (2) if s[i] is equal to s[i + 1], then arr[i] is equal to 1, and
    // (3) if s[i] is not equal to s[i + 1], then arr[i] is equal to 0.
    // Thus, the indexing in this array starts from 0 and goes up to (n - 1).

    // Now, the answer to the query 'l,r' is equal to the following sum :-
    // arr[l] + arr[l + 1] + ... + arr[r - 1].

    // To calculate the sums faster, the following operation is applied to the
    // array before answering the queries:-
    // for (int i = 1; i < 100000; i++)
    //     arr[i] += arr[i - 1];
    // This makes the answer to the query 'l,r' equal to arr[r - 1] - arr[l - 1].
    // [In other words, the sum from arr[l] to arr[r - 1] is equal to the sum
    // from arr[0] to arr[r - 1] minus the sum from arr[0] to arr[l - 1]]

    // In this program, both of these steps have been completed in a single loop.

    int a[100000];
    a[0] = 0;

    int c1 = getchar();

    int c2;
    for (int i = 1; (((c2 = getchar()) != '\n') && (c2 != EOF)); i++)
    {
        if (c1 == c2)
            a[i] = 1;
        else
            a[i] = 0;

        a[i] += a[i - 1];

        c1 = c2;
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        int l, r;
        scanf("%d %d", &l, &r);

        printf("%d\n", a[r - 1] - a[l - 1]);
    }

    return 0;

}





/* Exceeds time limit -

#include <stdio.h>


int main(void)
{

    char s[100002];
    fgets(s + 1, 100001, stdin);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        int l, r;
        scanf("%d %d", &l, &r);

        int answer = 0;

        for (int j = l; j < r; j++)
        {
            if (s[j] == s[j + 1])
                (answer)++;
        }

        printf("%d\n", answer);
    }

    return 0;

}

*/
