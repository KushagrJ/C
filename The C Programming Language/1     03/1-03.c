#include <stdio.h>


int main(void)
{

    double fahr, celsius;

    int lower = 0;
    int upper = 300;
    int step = 20;

    fahr = lower;

    printf(" F      C\n\n");
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%03.0f   %05.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    return 0;

}
