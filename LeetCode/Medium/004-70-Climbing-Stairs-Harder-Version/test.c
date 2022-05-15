#include <stdio.h>
#include <stdlib.h>


int main(void)
{

    int n;
    printf("Enter the number of stairs (positive integer): ");
    scanf("%d", &n);

    int m;
    printf("Enter the max capacity (positive integer): ");
    scanf("%d", &m);

    int* ans = malloc((n + m + 1) * sizeof (int));
    if (ans == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < m; i++)
        ans[i] = 0;
    ans += m;
    ans[0] = 1;

    int current_sum = 0;

    for (int i = 1; i <= n; i++)
    {
        current_sum -= ans[i - m - 1];
        current_sum += ans[i - 1];

        ans[i] = current_sum;
    }

    printf("No. of ways: %d\n", ans[n]);

    free(ans - m);

    return EXIT_SUCCESS;

}
