# Graph

## Task
The task is to implement **Graph** data structure and basic algorithms. 

## Modifiers
**add_edge** take two vertexes and create an edge with the given weight-value.  
**delete_edge** take two vertexes and delete and edge between them.  
**find_shortest_path_djkstra** take an vertex index and find the shortest path from all another vertexes.  

## Based on
The data organization type of data structure **Graph** is an adjacency matrix.  
The basic value of this matrix is the weight of the vertex in graph.  
I encapsulated the analog of the vector into SortedSequence that I had already developed([Sequence](https://github.com/VanyushaDoronin/Sequence)).

## Djkstra algorithm
**The problem** is to find shortest paths from a given vertex to all another vertexes.  
**Algorithm asymptotic** is $$O(n^2 + m)$$
The algorithm itself consists of **n** iterations. At the next iteration we take the vertex with the smallest value **path_sequence[vertex]**.  
The vertex chosen by us in this iteration is marked as visited in boolean **visited_sequence[vertex]**.  
Then on this iteration we consider all edges coming from the vertex named **vertex** and for every vertex named **j** algorithm tries to make better value **path_sequence[j]**.  
It is worth noting that if not all vertexes of the graph are reachable from the vertex s, then the values **path_sequence[vertex]** will remain infinity( **SIZE_MAX_LOCAL**)  

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
