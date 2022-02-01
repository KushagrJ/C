// Using indexing from 0 to 4, instead of from 1 to 5.

#include <stdio.h>
#include <stdlib.h>


int main(void)
{

    int num;

    int i = 0;

    while (1)
    {
        scanf("%d", &num);

        if (num == 1)
            break;

        i++;
    }

    printf("%d\n", abs((i / 5) - 2) + abs((i % 5) - 2));

    return 0;

}
