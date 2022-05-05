// This program uses a different way to create a singly linked list, in order to
// avoid the if (ptr_head_node == NULL) check in every iteration.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define LIST_SIZE 100000
#define LIST_MIN -10
#define LIST_MAX 10


struct node
{
    int num;
    struct node* ptr_next_node;
};

typedef struct node Node;


int rand_int(int, int);

// Stable sort.
void merge_sort(Node**);
Node* find_middle_node(Node*);
void merge(Node**, Node*, Node*);


int main(void)
{

    srand((unsigned) time(NULL));

    Node* ptr_dummy_head_node = calloc(1, sizeof (Node));
    if (ptr_dummy_head_node == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        return EXIT_FAILURE;
    }

    Node* ptr_previous_node = ptr_dummy_head_node;
    Node* ptr_current_node;

    for (int i = 0; i < LIST_SIZE; i++)
    {
        ptr_current_node = (Node*) malloc(sizeof (Node));
        if (ptr_current_node == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            return EXIT_FAILURE;
        }

        (ptr_current_node)->num = rand_int(LIST_MIN, LIST_MAX);

        (ptr_previous_node)->ptr_next_node = ptr_current_node;
        (ptr_current_node)->ptr_next_node = NULL;

        ptr_previous_node = ptr_current_node;
    }

    Node* ptr_head_node = ((ptr_dummy_head_node)->ptr_next_node);
    free(ptr_dummy_head_node);

    if (ptr_head_node)
    {
        merge_sort(&(ptr_head_node));

        bool sorting_is_successful = true;

        ptr_previous_node = ptr_head_node;
        ptr_current_node = ((ptr_head_node)->ptr_next_node);

        while (ptr_current_node)
        {
            if (((ptr_previous_node)->num) > ((ptr_current_node)->num))
            {
                sorting_is_successful = false;
                break;
            }

            ptr_previous_node = ptr_current_node;
            ptr_current_node = ((ptr_current_node)->ptr_next_node);
        }

        if (sorting_is_successful)
            printf("Success\n");
        else
            printf("Failure\n");
    }

    while (ptr_head_node)
    {
        Node* ptr_temp_node = ((ptr_head_node)->ptr_next_node);
        free(ptr_head_node);
        ptr_head_node = ptr_temp_node;
    }

    return EXIT_SUCCESS;

}


int rand_int(int a, int b)
{
    size_t n = ((size_t) b - (size_t) a + (size_t) 1);
    size_t rem = (((size_t) RAND_MAX + (size_t) 1) % n);

    size_t x;
    do
    {
        x = (size_t) rand();
    }
    while (x >= (((size_t) RAND_MAX + (size_t) 1) - rem));

    return (int) ((size_t) a + (x % n));
}


void merge_sort(Node** ptr_ptr_head_node)
{

    if ((*ptr_ptr_head_node) && ((*ptr_ptr_head_node)->ptr_next_node))
    {
        Node* ptr_middle_node = find_middle_node(*ptr_ptr_head_node);

        Node* ptr_head_node_of_left = *ptr_ptr_head_node;

        Node* ptr_head_node_of_right = ((ptr_middle_node)->ptr_next_node);
        (ptr_middle_node)->ptr_next_node = NULL;

        merge_sort(&(ptr_head_node_of_left));
        merge_sort(&(ptr_head_node_of_right));

        merge(ptr_ptr_head_node, ptr_head_node_of_left, ptr_head_node_of_right);
    }

}


Node* find_middle_node(Node* ptr_head_node)
{

    Node* slow_pointer = ptr_head_node;
    Node* fast_pointer = ptr_head_node;

    while (((fast_pointer)->ptr_next_node) &&
               (((fast_pointer)->ptr_next_node)->ptr_next_node))
    {
        slow_pointer = ((slow_pointer)->ptr_next_node);
        fast_pointer = (((fast_pointer)->ptr_next_node)->ptr_next_node);
    }

    return slow_pointer;

}


void merge(Node** ptr_ptr_head_node, Node* ptr_current_node_of_left,
           Node* ptr_current_node_of_right)
{

    Node* ptr_dummy_head_node = calloc(1, sizeof (Node));
    if (ptr_dummy_head_node == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);;
    }

    Node* ptr_current_node = ptr_dummy_head_node;

    while ((ptr_current_node_of_left) && (ptr_current_node_of_right))
    {
        if ((ptr_current_node_of_left)->num <= (ptr_current_node_of_right)->num)
        {
            (ptr_current_node)->ptr_next_node = ptr_current_node_of_left;

            ptr_current_node_of_left =
                ((ptr_current_node_of_left)->ptr_next_node);
        }

        else
        {
            (ptr_current_node)->ptr_next_node = ptr_current_node_of_right;

            ptr_current_node_of_right =
                ((ptr_current_node_of_right)->ptr_next_node);
        }

        ptr_current_node = ((ptr_current_node)->ptr_next_node);
    }

    if (ptr_current_node_of_left)
        (ptr_current_node)->ptr_next_node = ptr_current_node_of_left;
    else
        (ptr_current_node)->ptr_next_node = ptr_current_node_of_right;

    *ptr_ptr_head_node = ((ptr_dummy_head_node)->ptr_next_node);
    free(ptr_dummy_head_node);

}
