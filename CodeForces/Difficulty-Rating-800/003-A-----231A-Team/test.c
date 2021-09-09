#include <stdio.h>


int main(void)
{

    int numberOfProblems;
    scanf("%d", &numberOfProblems);

    int answer = 0;

    for (int i = 0; i < numberOfProblems; i++)
    {
        int count = 0;
        int input;

        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &input);
            if (input == 1)
                count++;
        }

        if (count >= 2)
            answer++;
    }

    printf("%d\n", answer);

    return 0;

}
