#ifndef ARRAY_LIST_INT
#define ARRAY_LIST_INT

#include <stddef.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////

// AL_int x; creates an object handler called 'x' for an array list.
// The creation of an object handler for an array list must be followed by
// AL_int_create_empty() or AL_int_create_empty_with_initial_capacity() before
// the array list can be used.
typedef struct
{
    int* arr;
    ptrdiff_t size;
    ptrdiff_t capacity;
}
AL_int;

////////////////////////////////////////////////////////////////////////////////

extern const ptrdiff_t AL_INT_MAX_CAPACITY;

// Allocates memory for the array list (which is handled by the object handler
// pointed to by 'ptr'), and sets the size and the capacity of the array list to
// 0 and 1, respectively.
// May cause the program to terminate due to 'out of memory'.
void AL_int_create_empty(AL_int* ptr);

// Allocates memory for the array list (which is handled by the object handler
// pointed to by 'ptr'), and sets the size and the capacity of the array list to
// 0 and 'initial_capacity', respectively.
// May cause the program to terminate due to 'out of memory'.
// 'initial_capacity' must be less than or equal to AL_INT_MAX_CAPACITY.
void AL_int_create_empty_with_initial_capacity(AL_int* ptr,
                                               ptrdiff_t initial_capacity);

// Frees the memory taken up by the array list (which is handled by the object
// handler pointed to by 'ptr').
void AL_int_destroy(const AL_int* ptr);

////////////////////////////////////////////////////////////////////////////////

// Adds 'n' to the end of the array list (which is handled by the object handler
// pointed to by 'ptr').
// May cause the program to terminate due to 'capacity overflow' or 'out of
// memory'.
void AL_int_add(AL_int* ptr, int n);

// Adds 'n' at the index 'i' to the array list (which is handled by the object
// handler pointed to by 'ptr'), shifting elements as required.
// May cause the program to terminate due to 'index out of bounds', 'capacity
// overflow' or 'out of memory'.
void AL_int_add_at_index(AL_int* ptr, ptrdiff_t i, int n);

// Clears the array list (which is handled by the object handler pointed to by
// 'ptr'), and sets the size and the capacity of the array list to 0 and 1,
// respectively.
// May cause the program to terminate due to 'out of memory'.
void AL_int_clear(AL_int* ptr);

// Returns true if 'n' is present in the array list (which is handled by the
// object handler pointed to by 'ptr'), and returns false otherwise.
bool AL_int_contains(const AL_int* ptr, int n);

// Returns the element at the index 'i' in the array list (which is handled by
// the object handler pointed to by 'ptr').
// May cause the program to terminate due to 'index out of bounds'.
int AL_int_get(const AL_int* ptr, ptrdiff_t i);

// Returns the index of the first occurrence of 'n' at the range of indices
// ['i', 'j') in the array list (which is handled by the object handler pointed
// to by 'ptr'), and returns -1 if 'n' is not present at the range of indices in
// the array list.
ptrdiff_t AL_int_index_of(const AL_int* ptr, ptrdiff_t i, ptrdiff_t j, int n);

// Returns true if the array list (which is handled by the object handler
// pointed to by 'ptr') is empty (i.e. if the size of the array list is 0), and
// returns false otherwise.
bool AL_int_is_empty(const AL_int* ptr);

// Returns the index of the last occurrence of 'n' at the range of indices
// ['i', 'j') in the array list (which is handled by the object handler pointed
// to by 'ptr'), and returns -1 if 'n' is not present at the range of indices in
// the array list.
ptrdiff_t AL_int_last_index_of(const AL_int* ptr, ptrdiff_t i, ptrdiff_t j,
                               int n);

// Removes the element at the index 'i' from the array list (which is handled by
// the object handler pointed to by 'ptr'), shifting elements as required.
// May cause the program to terminate due to 'index out of bounds' or 'out of
// memory'.
void AL_int_remove(AL_int* ptr, ptrdiff_t i);

// Removes the elements at the range of indices ['i', 'j') from the array list
// (which is handled by the object handler pointed to by 'ptr'), shifting
// elements as required.
// May cause the program to terminate due to 'index out of bounds' or 'out of
// memory'.
void AL_int_remove_range(AL_int* ptr, ptrdiff_t i, ptrdiff_t j);

// Assigns 'n' to the element at the index 'i' in the array list (which is
// handled by the object handler pointed to by 'ptr').
// May cause the program to terminate due to 'index out of bounds'.
void AL_int_set(AL_int* ptr, ptrdiff_t i, int n);

// Returns the size of the array list (which is handled by the object handler
// pointed to by 'ptr').
ptrdiff_t AL_int_size(const AL_int* ptr);

// Copies the elements of the array list (which is handled by the object handler
// pointed to by 'ptr') to a malloc'ed array, and returns a pointer to its first
// element.
// May cause the program to terminate due to 'out of memory'.
int* AL_int_to_array(const AL_int* ptr);

////////////////////////////////////////////////////////////////////////////////

#endif
