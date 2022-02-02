#include <stdio.h>


int main(void)
{

    unsigned long long n, m, a;
    scanf("%llu %llu %llu", &n, &m, &a);

    // For unsigned integers, ((x / y) + (x % y != 0)) does ceiling division.
    printf("%llu\n", ((n / a) + (n % a != 0)) * ((m / a) + (m % a != 0)));

    return 0;

}
