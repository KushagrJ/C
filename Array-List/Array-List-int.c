#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "Array-List-int.h"

////////////////////////////////////////////////////////////////////////////////

#define AL_INT_INDEX_OUT_OF_BOUNDS "Array List (int) - Index out of Bounds"
#define AL_INT_CAPACITY_OVERFLOW "Array List (int) Capacity Overflow"
#define AL_INT_OUT_OF_MEMORY "Array List (int) - Out of Memory"

// Terminates the program after sending a diagnostic message to stderr.
// 'cause' points to the first character of a null-terminated string describing
// the cause of termination.
// 'caller' points to the first character of a null-terminated string
// representing the name of the calling function.
static void AL_int_exit(const char* cause, const char* caller)
{
    fprintf(stderr, "%s\n\tat %s()\n", cause, caller);
    fprintf(stderr, "\nExiting due to failure\n");

    exit(EXIT_FAILURE);
}

////////////////////////////////////////////////////////////////////////////////

const ptrdiff_t AL_INT_MAX_CAPACITY =
    ((uintmax_t) PTRDIFF_MAX < SIZE_MAX / sizeof (int)) ?
        PTRDIFF_MAX : (ptrdiff_t) (SIZE_MAX / sizeof (int));

// Increases the capacity of the array list (which is handled by the object
// handler pointed to by 'ptr').
// May cause the program to terminate due to 'capacity overflow' or 'out of
// memory'.
static void AL_int_expand(AL_int* ptr)
{
    if (ptr->capacity > AL_INT_MAX_CAPACITY / 2)
    {
        if (ptr->capacity < AL_INT_MAX_CAPACITY)
            ptr->capacity = AL_INT_MAX_CAPACITY;
        else
            AL_int_exit(AL_INT_CAPACITY_OVERFLOW, __func__);
    }

    else
    {
        ptr->capacity = ptr->capacity * 2;
    }

    ptr->arr = realloc(ptr->arr, (size_t) ptr->capacity * sizeof (int));
    if (ptr->arr == NULL)
        AL_int_exit(AL_INT_OUT_OF_MEMORY, __func__);
}

// Reduces the capacity of the array list (which is handled by the object
// handler pointed to by 'ptr').
// May cause the program to terminate due to 'out of memory'.
static void AL_int_shrink(AL_int* ptr)
{
    ptr->capacity = (ptr->size == 0) ? 1 : ptr->size;

    ptr->arr = realloc(ptr->arr, (size_t) ptr->capacity * sizeof (int));
    if (ptr->arr == NULL)
        AL_int_exit(AL_INT_OUT_OF_MEMORY, __func__);
}

////////////////////////////////////////////////////////////////////////////////

// Shifts (by copying) the elements of the array list (which is handled by the
// object handler pointed to by 'ptr') at the range of indices ['l', ptr->size)
// left by 'offset' positions.
// It must be ensured that 'l' and 'offset' are valid.
static void AL_int_shift_left(const AL_int* ptr, ptrdiff_t l, ptrdiff_t offset)
{
    // for (ptrdiff_t k = l; k < ptr->size; ++k)
    //     (ptr->arr)[k - offset] = (ptr->arr)[k];

    memmove(ptr->arr + l - offset, ptr->arr + l,
            (size_t) (ptr->size - l) * sizeof (int));
}

// Shifts (by copying) the elements of the array list (which is handled by the
// object handler pointed to by 'ptr') at the range of indices ['l', ptr->size)
// right by 'offset' positions.
// It must be ensured that 'l' and 'offset' are valid, and that the capacity of
// the array list is large enough.
static void AL_int_shift_right(const AL_int* ptr, ptrdiff_t l, ptrdiff_t offset)
{
    // for (ptrdiff_t k = ptr->size - 1; k >= l; --k)
    //     (ptr->arr)[k + offset] = (ptr->arr)[k];

    memmove(ptr->arr + l + offset, ptr->arr + l,
            (size_t) (ptr->size - l) * sizeof (int));
}

////////////////////////////////////////////////////////////////////////////////

void AL_int_create_empty(AL_int* ptr)
{
    ptr->arr = malloc(sizeof (int));
    if (ptr->arr == NULL)
        AL_int_exit(AL_INT_OUT_OF_MEMORY, __func__);

    ptr->size = 0;
    ptr->capacity = 1;
}

void AL_int_create_empty_with_initial_capacity(AL_int* ptr,
                                               ptrdiff_t initial_capacity)
{
    ptr->arr = malloc((size_t) initial_capacity * sizeof (int));
    if (ptr->arr == NULL)
        AL_int_exit(AL_INT_OUT_OF_MEMORY, __func__);

    ptr->size = 0;
    ptr->capacity = initial_capacity;
}

void AL_int_destroy(const AL_int* ptr)
{
    free(ptr->arr);
}

////////////////////////////////////////////////////////////////////////////////

void AL_int_add(AL_int* ptr, int n)
{
    if (ptr->size == ptr->capacity)
        AL_int_expand(ptr);

    (ptr->arr)[ptr->size] = n;
    ++(ptr->size);
}

void AL_int_add_at_index(AL_int* ptr, ptrdiff_t i, int n)
{
    if ((i < 0) || (i > ptr->size))
        AL_int_exit(AL_INT_INDEX_OUT_OF_BOUNDS, __func__);

    if (ptr->size == ptr->capacity)
        AL_int_expand(ptr);

    AL_int_shift_right(ptr, i, 1);
    (ptr->arr)[i] = n;
    ++(ptr->size);
}

void AL_int_clear(AL_int* ptr)
{
    ptr->size = 0;
    AL_int_shrink(ptr);
}

bool AL_int_contains(const AL_int* ptr, int n)
{
    for (ptrdiff_t i = 0; i < ptr->size; ++i)
        if ((ptr->arr)[i] == n)
            return true;

    return false;
}

int AL_int_get(const AL_int* ptr, ptrdiff_t i)
{
    if ((i < 0) || (i >= ptr->size))
        AL_int_exit(AL_INT_INDEX_OUT_OF_BOUNDS, __func__);

    return (ptr->arr)[i];
}

ptrdiff_t AL_int_index_of(const AL_int* ptr, ptrdiff_t i, ptrdiff_t j, int n)
{
    for (ptrdiff_t k = i; k < j; ++k)
        if ((ptr->arr)[k] == n)
            return k;

    return -1;
}

bool AL_int_is_empty(const AL_int* ptr)
{
    return ptr->size == 0;
}

ptrdiff_t AL_int_last_index_of(const AL_int* ptr, ptrdiff_t i, ptrdiff_t j,
                               int n)
{
    for (ptrdiff_t k = j - 1; k >= i; --k)
        if ((ptr->arr)[k] == n)
            return k;

    return -1;
}

void AL_int_remove(AL_int* ptr, ptrdiff_t i)
{
    AL_int_remove_range(ptr, i, i + 1);
}

void AL_int_remove_range(AL_int* ptr, ptrdiff_t i, ptrdiff_t j)
{
    if ((i >= j) || (i < 0) || (j > ptr->size))
        AL_int_exit(AL_INT_INDEX_OUT_OF_BOUNDS, __func__);

    ptrdiff_t offset = j - i;

    AL_int_shift_left(ptr, j, offset);
    ptr->size -= offset;

    if (ptr->size < ptr->capacity / 2)
        AL_int_shrink(ptr);
}

void AL_int_set(AL_int* ptr, ptrdiff_t i, int n)
{
    if ((i < 0) || (i >= ptr->size))
        AL_int_exit(AL_INT_INDEX_OUT_OF_BOUNDS, __func__);

    (ptr->arr)[i] = n;
}

ptrdiff_t AL_int_size(const AL_int* ptr)
{
    return ptr->size;
}

int* AL_int_to_array(const AL_int* ptr)
{
    int* array = malloc((size_t) ptr->size * sizeof (int));
    if (ptr->arr == NULL)
        AL_int_exit(AL_INT_OUT_OF_MEMORY, __func__);

    for (ptrdiff_t i = 0; i < ptr->size; ++i)
        array[i] = (ptr->arr)[i];

    return array;
}
