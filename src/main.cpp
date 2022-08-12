#include <iostream>

#include "Graph.hpp"

int main() {

    auto source = new graph<int>(5, false, SIZE_MAX_LOCAL);

    source->add_edge(0, 1, 2);
    source->add_edge(1, 0, 2);
    source->add_edge(0, 2, 3);
    source->add_edge(1, 2, 4);
    source->add_edge(3, 4, 5);
    source->add_edge(3, 2, 6);
    source->add_vertex();
    source->add_edge(0, 5, 11);
    source->add_edge(5, 4, 22);

    std::cout << source << "\n\n\nIs empty: " <<  source->empty() << "\nElements quantity: " << source->get_elements_quantity() << "\nWeight vertex 0 1: " << source->get_edge_weight(0, 1);
    
    std::cout << "\n\n\n" << source->get_adjency_matrix();
    std::cout << "\n\n\n" << source->find_shortest_path_djkstra(2) << "\n\n\n" << source->breadth_first_search(0) << "\n\n\n" << source->find_all_shortest_path_wallsher();

    std::cout << "\n\n\n" << source->find_minimal_spanning_tree() << "\n\n\n";

    return 0;
}
