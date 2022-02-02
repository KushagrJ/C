#include <stdio.h>


int main(void)
{

    int a, b;
    scanf("%d %d", &a, &b);

    int number_of_years = 0;

    while (a <= b)
    {
        (number_of_years)++;
        a *= 3;
        b *= 2;
    }

    printf("%d\n", number_of_years);

    return 0;

}
