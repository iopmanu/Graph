#include <iostream>
#include <vector>

#include "Graph.hpp"

void testing_djkstra();
void testing_bfs();
void testing_wallsher();
void testing_spanning_tree();
void testing_connected_components();
void testing_topological();

int main() {

    testing_djkstra();
    testing_bfs();
    testing_wallsher();
    testing_spanning_tree();
    testing_connected_components();
    testing_topological();

    auto source = new graph<int>(5, true, SIZE_MAX_LOCAL);

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
    
    auto adjency_matrix = source->get_adjency_matrix();
    std::cout << "\n\n\n" << adjency_matrix;
    delete adjency_matrix;

    auto djkstra = source->find_shortest_path_djkstra(2);
    auto wallsher = source->find_all_shortest_path_wallsher();
    auto breadth_search = source->breadth_first_search(2);

    std::cout << "Djkstra:\n\n\n" << djkstra << "Wallsher\n\n\n" << breadth_search << "Breadth\n\n\n" << wallsher;
    delete djkstra;
    delete wallsher;
    delete breadth_search;

    auto spanning = source->find_minimal_spanning_tree();
    std::cout << "\nSpanning\n\n" << spanning << "\n\n\n";
    delete spanning;
    
    auto to_out = new array_sequence<bool>(source->get_elements_quantity(), false);
    source->depth_first_search(0, to_out);
    std::cout << to_out;
    delete to_out;

    auto components = source->find_connected_components();
    for (std::size_t i = 0; i < components->get_size(); i++) {
        std::cout << components->operator[](i);
        delete components->operator[](i);
    }
    delete components;
    
    auto top_sorted = source->topological_sort();
    std::cout << "\nTopolog\n\n" << top_sorted;
    delete top_sorted;

    delete source;
    return 0;
}

void testing_djkstra() {
    auto source = new graph<int>(5, true, SIZE_MAX_LOCAL);

    source->add_edge(0, 1, 2);
    source->add_edge(1, 0, 2);
    source->add_edge(0, 2, 3);
    source->add_edge(1, 2, 4);
    source->add_edge(3, 4, 5);
    source->add_edge(3, 2, 6);
    source->add_vertex();
    source->add_edge(0, 5, 11);
    source->add_edge(5, 4, 22);

    auto djkstra = source->find_shortest_path_djkstra(2);
    std::vector<std::size_t> correct = {3, 4, 0, 6, 32535, 32535};

    for (std::size_t i = 0; i < djkstra->get_size(); i++) {
        assert(djkstra->operator[](i) == correct[i]);
    }
    
    delete djkstra;
    delete source;
}

void testing_bfs() {
     auto source = new graph<int>(5, true, SIZE_MAX_LOCAL);

     source->add_edge(0, 1, 2);
     source->add_edge(1, 0, 2);
     source->add_edge(0, 2, 3);
     source->add_edge(1, 2, 4);
     source->add_edge(3, 4, 5);
     source->add_edge(3, 2, 6);
     source->add_vertex();
     source->add_edge(0, 5, 11);
     source->add_edge(5, 4, 22);
    
     auto breadth = source->breadth_first_search(2);
 
     std::vector<std::size_t> correct = {1, 1, 0, 1, 0, 0};

     for (std::size_t i = 0; i < breadth->get_size(); i++) {
         assert(breadth->operator[](i) == correct[i]);
     }

     delete breadth;
     delete source;
 }

void testing_wallsher() {
      auto source = new graph<int>(5, true, SIZE_MAX_LOCAL);

      source->add_edge(0, 1, 2);
      source->add_edge(1, 0, 2);
      source->add_edge(0, 2, 3);
      source->add_edge(1, 2, 4);
      source->add_edge(3, 4, 5);
      source->add_edge(3, 2, 6);
      source->add_vertex();
      source->add_edge(0, 5, 11);
      source->add_edge(5, 4, 22);

      auto wallsher = source->find_all_shortest_path_wallsher();
      std::vector<std::vector<std::size_t>> correct = {{32535, 2, 32535, 32535, 32535, 32535, 32535},
                                                      {2, 32535, 32535, 32535, 32535, 32535, 32535},
                                                      {3, 4, 32535, 6, 32535, 32535},
                                                      {32535, 32535, 32535, 32535, 32535, 32535},
                                                      {33, 32535, 32535, 5, 32535, 22}, 
                                                      {11, 32535, 32535, 32535, 32535, 32535}};
      for (std::size_t i = 0; i < wallsher->get_elements_quantity(); i++) {
          for (std::size_t j = 0; j < wallsher->get_elements_quantity(); j++) {
              assert(wallsher->get_edge_weight(i, j) == correct[i][j]);
          }
      }

      delete wallsher;
      delete source;
}

void testing_spanning_tree() {
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
    
    auto spanning = source->find_minimal_spanning_tree();
    std::vector<std::size_t> correct = {0, 1, 0, 2, 2, 3, 3, 4, 0, 5};

    for (std::size_t i = 0; i < spanning->get_size(); i++) {
        assert(spanning->operator[](i) == correct[i]);
    }

    delete source;
    delete spanning;
}

void testing_connected_components() {
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

    auto components = source->find_connected_components();
    std::vector<std::size_t> correct = {0, 1, 2, 3, 4, 5};

    for (std::size_t i = 0; i < correct.size(); i++) {
        assert(components->operator[](0)->operator[](i) == correct[i]);
    }

    delete source;
    delete components->operator[](0);
    delete components;
}

void testing_topological() {
    auto source = new graph<int>(5, true, SIZE_MAX_LOCAL);

    source->add_edge(0, 1, 2);
    source->add_edge(1, 0, 2);
    source->add_edge(0, 2, 3);
    source->add_edge(1, 2, 4);
    source->add_edge(3, 4, 5);
    source->add_edge(3, 2, 6);
    source->add_vertex();
    source->add_edge(0, 5, 11);
    source->add_edge(5, 4, 22);

    auto sorted_vertex = source->topological_sort();
    std::vector<std::size_t> correct = {4, 5, 2, 3, 0, 1};

    for (std::size_t i = 0; i < sorted_vertex->get_size(); i++) {
        assert(sorted_vertex->operator[](i) == correct[i]);
    }

    delete sorted_vertex;
    delete source;
}
