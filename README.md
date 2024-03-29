# Graph

## Task
The task is to implement **Graph** data structure and basic algorithms. 

## Modifiers
**add_edge** take two vertexes and create an edge with the given weight-value.  
**delete_edge** take two vertexes and delete an edge between them.  
**add_vertex** add a nonadjacent vertex to the graph.  
**delete_vertex** delete last vertex with all edges incident to it.  
**get_edge_weight** take two vertexes and return weight of the edge between them.  
**find_shortest_path_djkstra** take an vertex index and find the shortest path from all another vertexes.  
**get_adjacency_matrix** return the adjency matrix of the current graph.  
**find_all_shortest_path_wallsher** return the shortest paths matrix.  
**find_minimal_spanning_tree** return sequence of vertexes (incoming - outgoing vertex) - it's like a sequence of graph edges. This sequence of graph edges is minimal spanning tree for this graph.  
**breadth_first_search** return lengths of the smallest paths sequence for the given vertex in unweighted graph.  
**depth_first_search** traverse graph and mark all visited vertexes in boolean sequence.  
**find_connected_components** return sequence of sequences(sequence of connected components) with marked vertexes.  
**topological_sort** return the ordered sequence of vertexes( *topological order*).  

## Based on
The data organization type of data structure **Graph** is an adjacency matrix.  
The basic value of this matrix is the weight of the vertex in graph.  
I encapsulated the analog of the vector into Graph that I had already developed([Sequence](https://github.com/VanyushaDoronin/Sequence)).

## Graph theory basics

### Introduction

The are 3 basic types for **graphs**: *directed graph*, *undirected graph*, *metagraph*.  
*V* - finite set of vertexes, *U* - finite set of edges. Graph **G** = <*V*, *U*>.  
**Undirected graph**  
**G** = <*V, U*> $$(v_{i}, v_{j}) = (v_{j}, v_{i}), - graph edge$$ $$(v_{i}, v_{i}) - loop$$  

**Directed graph**  
**G** = <*V, U*> $$(v_{i}, v_{j}) \neq (v_{j}, v_{i}), - arc$$ $$(v_{i}, v_{i}) - loop$$  

### How to set graph

**Adjacency matrix**
$$a(i,j) =0:(v_{i}, v_{j})\notin U$$
$$a(i,j) =1:(v_{i}, v_{j})\in U$$

**Adjacency matrix directed graph**
$$a(i,j) =0:(v_{i}, v_{j})\notin U$$
$$a(i,j) =1:(v_{i}, v_{j})\in U$$

**Adjacency list**  
It's one way to represent a graph as a collection of vertex lists.  
Each vertex of the graph corrensponds to a list consisting of the *"neighbors"* of this vertex.  

### Basic terms
**Vertex degree** is quantity of edges incident to this vertex.  

**Route** is a vertex sequence:
$$v_{i},v_{1} ... v_{n}$$

**Route** is a **chain** if:
$$\forall i, j\in [1, n] : i \neq j \Rightarrow u_{i} \neq u_{j}$$

**Path** is the shortest distance between two vertexes.
$$(v_{i}, v_{j}) \notin U \Rightarrow d(v_{i}, v_{j}) = ∞$$

### Operations
**Edge deletion**  
$$G<V,U> \Rightarrow G <\acute{V}, \acute{U}>$$
$$\acute{U} = U\smallsetminus u$$
$$\acute{V} = V$$

**Vertex deletion**  
$$G<V,U> \Rightarrow G <\acute{V}, \acute{U}>$$
$$\acute{V} = V\smallsetminus v$$
$$\acute{U} = U\bigcap_{}^{}\acute{V}×\acute{V}$$

## Breadth-first search
**The problem** is to find path with the smallest length in unweighted graph( *path* with the least number of edges).  
**Algorithm asymptotic** is $$O(n + m)$$
The algorithm itself can be understood as the process of "setting fire" to the graph: at the zero step, we set fire only to the vertex *start_pos*. At each next step, the fire from
each already burning vertex is spread to all its neighbors; in one iteration of the algorithm, the "ring of fire" is expanded by one in width (hence the name of the algorithm).  
We use *queue* (adapter on *array_sequence* with push(append) and pop(get_first->erase(0))) to mark vertexes which are already burning. Also we use boolean *sequence* to mark already
used vertexes and *sequence* of shortest lengths - our **result**.  
**How to apply**  
*1. Finding the shortest path in an unweighted graph*  
*2. Search for connectivity components in a graph*  

## Depth-first search
**The problem** is to traverse graph.  
**Algorithm asymptotic** is $$O(n + m)$$
**How to apply**  
*1. Finding connected components*  
*2. Topological sorting*  
*3. Finding the bridges*  
### Graph theory elements
**Bridge**
is an edge, whose removal increase quantity of connected components.

## Finding connected components
**The problem** is to find all connected components.  
**Algorithm asymptotic** is $$O(n + m)$$
The algorithm splits the set of all vertexes into groups. Within each group we can build simple chain from each vertex to all others.  
In this algorithm we use depth first search by launching it from first vertex and set all true values in the boolean sequence, which we have obtained, are connected component.  
Then we start dfs with the next remaining vertex.  
### Graph theory elements
**Connected component**
is the maximal connected subgraph of the graph *G*.  
**Сonnected graph**
is a graph containing exactly one connected component. This means, that there is at least one chain between any pair of vertexes.  

## Topological sort
**The problem** is to change vertexes numbering according to the topoligical order in the directed graph.  
**Algorithm asymptotic** is $$O(n + m)$$
In this algorithm we use depth-first search by launching it from first vertex. Then in the end of depth-first search we prepend the vertex into vertexes sequence.  
This sequence is topologically ordered set of vertexes - solution of the problem.  
If our graph have a *cycle*, vertex sequence will remain in the original order.  
### Graph theory elements
**Topological sort**
is renumbering of the vertexes set so that each edge leads from a vertex with a smaller number to a vertex with a larger one.  
Topological sorting may not exist at all — if the graph contains *cycles*.  

## Djkstra algorithm
**The problem** is to find shortest paths from a given vertex to all another vertexes.  
**Algorithm asymptotic** is $$O(n^2 + m)$$
The algorithm itself consists of *n* iterations. At the next iteration we take the vertex with the smallest value **path_sequence[vertex]**.  
The vertex chosen by us in this iteration is marked as visited in boolean **visited_sequence[vertex]**.  
Then on this iteration we consider all edges coming from the vertex named **vertex** and for every vertex named *j* algorithm tries to make better value **path_sequence[j]**.  
It is worth noting that if not all vertexes of the graph are reachable from the vertex s, then the values **path_sequence[vertex]** will remain infinity( **SIZE_MAX_LOCAL**)  

## Wallsher algorithm
**The problem** is to find shortest path from every vertex to all another vertexes.  
**Algorithm asymptotic** is $$O(n^3)$$
The **key-idea** of this algorithm is to separate the process into phases.  
Let the iteration be at *k* phase. We need to rebuild the matrix in matching *(k+1)* phase and make better every **path_matrix[i][j]**.  
As in Dijkstra's algorithm, the formula on pseudocode is **path_matrix[i][j] = min(path_matrix[i][j], path_matrix[i][k] + path_matrix[k][j])**.  

## Prim's algorithm
**The problem** is to find minimal spanning tree for the inputed graph.  
**Algorithm asymptotic** is $$O(n^2 + m)$$
We have 4 sequences in this algorithm. **Spanning sequence** contains the value of the minimal weight of the edge from vertex *i*, **is_used** for checking inclusion
in the minimal spanning tree, **edge end** collects the end of edges containing in the **spanning sequence**, **spanning tree** to output our minimal spanning tree.  
Desired spanning tree is building by adding one edge with the minimal weight at a time.   
### Graph theory elements 
The minimal spanning tree is a tree without cycles based on vertexes of the main graph. It's easy to understand, that if our current graph has *n* vertexes, then our
spanning tree will contain *n* vertexes and *n - 1* edges. If the main graph has more than **1** *connected components*, we can't build spanning tree.  

## Bear
.  
┈┈╭━╱▔▔▔▔╲━╮┈┈┈  
┈┈╰╱╭▅╮╭▅╮╲╯┈┈┈  
╳┈┈▏╰┈▅▅┈╯▕┈┈┈┈  
┈┈┈╲┈╰━━╯┈╱┈┈╳┈  
┈┈┈╱╱▔╲╱▔╲╲┈┈┈┈  
┈╭━╮▔▏┊┊▕▔╭━╮┈╳  
┈┃┊┣▔╲┊┊╱▔┫┊┃┈┈  
┈╰━━━━╲╱━━━━╯┈╳  
