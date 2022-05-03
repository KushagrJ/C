// Incorporate 'Union by Rank' and 'Path Compression' before posting on
// Code Review Stack Exchange.
//
// Why does union by rank, i.e. making the root of the tree with fewer nodes
// point to the root of the tree with more nodes, increase efficiency?
// Understand the reason properly.

#include <stdio.h>
#include <stdlib.h>


struct edge
{
    // u is the vertex number of the first end vertex.
    size_t u;

    // v is the vertex number of the second end vertex.
    size_t v;

    int weight;

    struct edge* next_edge;
};

typedef struct edge Edge;


struct vertex
{
    size_t vertex_number;

    struct vertex* parent_vertex;
};

typedef struct vertex Vertex;


struct graph
{
    Edge* head_edge;

    size_t number_of_vertices;
    Vertex* vertices;
};

typedef struct graph Graph;


void take_input_from_user_and_create_graph(Graph*);
void kruskal(Graph*);
void free_graph(Graph*);


int main(void)
{

    Graph g;
    take_input_from_user_and_create_graph(&g);

    kruskal(&g);

    free_graph(&g);

    return 0;

}
