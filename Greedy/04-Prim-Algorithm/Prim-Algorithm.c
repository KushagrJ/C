#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>


typedef struct edge
{

    unsigned v;

    int w;

    struct edge* ptr_next_edge;

} Edge;


typedef struct graph
{

    unsigned n;

    unsigned r;

    void** vertices;

    int* key;

    unsigned* pre;

    void** min_priority_queue;

    unsigned heap_size;

    Edge** e;

} Graph;


void take_input_from_user_and_create_graph(Graph*);

int rand_int(int, int);

void prim(Graph*);

// min priority queue operations.
void insert(Graph*, unsigned);
void decrease_key(Graph*, unsigned, int);
unsigned extract_min(Graph*);

void free_graph(Graph*);


int main(void)
{

    srand((unsigned) time(NULL));

    Graph g;
    take_input_from_user_and_create_graph(&g);

    prim(&g);

    free_graph(&g);

    return 0;

}


void take_input_from_user_and_create_graph(Graph* ptr_g)
{

    unsigned n;
    printf("Enter the number of vertices: ");
    scanf("%u", &n);
    ((ptr_g)->n) = n;

    unsigned r = rand_int(0, (n - 1));
    ((ptr_g)->r) = r;

    void** vertices = malloc(n * sizeof (void*));
    if (vertices == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->vertices) = vertices;

    int* key = malloc(n * sizeof (int));
    if (key == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->key) = key;

    unsigned* pre = malloc(n * sizeof (unsigned));
    if (pre == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->pre) = pre;

    void** min_priority_queue = malloc(n * sizeof (void*));
    if (min_priority_queue == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->min_priority_queue) = min_priority_queue;

    ((ptr_g)->heap_size) = 0;

    Edge** e = calloc(n, sizeof (Edge*));
    if (e == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->e) = e;

    printf("\nEnter edges (q to quit) :-\n");
    printf("(1 2 5 means an edge between vertices 1 and 2 of weight 5)\n");
    printf("(Don't enter self-loops and parallel edges)\n\n");

    while (true)
    {
        unsigned u, v;
        int w;

        printf(">>> ");
        if (scanf("%u %u %d", &u, &v, &w) != 3)
            break;

        // current_edge_1 is directed from u to v.
        Edge* ptr_current_edge_1 = malloc(sizeof (Edge));
        if (ptr_current_edge_1 == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        ((ptr_current_edge_1)->v) = (v - 1);
        ((ptr_current_edge_1)->w) = w;

        ((ptr_current_edge_1)->ptr_next_edge) = e[u - 1];
        e[u - 1] = ptr_current_edge_1;

        // current_edge_2 is directed from v to u.
        Edge* ptr_current_edge_2 = malloc(sizeof (Edge));
        if (ptr_current_edge_2 == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        ((ptr_current_edge_2)->v) = (u - 1);
        ((ptr_current_edge_2)->w) = w;

        ((ptr_current_edge_2)->ptr_next_edge) = e[v - 1];
        e[v - 1] = ptr_current_edge_2;
    }

}


// (b - a) must be a non-negative integer less than or equal to RAND_MAX.
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


void prim(Graph* ptr_g)
{

    // Remove all redundant variable definitions.
/**/    unsigned n = ((ptr_g)->n);
/**/    unsigned r = ((ptr_g)->r);
    void** vertices = ((ptr_g)->vertices);
/**/    int* key = ((ptr_g)->key);
    unsigned* pre = ((ptr_g)->pre);
    void** min_priority_queue = ((ptr_g)->min_priority_queue);
    unsigned heap_size = ((ptr_g)->heap_size);
    Edge** e = ((ptr_g)->e);

    for (unsigned x = 0; x < n; x++)
        key[x] = INT_MAX;
    key[r] = 0;

    for (unsigned x = 0; x < n; x++)
        insert(ptr_g, x);

}


void insert(Graph* ptr_g, unsigned x)
{

    unsigned n = ((ptr_g)->n);
    unsigned* ptr_heap_size = &((ptr_g)->heap_size);

    if (*ptr_heap_size >= n)
    {
        fprintf(stderr, "Heap overflow\n");
        exit(EXIT_FAILURE);
    }

    void** vertices = ((ptr_g)->vertices);
    int* key = ((ptr_g)->key);
    void** min_priority_queue = ((ptr_g)->min_priority_queue);

    (*ptr_heap_size)++;

    int new_key_of_x = key[x];
    key[x] = INT_MAX;

    vertices[x] = (void*) (min_priority_queue + (*ptr_heap_size - 1));
    min_priority_queue[*ptr_heap_size - 1] = (void*) (vertices + x);

    decrease_key(ptr_g, x, new_key_of_x);

}


void decrease_key(Graph* ptr_g, unsigned x, int new_key_of_x)
{

    int* key = ((ptr_g)->key);

    if (new_key_of_x > key[x])
    {
        fprintf(stderr, "New key is greater than current key\n");
        exit(EXIT_FAILURE);
    }

    void** vertices = ((ptr_g)->vertices);
    void** min_priority_queue = ((ptr_g)->min_priority_queue);

    key[x] = new_key_of_x;

    // This is the min heap's swim-up procedure.

    unsigned index = (((void**) (vertices[x])) - min_priority_queue);

    while (index > 0)
    {
        unsigned parent_index = ((index - 1) / 2);

        unsigned parent_x =
            (((void**) (min_priority_queue[parent_index])) - vertices);

        if (key[x] < key[parent_x])
        {
            vertices[parent_x] = ((void*) (min_priority_queue + index));
            min_priority_queue[index] = ((void*) (vertices + parent_x));

            vertices[x] = ((void*) (min_priority_queue + parent_index));
            min_priority_queue[parent_index] = ((void*) (vertices + x));

            index = parent_index;
        }

        else
        {
            break;
        }
    }

}


unsigned extract_min(Graph* ptr_g)
{

    unsigned* ptr_heap_size = &((ptr_g)->heap_size);

    if (*ptr_heap_size < 1)
    {
        fprintf(stderr, "Heap underflow\n");
        exit(EXIT_FAILURE);
    }

    void** vertices = ((ptr_g)->vertices);
    int* key = ((ptr_g)->key);
    void** min_priority_queue = ((ptr_g)->min_priority_queue);

    (*ptr_heap_size)--;

    unsigned min_x = (((void**) (min_priority_queue[0])) - vertices);
    vertices[min_x] = NULL;

    min_priority_queue[0] = min_priority_queue[*ptr_heap_size];
    *((void**) (min_priority_queue[0])) = ((void*) (min_priority_queue));

    // This is the min heap's sift-down procedure.

    unsigned parent_x = (((void**) (min_priority_queue[0])) - vertices);
    unsigned parent_index = 0;

    while (true)
    {
        unsigned left_child_index = ((2 * parent_index) + 1);
        unsigned left_child_x =
            (((void**) (min_priority_queue[left_child_index])) - vertices);

        unsigned right_child_index = ((2 * parent_index) + 2);
        unsigned right_child_x =
            (((void**) (min_priority_queue[right_child_index])) - vertices);

        unsigned largest_index = parent_index;
        unsigned largest_x = parent_x;

        if ((left_child_index < *ptr_heap_size) &&
               (key[left_child_x] < key[largest_x]))
        {
            largest_index = left_child_index;
            largest_x = left_child_x;
        }

        if ((right_child_index < *ptr_heap_size) &&
               (key[right_child_x] < key[largest_x]))
        {
            largest_index = right_child_index;
            largest_x = right_child_x;
        }

        if (largest_index == parent_index)
            break;

        vertices[parent_x] = ((void*) (min_priority_queue + largest_index));
        min_priority_queue[largest_index] = ((void*) (vertices + parent_x));

        vertices[largest_x] = ((void*) (min_priority_queue + parent_index));
        min_priority_queue[parent_index] = ((void*) (vertices + largest_x));

        parent_index = largest_index;
    }

    return min_x;

}


void free_graph(Graph* ptr_g)
{

    unsigned n = ((ptr_g)->n);
    Edge** e = ((ptr_g)->e);

    free((ptr_g)->vertices);
    free((ptr_g)->key);
    free((ptr_g)->pre);
    free((ptr_g)->min_priority_queue);

    for (unsigned i = 0; i < n; i++)
    {
        Edge* ptr_current_edge = e[i];

        while (ptr_current_edge)
        {
            Edge* temp = ((ptr_current_edge)->ptr_next_edge);
            free(ptr_current_edge);
            ptr_current_edge = temp;
        }
    }

    free(e);

}
