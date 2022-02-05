#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int qsort_compare(const void*, const void*);


int main(void)
{

    int n;
    scanf("%d", &n);

    int a[100000];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    qsort(a, n, sizeof (int), qsort_compare);

    int b[100000];
    for (int j = 0; j < n - 1; j++)
        scanf("%d", &b[j]);
    b[n - 1] = 0;
    qsort(b, n - 1, sizeof (int), qsort_compare);

    int c[100000];
    for (int k = 0; k < n - 2; k++)
        scanf("%d", &c[k]);
    c[n - 2] = c[n - 1] = 0;
    qsort(c, n - 2, sizeof (int), qsort_compare);

    int first_error, second_error;
    bool first_error_found = false, second_error_found = false;

    for (int p = 0; p < n; p++)
    {
        if (!(first_error_found) && (a[p] != b[p]))
        {
            first_error = a[p];
            first_error_found = true;
        }

        if (!(second_error_found) && (b[p] != c[p]))
        {
            second_error = b[p];
            second_error_found = true;
        }

        if (first_error_found && second_error_found)
        {
            break;
        }
    }

    printf("%d\n%d\n", first_error, second_error);

    return 0;

}


int qsort_compare(const void* a, const void* b)
{

    int x = *((const int*) a);
    int y = *((const int*) b);

    if (x > y)
        return 1;
    else if (x == y)
        return 0;
    else
        return -1;

}
