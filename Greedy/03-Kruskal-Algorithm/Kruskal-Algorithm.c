// To be tested properly.

// A disjoint-set forest has been used for the vertices.

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


typedef struct edge
{

    // u and v are the vertex numbers of the end vertices of the edge
    // corresponding to this edge object.
    size_t u, v;

    // w is the weight of the edge corresponding to this edge object.
    int w;

    // ptr_next_edge points to the next edge object in the singly linked list.
    struct edge* ptr_next_edge;

} Edge;


typedef struct graph
{

    // n is the number of vertices in the graph corresponding to this graph
    // object.
    size_t n;

    // For the graph corresponding to this graph object, vertices stores void*
    // objects (representing vertex objects, sort of) such that the index of
    // every object is the corresponding vertex number, and every object points
    // to its parent object in the rooted tree.
    void** vertices;

    // ptr_head_edge points to the head edge object in the singly linked list.
    Edge* ptr_head_edge;

} Graph;


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

    return EXIT_SUCCESS;

}


void take_input_from_user_and_create_graph(Graph* ptr_g)
{

    size_t n;
    printf("Enter the number of vertices: ");
    scanf("%zu", &n);
    ((ptr_g)->n) = n;

    void** vertices = malloc(n * sizeof (void*));
    if (vertices == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->vertices) = vertices;

    for (size_t x = 0; x < n; x++)
        make_set(ptr_g, x);

    printf("\nEnter edges (q to quit) :-\n");
    printf("(1 2 5 means an edge between vertices 1 and 2 of weight 5)\n");
    printf("(Don't enter self-loops and parallel edges)\n\n");

    Edge* ptr_dummy_head_edge = malloc(sizeof (Edge));
    if (ptr_dummy_head_edge == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_dummy_head_edge)->ptr_next_edge) = NULL;

    Edge* ptr_previous_edge = ptr_dummy_head_edge;
    Edge* ptr_current_edge;

    while (true)
    {
        size_t u, v;
        int w;

        // printf(">>> ");
        if (scanf("%zu %zu %d", &u, &v, &w) != 3)
            break;

        ptr_current_edge = malloc(sizeof (Edge));
        if (ptr_current_edge == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        (ptr_current_edge)->u = (u - 1);
        (ptr_current_edge)->v = (v - 1);
        (ptr_current_edge)->w = w;

        (ptr_previous_edge)->ptr_next_edge = ptr_current_edge;
        (ptr_current_edge)->ptr_next_edge = NULL;

        ptr_previous_edge = ptr_current_edge;
    }

    (ptr_g)->ptr_head_edge = ((ptr_dummy_head_edge)->ptr_next_edge);
    free(ptr_dummy_head_edge);

}


void kruskal(Graph* ptr_g)
{

    // The edges constituting an MST will be printed directly, instead of being
    // stored.

    // The step consisting of the make_set() operations has been completed in
    // the take_input_from_user_and_create_graph() function.

    printf("\nThe edges constituting an MST are :-\n\n");

    merge_sort(&((ptr_g)->ptr_head_edge));

    Edge* ptr_current_edge = ((ptr_g)->ptr_head_edge);

    while (ptr_current_edge)
    {
        size_t u = ((ptr_current_edge)->u);
        size_t v = ((ptr_current_edge)->v);

        // root_u is the vertex number of the root vertex of the rooted tree
        // containing vertex u.
        size_t root_u = find_set(ptr_g, u);

        // root_v is the vertex number of the root vertex of the rooted tree
        // containing vertex v.
        size_t root_v = find_set(ptr_g, v);

        if (root_u != root_v)
        {
            printf("%zu %zu\n", (u + 1), (v + 1));

            union_set(ptr_g, root_u, root_v);
        }

        ptr_current_edge = ((ptr_current_edge)->ptr_next_edge);
    }

}


void make_set(Graph* ptr_g, size_t x)
{

    void** vertices = ((ptr_g)->vertices);

    vertices[x] = (void*) (vertices + x);

}


size_t find_set(Graph* ptr_g, size_t x)
{

    void** vertices = ((ptr_g)->vertices);

    void** ptr_current_vertex = (vertices + x);

    while (ptr_current_vertex != (void**) (*ptr_current_vertex))
        ptr_current_vertex = (void**) (*ptr_current_vertex);

    return (ptr_current_vertex - vertices);

}


void union_set(Graph* ptr_g, size_t root_u, size_t root_v)
{

    void** vertices = ((ptr_g)->vertices);

    vertices[root_u] = (void*) (vertices + root_v);

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

    Edge* ptr_dummy_head_edge = malloc(sizeof (Edge));
    if (ptr_dummy_head_edge == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);;
    }

    Edge* ptr_current_edge = ptr_dummy_head_edge;

    while ((ptr_current_edge_of_left) && (ptr_current_edge_of_right))
    {
        if ((ptr_current_edge_of_left)->w <=
                (ptr_current_edge_of_right)->w)
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
    else
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





/*

 * The Kruskal's Algorithm (The Minimum Spanning Tree Problem) :-

   Electronic circuit designs, such as the connections of logic gates on a
   breadboard, often need to make the pins of several components electrically
   equivalent by wiring them together.
   To interconnect a set of n pins, the designer can use an arrangement of
   (n - 1) wires, each connecting two pins.
   Of all such arrangements, the one that uses the least amount of wire is
   usually the most desirable.

   This problem can be modelled using a weighted, connected and undirected graph
   G = (V, E), where V is the set of pins, E is the set of all possible
   interconnections between pairs of pins, and for each edge (u, v) belonging to
   E, w(u, v) specifies the cost (amount of wire needed) to connect u and v.
   The goal is to find a minimum spanning tree of this graph, i.e. a spanning
   tree whose total weight is minimum among all possible spanning trees.

   Given a weighted, connected and undirected graph G = (V, E) having no self
   loops and no parallel edges, the Kruskal's algorithm produces a minimum
   spanning tree of G.
   [For a weighted, complete and undirected graph G, there are (|V| ^ (|V| - 2))
    different possible spanning trees]

   The optimal substructure property of this problem is as follows:
   Suppose that after running some algorithm, it is found that a minimum
   spanning tree of G is T.
   Then, for every subtree T' of T, T' must be a minimum spanning tree of the
   corresponding subgraph G' of G consisting of those vertices present in T' and
   all edges of G between those vertices.

   If this problem is solved using dynamic programming, then the overlapping
   subproblems property of this problem is as follows :-
   Every dynamic programming algorithm checking all possible spanning trees
   will have to examine the same subtrees when trying to build different
   spanning trees multiple times.
   Solving the minimum spanning tree problem using dynamic programming is an
   overkill, as the greedy approach results in much more efficient algorithms.


   In the Kruskal's algorithm, a disjoint-set data structure (efficiently
   implemented as a disjoint-set forest with the union-by-rank and the
   path-compression heuristics) is maintained whose disjoint sets consist of the
   vertices belonging to the given graph.
   At the beginning, there are |V| disjoint sets, such that every set consists
   of a single vertex.
   In every iteration, a lowest-weight edge between two vertices belonging to
   different sets is added to the set A of edges constituting an MST.
   Consequently, the two sets containing the two vertices are combined to form a
   a new set, with the previous two sets getting destroyed.
   After all edges have been processed (or after (|V| - 1) edges have been added
   to A), the algorithm stops and A consists of the edges forming an MST.
   [The disjoint sets of vertices should be thought of as separate, smaller
    trees consisting of the corresponding vertices.
    Thus, if in any iteration a lowest-weight edge between two vertices
    belonging to the same set is found, then that edge is skipped, as adding
    that edge to A would make the graph formed by the edges of A cyclic.]

   In the Kruskal's algorithm, after every iteration, the edges selected so far
   may or may not form a tree.


   The operation MAKE-SET(v) creates a new set consisting only of vertex v and
   makes v the representative vertex of that set.
   The operation FIND-SET(v) returns the representative vertex of the set
   containing vertex v.
   The operation UNION(u, v) combines the two sets containing vertex u and
   vertex v, respectively, to form a new set, makes some vertex in that set its
   representative, and destroys the previous two sets.


   MST-KRUSKAL(G, w) --------------------------------------------> O(|E| log|V|)

   01. A = phi (empty set)
   02. for each vertex v belonging to G.V
   03.     MAKE-SET(v)
   04. create a list of the edges belonging to G.E
   05. sort the list of the edges in non-decreasing order by weight w
   06. for each edge (u, v) taken from the sorted list in order
   07.     if FIND-SET(u) != FIND-SET(v)
   08.         add (u, v) to A
   09.         UNION(u, v)
   10. return A

   Assuming a disjoint-set forest implementation,
   (1) Initializing the set A in line 01 takes O(1) time.
   (2) Creating the list in line 04 takes either O(1) or O(|E|) time.
   (3) Sorting the list in line 05 takes O(|E| log|E|) time.
   (4) All MAKE-SET, FIND-SET and UNION operations from lines 02-03 and 06-09
       together take O((|V| + |E|) alpha(|V|)) time, where alpha is a very
       slowly growing function due to the heuristics.
   Since G is connected, therefore |E| >= (|V| - 1), and so the disjoint-set
   operations take O(|E| alpha(|V|)) time.
   Moreover, since alpha(|V|) = O(log |V|) = O(log |E|), the total running time
   of the Kruskal's algorithm becomes O(|E| log|E|).
   Since the graph doesn't contain any self loops and parallel edges, therefore
   |E| < (|V| ^ 2), making log|E| = O(log|V|).
   So, the running time can be restated as O(|E| log|V|).

 */
