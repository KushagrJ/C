#include <stdio.h>
#include <ctype.h>
#include <string.h>


int main(void)
{

    char str1[101], str2[101];

    scanf("%100s", str1);
    scanf("%100s", str2);

    _Bool stringsEqual = 1;

    for (int i = 0; i < strlen(str1); i++)
        if (tolower(str1[i]) != tolower(str2[i]))
        {
            stringsEqual = 0;

            if (tolower(str1[i]) > tolower(str2[i]))
                printf("1\n");
            else
                printf("-1\n");

            break;
        }

    if (stringsEqual == 1)
        printf("0\n");

    return 0;

}
