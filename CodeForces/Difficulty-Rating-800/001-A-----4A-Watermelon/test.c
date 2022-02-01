#include <stdio.h>


int main(void)
{

    int input;
    scanf("%d", &input);

    if ((input % 2 == 0) && (input != 2))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;

}
