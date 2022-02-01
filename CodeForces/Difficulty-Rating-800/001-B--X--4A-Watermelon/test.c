#include <stdio.h>


int main(void)
{

    int n;
    scanf("%d", &n);

    printf("%s\n", ((n < 4) || (n & 1)) ? "NO" : "YES");

    return 0;

}
