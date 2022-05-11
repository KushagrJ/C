#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>


typedef struct vertex
{

    unsigned x;

    int key;

    unsigned pre;

    struct vertex** ptr_ptr_this_vertex;

} Vertex;


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

    Vertex* vertices;

    Vertex** min_priority_queue;

    unsigned heap_size;

    Edge** e;

} Graph;


void take_input_from_user_and_create_graph(Graph*);

int rand_int(int, int);

// min priority queue operations.
void insert(Graph*, unsigned);
void decrease_key(Graph*, unsigned, int);

void free_graph(Graph*);


int main(void)
{

    srand((unsigned) time(NULL));

    Graph g;
    take_input_from_user_and_create_graph(&g);

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

    Vertex* vertices = malloc(n * sizeof (Vertex));
    if (vertices == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->vertices) = vertices;

    for (unsigned x = 0; x < n; x++)
        (vertices[x]).key = INT_MAX;
    (vertices[r]).key = 0;

    Vertex** min_priority_queue = malloc(n * sizeof (Vertex*));
    if (min_priority_queue == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->min_priority_queue) = min_priority_queue;

    ((ptr_g)->heap_size) = 0;

    for (unsigned x = 0; x < n; x++)
        insert(ptr_g, x);

    Edge** e = calloc(n, sizeof (Edge*));
    if (e == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->e) = e;

    printf("\nEnter edges (q to quit) :-\n");
    printf("(1 2 5 means an edge from vertex 1 to vertex 2 of weight 5)\n\n");

    while (true)
    {
        unsigned u, v;
        int w;

        printf(">>> ");
        if (scanf("%u %u %d", &u, &v, &w) != 3)
            break;

        Edge* ptr_current_edge = malloc(sizeof (Edge));
        if (ptr_current_edge == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        (ptr_current_edge)->v = (v - 1);
        (ptr_current_edge)->w = w;

        (ptr_current_edge)->ptr_next_edge = e[u - 1];
        e[u - 1] = ptr_current_edge;
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


void insert(Graph* ptr_g, unsigned x)
{

    unsigned heap_size = ((ptr_g)->heap_size);

    if (heap_size == (ptr_g)->n)
    {
        fprintf(stderr, "Heap overflow\n");
        exit(EXIT_FAILURE);
    }

    Vertex** min_priority_queue = ((ptr_g)->min_priority_queue);
    Vertex* vertices = ((ptr_g)->vertices);

    int key = (vertices[x]).key;
    (vertices[x]).key = INT_MAX;

    min_priority_queue[heap_size] = (vertices + x);
    (vertices[x]).ptr_ptr_this_vertex = (min_priority_queue + heap_size);

    decrease_key(ptr_g, x, key);

    ((ptr_g)->heap_size)++;

}


void decrease_key(Graph* ptr_g, unsigned x, int key)
{

    Vertex** min_priority_queue = ((ptr_g)->min_priority_queue);
    Vertex* vertices = ((ptr_g)->vertices);

    if (key > (vertices[x]).key)
    {
        fprintf(stderr, "New key is greater than current key\n");
        exit(EXIT_FAILURE);
    }

    (vertices[x]).key = key;

    unsigned index = (((vertices[x]).ptr_ptr_this_vertex) - min_priority_queue);

    // This is the min heap's swim-up procedure.
    while (index > 0)
    {
        unsigned parent_index = ((index - 1) / 2);

        if (((min_priority_queue[index])->key) <
               ((min_priority_queue[parent_index])->key))
        {
            Vertex* temp = min_priority_queue[index];
            min_priority_queue[index] = min_priority_queue[parent_index];
            min_priority_queue[parent_index] = temp;

            (min_priority_queue[index])->ptr_ptr_this_vertex =
                (min_priority_queue + index);

            (min_priority_queue[parent_index])->ptr_ptr_this_vertex =
                (min_priority_queue + parent_index);

            index = parent_index;
        }

        else
        {
            break;
        }
    }

}


void free_graph(Graph* ptr_g)
{

    free((ptr_g)->vertices);
    free((ptr_g)->min_priority_queue);

    unsigned n = ((ptr_g)->n);
    Edge** e = ((ptr_g)->e);

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
