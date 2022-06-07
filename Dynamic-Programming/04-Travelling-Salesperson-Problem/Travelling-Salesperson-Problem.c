/*

 * The Travelling Salesperson Problem :-

   Given a weighted, directed/undirected and complete graph with all finite,
   non-negative edge weights, the aim is to find an optimal hamiltonian cycle.


   For a directed/undirected graph, a 'hamiltonian cycle' is a finite
   alternating sequence of vertices and directed/undirected edges starting and
   ending at the same vertex such that no directed/undirected edges are
   repeated, every vertex other than the starting (& ending) vertex is traversed
   exactly once and the starting (& ending) vertex is traversed exactly twice.

   Now, for a directed/undirected graph, let a 'tour' be a finite alternating
   sequence of vertices and directed/undirected edges starting and ending at the
   same vertex such that all directed/undirected edges and vertices may be
   repeated and every vertex is traversed at least once.
   [This definition of a tour differs from the one which is generally accepted]


   A common application of the travelling salesperson problem, besides a literal
   travelling salesperson wanting to sell items in n different locations, is the
   courier service, wherein a delivery executive is required to deliver items in
   n different locations, and would like to visit the locations in an order so
   as to minimize the total cost incurred by them, i.e. the delivery executive
   would like to make an optimal tour.
   [The costs, represented using edge weights, can mean distances, toll taxes,
    etc.]


   For eg., let the delivery executive start from location A, deliver items in
   locations B, C, D, ... , and end at location A.
   Let the locations be such that there exists at least one possible tour, i.e.
   every location is reachable from every other location.

   Let graph 1 represent the locations & the direct roads between them, and
   let the edge weights (i.e. the costs) be the lengths of these direct roads.
   This is the type of graph given as input in the shortest paths problems.
   [In case of multiple available direct roads (i.e. parallel edges), the one
    with the least cost is chosen]

   Generally, graph 1 wouldn't be a complete graph, as there need not be direct
   roads between every pair of locations.
   Moreover, for some locations A and B, a direct road may exist from A to B,
   but not from B to A (one-way road).
   [If graph 1 isn't a connected graph, then there is no possible tour]

   Now, let graph 2 be a complete graph representing the locations, with the
   edge weights being the shortest distances between the respective locations,
   found using some all-pairs shortest-paths algorithm.
   Since every location is reachable from every other location, therefore all of
   the edge weights of graph 2 are finite.

   The main difference between graphs 1 and 2 is that an edge from A to B in
   graph 1 means that there is a direct road from A to B, whereas an edge from
   A to B in graph 2 means that there may be a direct road from A to B, or the
   delivery executive may have to go through some other locations C, D, E, ...
   in order to go from A to B.
   In other words, graph 2 is only concerned with the distance that the delivery
   executive would have to travel in order to go from one location to another,
   without taking into account the actual path that they would have to follow.

 */
