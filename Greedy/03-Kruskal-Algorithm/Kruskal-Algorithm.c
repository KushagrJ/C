// A disjoint set forest has been used for the vertex objects.

// Incorporate 'Union by Rank' and 'Path Compression' before posting on
// Code Review Stack Exchange.

// Why does union by rank, i.e. making the root of the tree with fewer nodes
// point to the root of the tree with more nodes, increase efficiency?
// Understand the reason properly.

// The user must enter the edges assuming that vertex numbering begins from 1.
// Internally, vertex numbering begins from 0.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct vertex
{
    // x is the vertex number of this vertex object.
    size_t x;

    // ptr_parent_vertex points to the parent vertex object of this vertex
    // object in the rooted tree.
    struct vertex* ptr_parent_vertex;
};

typedef struct vertex Vertex;


struct edge
{
    // u and v are the vertex numbers of the end vertices of this edge object.
    size_t u, v;

    // weight is the weight of this edge object.
    int weight;

    // ptr_next_edge points to the next edge object in the singly linked list of
    // the edge objects.
    struct edge* ptr_next_edge;
};

typedef struct edge Edge;


struct graph
{
    // n is the number of vertex objects in this graph.
    size_t n;

    // vertices is an n-element array containing the vertex objects.
    Vertex* vertices;

    // ptr_head_edge points to the head edge object in the singly linked list of
    // the edge objects.
    Edge* ptr_head_edge;
};

typedef struct graph Graph;


void take_input_from_user_and_create_graph(Graph*);

void kruskal(Graph*);

void make_set(Graph*, size_t);
size_t find_set(Graph*, size_t);
void union_set(Graph*, size_t, size_t);

void merge_sort(Edge**);
Edge* find_middle_edge(Edge*);
void merge(Edge**, Edge*, Edge*);

void free_graph(Graph*);


int main(void)
{

    Graph g;
    take_input_from_user_and_create_graph(&g);

    kruskal(&g);

    free_graph(&g);

    return 0;

}


void take_input_from_user_and_create_graph(Graph* ptr_g)
{

    printf("Enter the number of vertices: ");
    scanf("%zu", &((ptr_g)->n));

    (ptr_g)->vertices = malloc(((ptr_g)->n) * sizeof (Vertex));
    if ((ptr_g)->vertices == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    for (size_t x = 0; x < (ptr_g)->n; x++)
    {
        (((ptr_g)->vertices)[x]).x = x;
        make_set(ptr_g, x);
    }

    printf("\nEnter edges (q to quit) :-\n");
    printf("(1 2 5 means an edge between vertices 1 and 2 of weight 5)\n\n");

    Edge* ptr_dummy_head_edge = calloc(1, sizeof (Edge));
    if (ptr_dummy_head_edge == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    Edge* ptr_previous_edge = ptr_dummy_head_edge;
    Edge* ptr_current_edge;

    while (true)
    {
        size_t u, v;
        int weight;

        // printf(">>> ");
        if (scanf("%zu %zu %d", &(u), &(v), &(weight)) != 3)
            break;

        ptr_current_edge = malloc(sizeof (Edge));
        if (ptr_current_edge == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        (ptr_current_edge)->u = (u - 1);
        (ptr_current_edge)->v = (v - 1);
        (ptr_current_edge)->weight = weight;

        (ptr_previous_edge)->ptr_next_edge = ptr_current_edge;
        (ptr_current_edge)->ptr_next_edge = NULL;

        ptr_previous_edge = ptr_current_edge;
    }

    (ptr_g)->ptr_head_edge = ((ptr_dummy_head_edge)->ptr_next_edge);
    free(ptr_dummy_head_edge);

}


void kruskal(Graph* ptr_g)
{

    // The edges constituting an MST have directly been printed, instead of
    // being stored.

    // The step consisting of the make_set() operations has been completed in
    // the take_input_from_user_and_create_graph() function.

    printf("\nThe edges constituting an MST are :-\n\n");

    merge_sort(&((ptr_g)->ptr_head_edge));

    Edge* ptr_current_edge = ((ptr_g)->ptr_head_edge);

    while (ptr_current_edge)
    {
        // root_u is the vertex number of the root vertex object of the rooted
        // tree containing the vertex object whose vertex number is u.
        size_t root_u = find_set(ptr_g, (ptr_current_edge)->u);

        // root_v is the vertex number of the root vertex object of the rooted
        // tree containing the vertex object whose vertex number is v.
        size_t root_v = find_set(ptr_g, (ptr_current_edge)->v);

        if (root_u != root_v)
        {
            printf("%zu %zu\n", ((ptr_current_edge)->u) + 1,
                   ((ptr_current_edge)->v) + 1);

            union_set(ptr_g, root_u, root_v);
        }

        ptr_current_edge = ((ptr_current_edge)->ptr_next_edge);
    }

}


void make_set(Graph* ptr_g, size_t x)
{

    Vertex* vertices = ((ptr_g)->vertices);

    (vertices[x]).ptr_parent_vertex = (vertices + x);

}


size_t find_set(Graph* ptr_g, size_t x)
{

    Vertex* ptr_current_vertex = ((ptr_g)->vertices + x);

    while ((ptr_current_vertex)->ptr_parent_vertex != ptr_current_vertex)
        ptr_current_vertex = ((ptr_current_vertex)->ptr_parent_vertex);

    return (ptr_current_vertex)->x;

}


void union_set(Graph* ptr_g, size_t root_u, size_t root_v)
{

    Vertex* vertices = ((ptr_g)->vertices);

    (vertices[root_u]).ptr_parent_vertex = (vertices + root_v);

}


void merge_sort(Edge** ptr_ptr_head_edge)
{

    if ((*ptr_ptr_head_edge) && ((*ptr_ptr_head_edge)->ptr_next_edge))
    {
        Edge* ptr_middle_edge = find_middle_edge(*ptr_ptr_head_edge);

        Edge* ptr_head_edge_of_left = *ptr_ptr_head_edge;

        Edge* ptr_head_edge_of_right = ((ptr_middle_edge)->ptr_next_edge);
        (ptr_middle_edge)->ptr_next_edge = NULL;

        merge_sort(&(ptr_head_edge_of_left));
        merge_sort(&(ptr_head_edge_of_right));

        merge(ptr_ptr_head_edge, ptr_head_edge_of_left, ptr_head_edge_of_right);
    }

}


Edge* find_middle_edge(Edge* ptr_head_edge)
{

    Edge* slow_pointer = ptr_head_edge;
    Edge* fast_pointer = ptr_head_edge;

    while (((fast_pointer)->ptr_next_edge) &&
               (((fast_pointer)->ptr_next_edge)->ptr_next_edge))
    {
        slow_pointer = ((slow_pointer)->ptr_next_edge);
        fast_pointer = (((fast_pointer)->ptr_next_edge)->ptr_next_edge);
    }

    return slow_pointer;

}


void merge(Edge** ptr_ptr_head_edge, Edge* ptr_current_edge_of_left,
           Edge* ptr_current_edge_of_right)
{

    Edge* ptr_dummy_head_edge = calloc(1, sizeof (Edge));
    if (ptr_dummy_head_edge == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);;
    }

    Edge* ptr_current_edge = ptr_dummy_head_edge;

    while ((ptr_current_edge_of_left) && (ptr_current_edge_of_right))
    {
        if ((ptr_current_edge_of_left)->weight <=
                (ptr_current_edge_of_right)->weight)
        {
            (ptr_current_edge)->ptr_next_edge = ptr_current_edge_of_left;

            ptr_current_edge_of_left =
                ((ptr_current_edge_of_left)->ptr_next_edge);
        }

        else
        {
            (ptr_current_edge)->ptr_next_edge = ptr_current_edge_of_right;

            ptr_current_edge_of_right =
                ((ptr_current_edge_of_right)->ptr_next_edge);
        }

        ptr_current_edge = ((ptr_current_edge)->ptr_next_edge);
    }

    if (ptr_current_edge_of_left)
        (ptr_current_edge)->ptr_next_edge = ptr_current_edge_of_left;
    else if (ptr_current_edge_of_right)
        (ptr_current_edge)->ptr_next_edge = ptr_current_edge_of_right;

    *ptr_ptr_head_edge = ((ptr_dummy_head_edge)->ptr_next_edge);
    free(ptr_dummy_head_edge);

}


void free_graph(Graph* ptr_g)
{

    free((ptr_g)->vertices);

    Edge* ptr_current_edge = ((ptr_g)->ptr_head_edge);

    while (ptr_current_edge)
    {
        Edge* temp = ((ptr_current_edge)->ptr_next_edge);
        free(ptr_current_edge);
        ptr_current_edge = temp;
    }

}
