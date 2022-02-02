#include <stdio.h>


int main(void)
{

    scanf("%*d");

    int minimum_stones = 0;

    char c1;
    scanf(" %c", &c1);

    int c2;

    while (((c2 = getchar()) != '\n') && (c2 != EOF))
    {
        if (c1 == (char) c2)
            (minimum_stones)++;

        c1 = (char) c2;
    }

    printf("%d\n", minimum_stones);

    return 0;

}
