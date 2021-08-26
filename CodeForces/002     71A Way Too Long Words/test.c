#include <stdio.h>
#include <string.h>


int main(void)
{

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        char c[101];
        scanf("%s", c);

        int x = strlen(c);

        if (x > 10)
            printf("%c%d%c\n", c[0], x-2, c[x-1]);
        else
            printf("%s\n", c);
    }

    return 0;

}
