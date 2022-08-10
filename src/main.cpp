#include <iostream>

#include "Graph.hpp"

int main() {
    auto source = new graph<int>(5);

    source->add_edge(0, 1, 2);
    source->add_edge(0, 2, 3);
    source->add_edge(1, 2, 4);
    source->add_edge(3, 4, 5);
    //source->delete_edge(3, 4);

    std::cout << source << "\n\n\nIs empty: " <<  source->empty() << "\nElements quantity: " << source->get_elements_quantity();


    return 0;
}
