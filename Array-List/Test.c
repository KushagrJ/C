#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "Array-List-int.h"

int main(void)
{
    AL_int a1;
    AL_int_create_empty(&a1);

    printf("---------------------------------------------------------------\n");

    printf(AL_int_is_empty(&a1) ? "true\n" : "false\n");

    printf("---------------------------------------------------------------\n");

    AL_int_add(&a1, 10);
    AL_int_add(&a1, 20);
    AL_int_add(&a1, 30);

    printf("%d\n", AL_int_get(&a1, 1));

    printf("---------------------------------------------------------------\n");

    printf(AL_int_is_empty(&a1) ? "true\n" : "false\n");

    printf("%td\n", AL_int_size(&a1));

    printf("---------------------------------------------------------------\n");

    for (ptrdiff_t i = 0; i < AL_int_size(&a1); ++i)
    {
        printf("%d ", AL_int_get(&a1, i));
    }

    printf("\n");

    printf("---------------------------------------------------------------\n");

    AL_int_set(&a1, 2, 40);

    for (ptrdiff_t i = 0; i < AL_int_size(&a1); ++i)
    {
        printf("%d ", AL_int_get(&a1, i));
    }

    printf("\n");

    printf("---------------------------------------------------------------\n");

    AL_int_add_at_index(&a1, 1, 50);

    for (ptrdiff_t i = 0; i < AL_int_size(&a1); ++i)
    {
        printf("%d ", AL_int_get(&a1, i));
    }

    printf("\n");

    printf("---------------------------------------------------------------\n");

    AL_int_clear(&a1);

    printf("%td\n", AL_int_size(&a1));

    printf("---------------------------------------------------------------\n");

    AL_int_add(&a1, 10);
    AL_int_add(&a1, 20);
    AL_int_add(&a1, 30);
    AL_int_add(&a1, 40);
    AL_int_add(&a1, 10);
    AL_int_add(&a1, 20);

    for (ptrdiff_t i = 0; i < AL_int_size(&a1); ++i)
    {
        printf("%d ", AL_int_get(&a1, i));
    }

    printf("\n");

    printf(AL_int_contains(&a1, 30) ? "true\n" : "false\n");

    printf(AL_int_contains(&a1, 50) ? "true\n" : "false\n");

    printf("---------------------------------------------------------------\n");

    for (ptrdiff_t i = 0; i < AL_int_size(&a1); ++i)
    {
        printf("%d ", AL_int_get(&a1, i));
    }

    printf("\n");

    printf("%td\n", AL_int_index_of(&a1, 0, AL_int_size(&a1), 10));

    printf("%td\n", AL_int_index_of(&a1, 0, AL_int_size(&a1), 30));

    printf("%td\n", AL_int_index_of(&a1, 0, AL_int_size(&a1), 50));

    printf("---------------------------------------------------------------\n");

    for (ptrdiff_t i = 0; i < AL_int_size(&a1); ++i)
    {
        printf("%d ", AL_int_get(&a1, i));
    }

    printf("\n");

    printf("%td\n", AL_int_last_index_of(&a1, 0, AL_int_size(&a1), 10));

    printf("%td\n", AL_int_last_index_of(&a1, 0, AL_int_size(&a1), 30));

    printf("%td\n", AL_int_last_index_of(&a1, 0, AL_int_size(&a1), 50));

    printf("---------------------------------------------------------------\n");

    AL_int_remove(&a1, 3);

    for (ptrdiff_t i = 0; i < AL_int_size(&a1); ++i)
    {
        printf("%d ", AL_int_get(&a1, i));
    }

    printf("\n");

    printf("---------------------------------------------------------------\n");

    AL_int_remove_range(&a1, 1, 3);

    int* array = AL_int_to_array(&a1);

    for (ptrdiff_t i = 0; i < AL_int_size(&a1); ++i)
    {
        printf("%d ", array[i]);
    }

    printf("\n");

    printf("---------------------------------------------------------------\n");

    free((void*) array);

    AL_int_destroy(&a1);

    return 0;
}
