#include <stdio.h>


int main(void)
{

    // f[0] will remain unused.
    // f[1] will be equal to the no. of groups consisting of one child each.
    // f[2] will be equal to the no. of groups consisting of two children each.
    // and so on.
    unsigned f[5] = { 0 };

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);

        (f[x])++;
    }

    // For the moment, let's ignore the groups consisting of one child each.
    // Then, we need to assign a new taxi to (i) every group consisting of four
    // children each, (ii) every group consisting of three children each and
    // (iii) every 2 groups consisting of two children each.
    // [For unsigned integers, ((x / y) + (x % y != 0)) does ceiling division]
    unsigned number_of_taxis = f[4] + f[3] + ((f[2] / 2) + (f[2] % 2 != 0));

    // Now, let's consider the groups consisting of one child each.
    // Every taxi that is assigned to a group consisting of three children has
    // 1 vacant seat. Also, if the no. of groups consisting of two children each
    // is odd, then there are 2 extra vacant seats.
    // d denotes the difference between the no. of groups consisting of one child
    // each and the no. of available vacant seats.
    // [For integers, (x & 1) evaluates to 1 if x is odd]
    int d = f[1] - (f[3] + (2 * (f[2] & 1)));

    if (d > 0)
        number_of_taxis += ((unsigned) d / 4) + ((unsigned) d % 4 != 0);

    printf("%u\n", number_of_taxis);

    return 0;

}
