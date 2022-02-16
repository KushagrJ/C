#include <stdio.h>


int main(void)
{

    int n;
    scanf("%d", &n);

    int i;

    for (i = 1; n > (5 * i); i *= 2)
        n -= (5 * i);

    switch ((n - 1) / i)
    {
        case 0:
            printf("Sheldon\n");
            break;
        case 1:
            printf("Leonard\n");
            break;
        case 2:
            printf("Penny\n");
            break;
        case 3:
            printf("Rajesh\n");
            break;
        case 4:
            printf("Howard\n");
            break;
        default:
            ;
    }

    return 0;

}
