#include <iostream>

#include "Graph.hpp"

int main() {
    auto source = new graph<int>(5, false);

    source->add_edge(0, 1, 2);
    source->add_edge(1, 0, 2);
    source->add_edge(0, 2, 3);
    source->add_edge(1, 2, 4);
    source->add_edge(3, 4, 5);
    source->add_edge(3, 2, 6);
    std::cout << source << "\n\n\nIs empty: " <<  source->empty() << "\nElements quantity: " << source->get_elements_quantity() << "\nWeight vertex 0 1: " << source->get_edge_weight(0, 1);

    std::cout << "\n\n\n" << source->find_shortest_path_djkstra(2) << "\n\n\n";

    return 0;
}
