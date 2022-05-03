// Incorporate 'Union by Rank' and 'Path Compression' before posting on
// Code Review Stack Exchange.
//
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
    size_t vertex_number;

    struct vertex* parent_vertex;
};

typedef struct vertex Vertex;


struct edge
{
    // u and v are the end vertices.
    size_t vertex_number_of_u, vertex_number_of_v;

    int weight;

    struct edge* next_edge;
};

typedef struct edge Edge;


struct graph
{
    size_t number_of_vertices;

    Vertex* vertices;

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
    scanf("%zu", &((ptr_g)->number_of_vertices));

    (ptr_g)->vertices = malloc(((ptr_g)->number_of_vertices) * sizeof (Vertex));
    if ((ptr_g)->vertices == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < (ptr_g)->number_of_vertices; i++)
    {
        (((ptr_g)->vertices)[i]).vertex_number = i;
        (((ptr_g)->vertices)[i]).parent_vertex = NULL;
    }

    (ptr_g)->head_edge = NULL;

    printf("\nEnter edges (q to quit) :-\n");
    printf("(1 2 5 means an edge between vertices 1 and 2 of weight 5)\n\n");

    while (true)
    {
        size_t vertex_number_of_u, vertex_number_of_v;
        int weight;

        // printf(">>> ");
        if (scanf("%zu", &(vertex_number_of_u)) != 1)
            break;
        scanf("%zu %d", &(vertex_number_of_v), &(weight));

        Edge* ptr_current_edge = malloc(sizeof (Edge));
        if (ptr_current_edge == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        (ptr_current_edge)->vertex_number_of_u = (vertex_number_of_u - 1);
        (ptr_current_edge)->vertex_number_of_v = (vertex_number_of_v - 1);
        (ptr_current_edge)->weight = weight;

        (ptr_current_edge)->next_edge = (ptr_g)->head_edge;
        (ptr_g)->head_edge = ptr_current_edge;
    }

}


void kruskal(Graph* ptr_g)
{

    // Simply print the edges constituting the MST, instead of storing them.

    for (size_t i = 0; i < (ptr_g)->number_of_vertices; i++)
        make_set(ptr_g, i);

    // merge_sort_singly_linked_list(&((ptr_g)->head_edge));

    printf("\nThe edges constituting an MST are :-\n\n");

    Edge* ptr_current_edge = (ptr_g)->head_edge;

    while (ptr_current_edge)
    {
        if (find_set(ptr_g, (ptr_current_edge)->vertex_number_of_u) !=
                find_set(ptr_g, (ptr_current_edge)->vertex_number_of_v))
        {
            printf("%zu %zu\n", ((ptr_current_edge)->vertex_number_of_u + 1),
                   ((ptr_current_edge)->vertex_number_of_v) + 1);

            union_set(ptr_g, (ptr_current_edge)->vertex_number_of_u,
                      (ptr_current_edge)->vertex_number_of_v);
        }

        ptr_current_edge = (ptr_current_edge)->next_edge;
    }

}


void make_set(Graph* ptr_g, size_t vertex_number)
{

    (((ptr_g)->vertices)[vertex_number]).parent_vertex =
        (((ptr_g)->vertices) + vertex_number);

}


size_t find_set(Graph* ptr_g, size_t vertex_number)
{

    size_t vertex_number_of_representative;

    Vertex* ptr_current_vertex = ((ptr_g)->vertices + vertex_number);

    while (true)
    {
        vertex_number_of_representative = (ptr_current_vertex)->vertex_number;

        if ((ptr_current_vertex)->parent_vertex == ptr_current_vertex)
            break;

        ptr_current_vertex = (ptr_current_vertex)->parent_vertex;
    }

    return vertex_number_of_representative;

}


void union_set(Graph* ptr_g, size_t u, size_t v)
{

    size_t vertex_number_of_representative_of_u = find_set(ptr_g, u);
    size_t vertex_number_of_representative_of_v = find_set(ptr_g, v);

    (((ptr_g)->vertices)[vertex_number_of_representative_of_u]).parent_vertex =
        (((ptr_g)->vertices) + vertex_number_of_representative_of_v);

}


void free_graph(Graph* ptr_g)
{

    free((ptr_g)->vertices);

    Edge* ptr_current_edge = (ptr_g)->head_edge;

    while (ptr_current_edge)
    {
        Edge* temp = (ptr_current_edge)->next_edge;
        free(ptr_current_edge);
        ptr_current_edge = temp;
    }

}
