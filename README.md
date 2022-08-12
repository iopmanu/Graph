# Graph

## Task
The task is to implement **Graph** data structure and basic algorithms. 

## Modifiers
**add_edge** take two vertexes and create an edge with the given weight-value.  
**delete_edge** take two vertexes and delete and edge between them.  
**add_vertex** add a nonadjacent vertex to the graph.  
**delete_vertex** delete last vertex with all edges incident to it.  
**get_edge_weight** take two vertexes and return weight of the edge between them.  
**find_shortest_path_djkstra** take an vertex index and find the shortest path from all another vertexes.  
**get_adjency_matrix** return the adjency matrix of the current graph.  
**find_all_shortest_path_wallsher** return the shortest paths matrix.  
**find_minimal_spanning_tree** return sequence of vertexes (incoming - outgoing vertex) - it's like a sequence of graph edges. This sequence of graph edges is minimal spanning tree for this graph.  


## Based on
The data organization type of data structure **Graph** is an adjacency matrix.  
The basic value of this matrix is the weight of the vertex in graph.  
I encapsulated the analog of the vector into Graph that I had already developed([Sequence](https://github.com/VanyushaDoronin/Sequence)).

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
## Graph theory elements 
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
