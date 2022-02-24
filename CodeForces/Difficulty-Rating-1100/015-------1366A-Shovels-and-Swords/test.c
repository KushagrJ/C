#include <stdio.h>


int main(void)
{

    int t;
    scanf("%d", &t);

    while (t--)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        int number_of_emeralds;

        if (a <= (b / 2))
            number_of_emeralds = a;
        else if (b <= (a / 2))
            number_of_emeralds = b;
        else
            number_of_emeralds = ((a + b) / 3);

        printf("%d\n", number_of_emeralds);
    }

    return 0;

}
