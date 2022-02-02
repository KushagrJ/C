#include <stdio.h>
#include <ctype.h>


int main(void)
{

    int c;

    while (((c = getchar()) != '\n') && (c != EOF))
    {
        switch (c)
        {
            case 'a':
            case 'A':
            case 'e':
            case 'E':
            case 'i':
            case 'I':
            case 'o':
            case 'O':
            case 'u':
            case 'U':
            case 'y':
            case 'Y':
                continue;
                break;
            default:
                printf(".%c", tolower(c));
        }
    }

    putchar('\n');

    return 0;

}
