#include <stdio.h>


int main(void)
{

    int numberOfProblems;
    scanf("%d", &numberOfProblems);

    int answer = 0;

    while (numberOfProblems--)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        if (a+b+c >= 2)
            answer++;
    }

    printf("%d\n", answer);

    return 0;

}
