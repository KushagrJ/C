#include <stdio.h>


int main(void)
{

    long blanks = 0L;
    int tabs = 0;
    int lines = 1;

    char lastChar = '\n';

    printf("Enter text (EOF to quit) :-\n");

    int c;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
            blanks++;

        else if (c == '\t')
            tabs++;

        else if (c == '\n')
            lines++;

        lastChar = c;
    }

    if (lastChar == '\n')
        lines--;

    printf("\n\nNo. of blanks = %ld\n", blanks);
    printf("No. of tabs   = %d\n", tabs);
    printf("No. of lines  = %d\n", lines);

    return 0;

}
