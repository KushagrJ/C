// If 'a' is less than 'b', then it isn't true that decreasing 'a' before 'b'
// will always yield the minimum product, even if it seems like that at first
// thought.
// For eg., when a, b, x, y, n are 10, 11, 9, 1, 10, respectively.
// If we decrease 'a' before 'b', since 'a' is less than 'b', then 'a' will
// become equal to 9, alongwith 'n' becoming equal to 9. Now, we will decrease
// 'b', making 'b' equal to 2 and 'n' equal to 0. This will make the minimum
// product of 'a' and 'b' equal to 18.
// But, if we decrease 'b' before 'a' instead of decreasing 'a' before 'b', then
// 'b' will become equal to 1, alongwith 'n' becoming equal to 0. This will make
// the minimum product of 'a' and 'b' equal to 10, which is smaller than 18.

#include <stdio.h>
#include <limits.h>


unsigned long long minimum_product(unsigned long long, unsigned long long,
                                   unsigned long long, unsigned long long,
                                   unsigned long long);
unsigned long long min(unsigned long long, unsigned long long);


int main(void)
{

    int t;
    scanf("%d", &t);

    while (t--)
    {
        unsigned long long a, b, x, y, n;
        scanf("%llu %llu %llu %llu %llu", &a, &b, &x, &y, &n);

        printf("%llu\n",
            min(minimum_product(a, b, x, y, n), minimum_product(b, a, y, x, n)));
    }

    return 0;

}


unsigned long long minimum_product(unsigned long long a, unsigned long long b,
                                   unsigned long long x, unsigned long long y,
                                   unsigned long long n)
{

    unsigned long long integer_to_be_subtracted;

    integer_to_be_subtracted = min((a - x), n);
    a -= integer_to_be_subtracted;
    n -= integer_to_be_subtracted;

    integer_to_be_subtracted = min((b - y), n);
    b -= integer_to_be_subtracted;

    return (a * b);

}


unsigned long long min(unsigned long long p, unsigned long long q)
{

    return ((p < q) ? p : q);

}
