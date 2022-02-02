#include <stdio.h>
#include <stdbool.h>


int main(void)
{

    // alphabet_is_present[0] is true if 'a' is present in the string.
    // alphabet_is_present[1] is true if 'b' is present in the string.
    // and so on.
    bool alphabet_is_present[26] = { false };

    int number_of_distinct_characters = 0;

    int c;
    while (((c = getchar()) != '\n') && (c != EOF))
    {
        if (!(alphabet_is_present[c - 'a']))
        {
            alphabet_is_present[c - 'a'] = true;
            (number_of_distinct_characters)++;
        }
    }

    // (x & 1) evaluates to 1 when x is an odd integer.
    if (number_of_distinct_characters & 1)
        printf("IGNORE HIM!\n");
    else
        printf("CHAT WITH HER!\n");

    return 0;

}
