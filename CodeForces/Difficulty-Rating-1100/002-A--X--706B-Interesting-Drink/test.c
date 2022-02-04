#include <stdio.h>
#include <stdlib.h>


int qsort_compare(const void*, const void*);
int number_of_elements_less_than_or_equal_to(int*, int, int);


int main(void)
{

    int n;
    scanf("%d", &n);

    int arr[100000];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    qsort(arr, n, sizeof (int), qsort_compare);

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++)
    {
        int m;
        scanf("%d", &m);

        printf("%d\n", number_of_elements_less_than_or_equal_to(arr, n, m));
    }

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


int number_of_elements_less_than_or_equal_to(int* arr, int n, int target)
{

    int lower_index = 0;
    int upper_index = n - 1;

    // required_index is the index of the last element which is less than or
    // equal to target.
    int required_index = -1;

    while (lower_index <= upper_index)
    {
        int middle_index = (lower_index + upper_index) / 2;

        if (arr[middle_index] <= target)
        {
            required_index = middle_index;
            lower_index = middle_index + 1;
        }

        else
        {
            upper_index = middle_index - 1;
        }
    }

    return required_index + 1;

}
