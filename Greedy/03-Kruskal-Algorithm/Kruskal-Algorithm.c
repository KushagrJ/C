// A disjoint set forest has been used for the vertices.

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
    // x is the vertex number of this vertex.
    size_t x;

    // parent points to the parent vertex of this vertex in the rooted tree.
    struct vertex* parent;
};

typedef struct vertex Vertex;


struct edge
{
    // u and v are the vertex numbers of the end vertices of this edge.
    size_t u, v;

    // weight is the weight of this edge.
    int weight;

    // next points to the next edge in the singly linked list of the edges.
    struct edge* next;
};

typedef struct edge Edge;


struct graph
{
    // n is the number of vertices in the graph.
    size_t n;

    // vertices is an n-element array containing the vertex objects.
    Vertex* vertices;

    // head_edge points to the head edge in the singly linked list of the edges.
    Edge* head_edge;
};

typedef struct graph Graph;


void take_input_from_user_and_create_graph(Graph*);

void kruskal(Graph*);

void make_set(Graph*, size_t);
size_t find_set(Graph*, size_t);
void union_set(Graph*, size_t, size_t);

void merge_sort_singly_linked_list(Edge**);

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

    (ptr_g)->head_edge = NULL;

    printf("\nEnter edges (q to quit) :-\n");
    printf("(1 2 5 means an edge between vertices 1 and 2 of weight 5)\n\n");

    while (true)
    {
        size_t u, v;
        int weight;

        // printf(">>> ");
        if (scanf("%zu %zu %d", &(u), &(v), &(weight)) != 3)
            break;

        Edge* ptr_current_edge = malloc(sizeof (Edge));
        if (ptr_current_edge == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        (ptr_current_edge)->u = (u - 1);
        (ptr_current_edge)->v = (v - 1);
        (ptr_current_edge)->weight = weight;

        (ptr_current_edge)->next = (ptr_g)->head_edge;
        (ptr_g)->head_edge = ptr_current_edge;
    }

}


void kruskal(Graph* ptr_g)
{

    // The edges constituting an MST have directly been printed, instead of
    // being stored.

    // The step consisting of make_set() operations has been completed in the
    // take_input_from_user_and_create_graph() function.

    // merge_sort_singly_linked_list(&((ptr_g)->head_edge));

    printf("\nThe edges constituting an MST are :-\n\n");

    Edge* ptr_current_edge = (ptr_g)->head_edge;

    while (ptr_current_edge)
    {
        // root_u is the vertex number of the root vertex of the rooted tree
        // containing vertex number u.
        size_t root_u = find_set(ptr_g, (ptr_current_edge)->u);

        // root_v is the vertex number of the root vertex of the rooted tree
        // containing vertex number v.
        size_t root_v = find_set(ptr_g, (ptr_current_edge)->v);

        if (root_u != root_v)
        {
            printf("%zu %zu\n", ((ptr_current_edge)->u + 1),
                   ((ptr_current_edge)->v) + 1);

            union_set(ptr_g, root_u, root_v);
        }

        ptr_current_edge = (ptr_current_edge)->next;
    }

}


void make_set(Graph* ptr_g, size_t x)
{

    (((ptr_g)->vertices)[x]).parent = ((ptr_g)->vertices + x);

}


size_t find_set(Graph* ptr_g, size_t x)
{

    Vertex* ptr_current_vertex = ((ptr_g)->vertices + x);

    while ((ptr_current_vertex)->parent != ptr_current_vertex)
        ptr_current_vertex = (ptr_current_vertex)->parent;

    return (ptr_current_vertex)->x;

}


void union_set(Graph* ptr_g, size_t root_u, size_t root_v)
{

    (((ptr_g)->vertices)[root_u]).parent = ((ptr_g)->vertices + root_v);

}


void free_graph(Graph* ptr_g)
{

    free((ptr_g)->vertices);

    Edge* ptr_current_edge = (ptr_g)->head_edge;

    while (ptr_current_edge)
    {
        Edge* temp = (ptr_current_edge)->next;
        free(ptr_current_edge);
        ptr_current_edge = temp;
    }

}
