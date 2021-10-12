#include <stdio.h>
#include <string.h>


#define N 10


const int LOWER_LIMIT = -(1 << (N-1));
const int UPPER_LIMIT = +(1 << (N-1)) - 1;


void convert_decimal_integer_to_N_bit_binary(int, _Bool*);
void find_twos_complement_in_N_bits(_Bool*, _Bool*);
void add_two_N_bit_binary_integers(_Bool*, _Bool*, _Bool*);
int convert_2N_bit_binary_integer_to_decimal(_Bool*);


int main(void)
{

    int temp;

    printf("Enter Multiplicand & Multiplier (%+d to %+d): ",
           LOWER_LIMIT, UPPER_LIMIT);

    _Bool multiplicand[N];
    scanf("%d", &temp);
    convert_decimal_integer_to_N_bit_binary(temp,
                                            multiplicand);
    printf("\nMultiplicand, M = %d = ", temp);
    for (int i = 0; i < N; i++)
        printf("%d", (int) multiplicand[i]);
    printf("\n");

    _Bool negative_of_multiplicand[N];
    find_twos_complement_in_N_bits(multiplicand,
                                   negative_of_multiplicand);
    printf("-M = 2's complement of M = ");
    for (int i = 0; i < N; i++)
        printf("%d", (int) negative_of_multiplicand[i]);
    printf("\n");

    _Bool product[(2*N)+1] = { (_Bool) 0 };
    scanf("%d", &temp);
    convert_decimal_integer_to_N_bit_binary(temp,
                                            product + N);
    printf("Multiplier, Q = %d = ", temp);
    for (int i = 0; i < N; i++)
        printf("%d", (int) product[i+N]);
    printf("\n");

    printf("Accumulator, A = 0 = %0*d\n", N, 0);

    int sequence_counter = N;
    printf("Sequence Counter, SC = %d\n\n\n\n", N);


    printf("  %*cA%*cQ%*cSC\n\n\n", N-1, ' ', 2*(N+1), ' ',
           N+3, ' ');

    printf("  ");
    for (int i = 0; i < N; i++)
        printf("%d ", (int) product[i]);
    printf("  ");
    for (int i = N; i <= 2*N; i++)
        printf("%d ", (int) product[i]);
    printf("  %d\n", N);
    (sequence_counter)--;

    while (sequence_counter >= 0)
    {
        if (product[(2*N)-1] == 0 && product[2*N] == 1)
        {
            printf("\n\n  A = A + M,\n\n");

            printf("  ");
            for (int i = 0; i < N; i++)
                printf("%d ", (int) product[i]);
            putchar('\n');

            printf("+ ");
            for (int i = 0; i < N; i++)
                printf("%d ", (int) multiplicand[i]);
            putchar('\n');

            printf("  ");
            for (int i = 0; i < (2*N)-1; i++)
                printf("-");
            putchar('\n');

            add_two_N_bit_binary_integers(product,
                                          multiplicand,
                                          product);

            printf("  ");
            for (int i = 0; i < N; i++)
                printf("%d ", (int) product[i]);
            printf("  ");
            for (int i = N; i <= 2*N; i++)
                printf("%d ", (int) product[i]);
            putchar('\n');

            printf("  ");
            for (int i = 0; i < (2*N)-1; i++)
                printf("-");
            putchar('\n');
        }


        else if (product[(2*N)-1] == 1 && product[2*N] == 0)
        {
            printf("\n\n  A = A + (-M),\n\n");

            printf("  ");
            for (int i = 0; i < N; i++)
                printf("%d ", (int) product[i]);
            putchar('\n');

            printf("+ ");
            for (int i = 0; i < N; i++)
                printf("%d ",
                       (int) negative_of_multiplicand[i]);
            putchar('\n');

            printf("  ");
            for (int i = 0; i < (2*N)-1; i++)
                printf("-");
            putchar('\n');

            add_two_N_bit_binary_integers(product,
                                    negative_of_multiplicand,
                                    product);

            printf("  ");
            for (int i = 0; i < N; i++)
                printf("%d ", (int) product[i]);
            printf("  ");
            for (int i = N; i <= 2*N; i++)
                printf("%d ", (int) product[i]);
            putchar('\n');

            printf("  ");
            for (int i = 0; i < (2*N)-1; i++)
                printf("-");
            putchar('\n');
        }


        printf("\n\n  Arithmetic right shift,\n\n");

        memmove(product + 1, product, 2*N * sizeof (_Bool));

        printf("  ");
        for (int i = 0; i < N; i++)
            printf("%d ", (int) product[i]);
        printf("  ");
        for (int i = N; i <= 2*N; i++)
            printf("%d ", (int) product[i]);
        printf("  %d\n", sequence_counter);


        (sequence_counter)--;
    }

    printf("\n\n\nProduct = ");
    for (int i = 0; i < 2*N; i++)
        printf("%d", product[i]);
    printf(" = %+d\n",
          convert_2N_bit_binary_integer_to_decimal(product));

    return 0;

}


void convert_decimal_integer_to_N_bit_binary(int decimal,
                                             _Bool* binary)
{

    int temp;

    if (decimal >= 0)
    {
        binary[0] = (_Bool) 0;
        temp = decimal;
    }

    else
    {
        binary[0] = (_Bool) 1;
        temp = decimal + (1 << ((2*N)-1));
    }

    for (int i = N-1; i > 0; i--)
    {
        binary[i] = temp % 2;
        temp /= 2;
    }

}


void find_twos_complement_in_N_bits(_Bool* original,
                                    _Bool* result)
{

    for (int i = 0; i < N; i++)
        result[i] = (_Bool) (1 - original[i]);

    _Bool one[N] = { [N-1] = (_Bool) 1 };

    add_two_N_bit_binary_integers(result, one, result);

}


void add_two_N_bit_binary_integers(_Bool* num1, _Bool* num2,
                                   _Bool* sum)
{

    int a, b;
    int carry = 0;

    for (int i = N-1; i >= 0; i--)
    {
        a = (int) num1[i];
        b = (int) num2[i];

        switch (a + b + carry)
        {
            case 0:
                sum[i] = (_Bool) 0;
                carry = 0;
                break;
            case 1:
                sum[i] = (_Bool) 1;
                carry = 0;
                break;
            case 2:
                sum[i] = (_Bool) 0;
                carry = 1;
                break;
            case 3:
                sum[i] = (_Bool) 1;
                carry = 1;
        }
    }

}


int convert_2N_bit_binary_integer_to_decimal(_Bool* binary)
{

    int decimal = 0;

    for (int i = (2*N)-1; i > 0; i--)
        decimal += (1 << ((2*N) - i - 1)) * (int) binary[i];

    if (binary[0] == (_Bool) 0)
        return decimal;
    else
        return decimal - (1 << ((2*N)-1));

}
