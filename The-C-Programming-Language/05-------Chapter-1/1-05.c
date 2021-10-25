#include <stdio.h>


int main(void)
{

    double fahr, celsius;

    int lower = 0;
    int upper = 300;
    int step = 20;

    celsius = upper;

    printf(" C      F\n\n");
    while (celsius >= lower)
    {
        fahr = ((9.0 / 5.0) * celsius) + 32.0;
        printf("%03.0f   %05.1f\n", celsius, fahr);
        celsius = celsius - step;
    }

    return 0;

}
