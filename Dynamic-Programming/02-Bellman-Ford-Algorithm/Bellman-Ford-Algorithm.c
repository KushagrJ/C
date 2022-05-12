// To be tested properly.

// The user must enter the edges assuming that vertex numbering begins from 1.
// Internally, vertex numbering begins from 0.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


typedef struct edge
{

    // v is the vertex number of the end vertex of the edge corresponding to
    // this edge object.
    size_t v;

    // w is the weight of the edge corresponding to this edge object.
    int w;

    // ptr_next_edge points to the next edge object in the singly linked list.
    struct edge* ptr_next_edge;

} Edge;


typedef struct graph
{

    // e points to the adjacency list representation of the graph corresponding
    // to this graph object.
    Edge** e;

    // n is the number of vertices in the graph corresponding to this graph
    // object.
    size_t n;

    // s is the vertex number of the source vertex in the graph corresponding
    // to this graph object.
    size_t s;

    // For the graph corresponding to this graph object, dist stores the
    // shortest distance estimates from vertex s to the other vertices.
    int* dist;

    // For the graph corresponding to this graph object, pre stores shortest
    // path predecessors of the vertices.
    size_t* pre;

} Graph;


void take_input_from_user_and_create_graph(Graph*);
bool bellman_ford(Graph*);
void print_shortest_paths(Graph*);
void print_shortest_path_from_s_to_t(Graph*, size_t);
void free_graph(Graph*);


int main(void)
{

    Graph g;
    take_input_from_user_and_create_graph(&g);

    if (bellman_ford(&g))
        // print_shortest_paths(&g);
        ;
    else
        printf("\nError: Negative-weight cycle reachable from source exists\n");

    free_graph(&g);

    return 0;

}


void take_input_from_user_and_create_graph(Graph* ptr_g)
{

    size_t n;
    printf("Enter the number of vertices: ");
    scanf("%zu", &n);
    ((ptr_g)->n) = n;

    printf("Enter the source vertex (vertex numbering begins from 1): ");
    scanf("%zu", &((ptr_g)->s));
    ((ptr_g)->s)--;

    Edge** e = calloc(n, sizeof (Edge*));
    if (e == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->e) = e;

    int* dist = malloc(n * sizeof(int));
    if (dist == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->dist) = dist;

    size_t* pre = malloc(n * sizeof(size_t));
    if (pre == NULL)
    {
        fprintf(stderr, "Unsuccessful allocation\n");
        exit(EXIT_FAILURE);
    }
    ((ptr_g)->pre) = pre;

    printf("\nEnter edges (q to quit) :-\n");
    printf("(1 2 5 means an edge from vertex 1 to vertex 2 of weight 5)\n\n");

    while (true)
    {
        size_t u, v;
        int w;

        printf(">>> ");
        if (scanf("%zu %zu %d", &u, &v, &w) != 3)
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


bool bellman_ford(Graph* ptr_g)
{

    Edge** e = ((ptr_g)->e);
    size_t n = ((ptr_g)->n);
    size_t s = ((ptr_g)->s);
    int* dist = ((ptr_g)->dist);
    size_t* pre = ((ptr_g)->pre);

    for (size_t t = 0; t < n; t++)
        dist[t] = INT_MAX;
    dist[s] = 0;

    for (size_t k = 1; k <= (n - 1); k++)
    {
        int* temp_dist = malloc(n * sizeof (int));
        if (temp_dist == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        for (size_t x = 0; x < n; x++)
            temp_dist[x] = dist[x];

        for (size_t u = 0; u < n; u++)
        {
            Edge* ptr_current_edge = e[u];

            while (ptr_current_edge)
            {
                size_t v = ((ptr_current_edge)->v);
                int w = ((ptr_current_edge)->w);

                if ((temp_dist[u] != INT_MAX) &&
                       (temp_dist[v] > (temp_dist[u] + w)))
                {
                    dist[v] = (temp_dist[u] + w);
                    pre[v] = u;
                }

                ptr_current_edge = ((ptr_current_edge)->ptr_next_edge);
            }
        }

        print_shortest_paths(ptr_g);

        free(temp_dist);
    }

    for (size_t u = 0; u < n; u++)
    {
        Edge* ptr_current_edge = e[u];

        while (ptr_current_edge)
        {
            size_t v = ((ptr_current_edge)->v);
            int w = ((ptr_current_edge)->w);

            if ((dist[u] != INT_MAX) && (dist[v] > (dist[u] + w)))
            {
                return false;
            }

            ptr_current_edge = ((ptr_current_edge)->ptr_next_edge);
        }
    }

    return true;

}


void print_shortest_paths(Graph* ptr_g)
{

    size_t n = ((ptr_g)->n);
    size_t s = ((ptr_g)->s);
    int* dist = ((ptr_g)->dist);

    printf("\nShortest paths :-\n");

    for (size_t t = 0; t < n; t++)
    {
        if (dist[t] != INT_MAX)
        {
            printf("%zu to %zu (shortest distance = %3d): ", (s + 1), (t + 1),
                   dist[t]);
            print_shortest_path_from_s_to_t(ptr_g, t);
            putchar('\n');
        }

        else
        {
            printf("%zu to %zu (shortest distance = N/A): N/A\n", (s + 1),
                   (t + 1));
        }
    }

}


void print_shortest_path_from_s_to_t(Graph* ptr_g, size_t t)
{

    size_t s = ((ptr_g)->s);
    size_t* pre = ((ptr_g)->pre);

    if (s != t)
        print_shortest_path_from_s_to_t(ptr_g, pre[t]);

    printf("%zu ", (t + 1));

}


void free_graph(Graph* ptr_g)
{

    Edge** e = ((ptr_g)->e);
    size_t n = ((ptr_g)->n);
    int* dist = ((ptr_g)->dist);
    size_t* pre = ((ptr_g)->pre);

    for (size_t i = 0; i < n; i++)
    {
        Edge* ptr_current_edge = e[i];

        while (ptr_current_edge)
        {
            Edge* temp = (ptr_current_edge)->ptr_next_edge;
            free(ptr_current_edge);
            ptr_current_edge = temp;
        }
    }

    free(e);
    free(dist);
    free(pre);

}





/*

 * The Bellman-Ford Algorithm (The Single-Source Shortest-Paths Problem) :-

   Given a weighted, directed graph G with source vertex s and possibly negative
   edge weights, the Bellman-Ford algorithm returns a boolean value indicating
   whether there is a negative-weight cycle that is reachable from s.
   If there is no such cycle, the algorithm produces the shortest paths and
   their weights.
   If there is such a cycle, the algorithm indicates that no solution exists.


   The four-step sequence for the Bellman-Ford algorithm is described below :-

   (1) An optimal solution to the single source shortest paths problem consists
       of shortest paths (and their weights) from the source vertex s to every
       other vertex.

       The optimal substructre property of this problem is as follows:
       Suppose that after running some algorithm, it is found that a shortest
       path from s to t is (s -> v_1 -> v_2 -> ... -> v_n -> t).
       Then, for every intermediate vertex v_i, the path from s to v_i within
       the above path must also be a (not 'the') shortest path from s to v_i.
       This is because if there were a shorter path from s to v_i, then that
       path could've been substituted in the above path to get a shorter path
       from s to t, which leads to a contradiction.

       According to this algorithm, to find shortest paths from s to every other
       vertex, shortest paths from s to every other vertex consisting of less
       than or equal to 1 edge need to be found, then shortest paths from s to
       every other vertex consisting of less than or equal to 2 edges need to be
       found, and so on until shortest paths from s to every other vertex
       consisting of less than or equal to (|V| - 1) edges have been found.

       These shortest paths from s to every other vertex consisting of less than
       or equal to (|V| - 1) edges will be the final shortest paths.
       This is because a shortest path will always be a simple path, as if
       visiting a vertex more than once reduces the total weight of a path, then
       that vertex must be part of a negative-weight cycle, which is not allowed
       in this algorithm.
       [A zero-weight cycle may be included in order to get a shortest path
        using more than (|V| - 1) edges, but since removing that cycle will
        produce a path with the same shortest distance, therefore including a
        zero-weight cycle becomes redundant]

       Thus, a subproblem with respect to this algorithm means shortest paths
       from s to every other vertex consisting of less than or equal to k edges.

   (2) Let the vertex numbering in the graph begin with 0.

       Let dist_k[t] be the shortest distance from the source vertex s to the
       vertex t under the constraint that the corresponding path consists of
       less than or equal to k edges.

       For the full problem, the shortest distance from s to t is thus
       dist_(|V| - 1)[t].

       The recursive definition of the value of an optimal solution to this
       problem is as follows:
       dist_k[t] = the minimum value out of (1) dist_(k-1)[t] and (2) the
       minimum value of dist_(k-1)[v] + w[v][t] over all possible values of v
       (i.e. over all values of v such that there is an edge from v to t).

       The overlapping subproblems property of this problem is as follows:
       According to the above definition of the value of an optimal solution,
       to calculate dist_k[t], the values from dist_(k-1) are needed multiple
       times, and the same values from dist_(k-1) are used multiple times to
       calculate dist_k[t] for different values of t.

       To help construct an optimal solution during step 4, let pre[t] be the
       predecessor vertex of t in the corresponding shortest path.

   (3) BELLMAN-FORD(G, w, s, dist, pre) ---------------------> O(|V|^2 + |V||E|)

       01. for each vertex v belonging to G.V
       02.     dist[v] = infinity
       03.     pre[v] = NIL
       04. dist[s] = 0
       05. for k = 1 to (|G.V| - 1)
       06.     let temp_dist[|V|] be a new copy of the current dist table
       07.     for each edge (u, v) belonging to G.E
       08.         if temp_dist[v] > temp_dist[u] + w(u, v)
       09.             dist[v] = temp_dist[u] + w(u, v)
       10.             pre[v] = u
       11. for each edge (u, v) belonging to G.E
       12.     if dist[v] > dist[u] + w(u, v)
       13.         return FALSE
       14. return TRUE

       Traversing an adjacency list takes O(|V| + |E|) time.
       This is because the outer loop going over the vertices is executed O(|V|)
       times, regardless of the number of edges in the graph.
       Now, the inner loop going over the edges originating from the
       corresponding vertex is executed O(1 + deg(v)) times, where deg(v) is
       the degree of the current vertex being examined.
       [The 1 in O(1 + deg(v)) represents the additional constant work to be
        done for every vertex, i.e. reading the head pointer]
       Thus, for every vertex v, O(1 + deg(v)) time is required.
       Summing it all up, the total time taken to traverse an adjacency list is
       thus equal to O((1 + deg(v_1)) + (1 + deg(v_2)) + ... + (1 + deg(v_n)),
       i.e. O((1 + 1 + ... |V| times) + (deg(v_1) + deg(v_2) + ... + deg(v_n))),
       i.e. O(|V| + |E|).
       [It should be noted that one may also say that the time taken to traverse
        an adjacency list is O(|V| * |E|) at first glance, but O(|V| + |E|)
        gives a better view of the actual scanario.
        Even though O(|V| * |E|) is technically correct, as every O(1) algorithm
        is also O(n), O(n^2), and so on, but O(|V| + |E|) is better.]

       Immediately after the k-th iteration, shortest paths from s to every
       other vertex consisting of less than or equal to k edges are found.
       Thus, to find shortest paths from a single source vertex to every other
       vertex consisting of less than or equal to k edges, the Bellman-Ford
       algorithm can simply be stopped after k iterations.

       The crucial observation is that if after the termination of the algorithm
       it is found that 0 -> 2 -> 1 -> 4 is a shortest path, for example, then
       it can be guaranteed that this particular shortest path was obtained
       immediately after the 3-rd iteration itself.

       More generally, if an existing estimated shortest path is improved in the
       k-th iteration, then the resulting newly estimated shortest path will
       consist of exactly k edges, and not less.
       For eg., if a shortest path estimate for s = 0 and t = 4 is 0 -> 4
       immediately after the 1-st iteration, and if this estimate isn't improved
       immediately after the 2-nd iteration, then if this estimate is improved
       immediately after the 3-rd iteration, then the improved shortest path
       estimate cannot consist of 2 edges, and must consist of exactly 3 edges,
       such as 0 -> 2 -> 1 -> 4.
       This is because if the estimate 0 -> 4 could've been improved using 2
       edges, then this would've happened immediately after the 2-nd iteration
       itself.

       This algorithm runs for (|V| - 1) iterations, and all shortest paths are
       found immediately after the (|V| - 1)-th iteration.

       Now, if the |V|-th iteration still improves a shortest path estimate,
       then it can be guaranteed that a shortest path consisting of exactly
       |V| edges exists, which means that a negative-weight cycle reachable from
       the source vertex exists in the graph.
       This is because a zero-weight or a positive-weight cycle will never be
       used by this algorithm to improve an existing shortest path estimate.

       According to the optimal substructure property, since an optimal solution
       to a problem always consists of optimal solutions to its subproblems,
       therefore storing only optimal solutions to smaller problems is
       enough to construct optimal solutions to bigger problems, as combining
       non-optimal solutions to smaller problems can never lead to optimal
       solutions to bigger problems.

       When optimal solutions to smaller problems are found, only one of those
       multiple (possibly) optimal solutions having the same value is stored.
       Does the choice of optimal solution matter in this algorithm?
       [To be answered]

   (4) PRINT-SHORTEST-PATH-FROM-S-TO-T(G, s, t)
       (Assuming that pre[t] != NIL)

       1. if s != t
       2.     PRINT-SHORTEST-PATH-FROM-S-TO-T(G, s, pre[t])
       3. print t


 * There is another simpler variation of the Bellman-Ford algorithm, in which
   the shortest path estimates are updated serially.
   Actually, the algorithm described above also updates the shortest path
   estimates serially, but it does so in a way that the parallel update property
   is not violated (by using a temporary dist table in every iteration).
   In an actual improved version of parallel update, all edges must be processed
   parallely in one go, using advanced programming techniques.

   In the following serial update version, shortest paths consisting of more
   than k edges may also be found immediately after the k-th iteration.
   Thus, there is no well defined subproblem when the following serial update
   version of the Bellman-Ford algorithm is used.
   [The following serial update version probably shouldn't be considered as a
    dynamic programming algorithm, due to the lack of well defined subproblems]

       BELLMAN-FORD(G, w, s, dist, pre) ---------------------> O(|V|^2 + |V||E|)

       01. for each vertex v belonging to G.V
       02.     dist[v] = infinity
       03.     pre[v] = NIL
       04. dist[s] = 0
       05. for k = 1 to (|G.V| - 1)
       06.     for each edge (u, v) belonging to G.E
       07.         if dist[v] > dist[u] + w(u, v)
       08.             dist[v] = dist[u] + w(u, v)
       09.             pre[v] = u
       10. for each edge (u, v) belonging to G.E
       11.     if dist[v] > dist[u] + w(u, v)
       12.         return FALSE
       13. return TRUE

 */
