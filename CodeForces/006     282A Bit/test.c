#include <stdio.h>


int main(void)
{

    int n;
    scanf("%d", &n);

    char arr[4]; // Last element - '\0'
    int answer = 0;

    for (int i = 0; i < n; i++)
    {
        scanf("%s", arr);

        if (arr[1] == '+')
            answer++;
        else
            answer--;
    }

    printf("%d\n", answer);

    return 0;

}
