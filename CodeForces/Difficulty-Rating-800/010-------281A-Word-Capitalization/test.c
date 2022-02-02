#include <stdio.h>
#include <ctype.h>


int main(void)
{

    int c;

    c = getchar();
    putchar(toupper(c));

    while (((c = getchar()) != '\n') && (c != EOF))
        putchar(c);
    putchar('\n');

    return 0;

}
