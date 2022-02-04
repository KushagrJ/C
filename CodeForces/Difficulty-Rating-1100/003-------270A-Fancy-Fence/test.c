#include <stdio.h>


int main(void)
{

    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++)
    {
        int a;
        scanf("%d", &a);

        // Each interior angle (in degrees) of a regular polygon having n sides
        // is equal to (((n - 2) * 180) / n).
        if (360 % (180 - a) == 0)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;

}
