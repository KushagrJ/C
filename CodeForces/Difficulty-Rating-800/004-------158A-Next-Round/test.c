#include <stdio.h>


int main(void)
{

    int n, k;
    scanf("%d %d", &n, &k);

    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int answer = 0;
    for (int i = 0; i < n; i++)
        if ((arr[i] > 0) && (arr[i] >= arr[k-1]))
            answer++;

    printf("%d\n", answer);

    return 0;

}
