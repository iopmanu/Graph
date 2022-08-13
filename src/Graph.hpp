#ifndef SRC_GRAPH_HPP_
#define SRC_GRAPH_HPP_

#include "ArraySequence.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>

#define INIT_CONST SIZE_MAX_LOCAL - 100

/*typename T is element weight*/
template <typename T>
class graph {
private:
    array_sequence<array_sequence<T> *> *_graph = NULL;
    bool is_directed = 0;

public:
    /*==================================CONSTRUCTORS==================================*/

    explicit graph(const std::size_t &elements_count, const bool &direction) noexcept
        : _graph(new array_sequence<array_sequence<T> *>(elements_count)), is_directed(direction) {
        for (std::size_t i = 0; i < _graph->get_size(); i++) {
            _graph->operator[](i) = new array_sequence<T>(elements_count, T(0));
        }
    }

    explicit graph(const std::size_t &elements_count, const bool &direction, const T &init_value) noexcept
        : _graph(new array_sequence<array_sequence<T> *>(elements_count)), is_directed(direction) {
        for (std::size_t i = 0; i < _graph->get_size(); i++) {
            _graph->operator[](i) = new array_sequence<T>(elements_count, init_value);
        }
    }

    ~graph() {
        for (std::size_t i = 0; i < _graph->get_size(); i++) {
            delete _graph->operator[](i);
        }

        delete _graph;
    }

    /*==================================OPERATORS==================================*/

    friend std::ostream &operator<<(std::ostream &out, graph<T> *source) noexcept {
        out << "\t";

        for (std::size_t i = 0; i < source->_graph->get_size(); i++) {
            out << i << "\t";
        }

        out << std::endl << std::endl;

        for (std::size_t i = 0; i < source->_graph->get_size(); i++) {
            out << i << source->_graph->operator[](i) << std::endl;
        }

        return out;
    }

    /*==================================LOOKUP==================================*/

    constexpr std::size_t get_elements_quantity() const noexcept { return this->_graph->get_size(); }

    constexpr std::size_t empty() const noexcept { return this->_graph->empty(); }

    /*==================================METHODS==================================*/

    void add_edge(const std::size_t &first_element, const std::size_t &second_element, const T &weight) noexcept {
        this->_graph->operator[](second_element)->operator[](first_element) = std::move(weight);
        if (this->is_directed == false) {
            this->_graph->operator[](first_element)->operator[](second_element) = std::move(weight);
        }
    }

    void delete_edge(const std::size_t &first_element, const std::size_t &second_element) noexcept {
        this->_graph->operator[](first_element)->operator[](second_element) = std::move(SIZE_MAX_LOCAL);
        if (this->is_directed == false) {
            this->_graph->operator[](second_element)->operator[](first_element) = std::move(SIZE_MAX_LOCAL);
        }
    }

    void add_vertex() noexcept {
        this->_graph->append(new array_sequence<T>(this->get_elements_quantity(), SIZE_MAX_LOCAL));

        for (std::size_t i = 0; i < this->get_elements_quantity(); i++) {
            _graph->operator[](i)->append(SIZE_MAX_LOCAL);
        }
    }

    void delete_vertex() noexcept {
        for (std::size_t i = 0; i < this->get_elements_quantity(); i++) {
            this->delete_edge(i, this->get_elements_quantity() - 1);
            _graph->operator[](i)->pop_back();
        }

        _graph->pop_back();
    }

    const T &get_edge_weight(const std::size_t &first_element, const std::size_t &second_element) const noexcept {
        return this->_graph->operator[](first_element)->operator[](second_element);
    }

    array_sequence<std::size_t> *find_shortest_path_djkstra(const std::size_t &started_element) const {
        auto path_sequence = new array_sequence<std::size_t>(_graph->get_size(), SIZE_MAX_LOCAL);
        auto parents_sequence = new array_sequence<std::size_t>(_graph->get_size(), size_t(0));
        auto visited_sequence = new array_sequence<bool>(_graph->get_size(), false);

        path_sequence->operator[](started_element) = 0;

        for (std::size_t i = 0; i < this->get_elements_quantity(); i++) {
            std::size_t vertex = INIT_CONST;

            for (std::size_t j = 0; j < this->get_elements_quantity(); j++) {
                if (!visited_sequence->operator[](j) &&
                    (vertex == INIT_CONST || path_sequence->operator[](j) < path_sequence->operator[](vertex))) {
                    vertex = j;
                }
            }

            if (path_sequence->operator[](vertex) == SIZE_MAX) {
                break;
            }

            visited_sequence->operator[](vertex) = true;

            for (std::size_t j = 0; j < this->get_elements_quantity(); j++) {
                if (_graph->operator[](vertex)->operator[](j) == T(0)) {
                    continue;
                }

                std::size_t length = _graph->operator[](vertex)->operator[](j);

                if (path_sequence->operator[](vertex) + length < path_sequence->operator[](j)) {
                    path_sequence->operator[](j) = path_sequence->operator[](vertex) + length;
                    parents_sequence->operator[](j) = vertex;
                }
            }
        }

        delete parents_sequence;
        delete visited_sequence;

        return path_sequence;
    }

    graph<std::size_t> *find_all_shortest_path_wallsher() const noexcept {
        auto path_matrix = new graph<std::size_t>(this->get_elements_quantity(), this->is_directed, SIZE_MAX_LOCAL);

        for (std::size_t k = 0; k < _graph->get_size(); k++) {
            for (std::size_t i = 0; i < _graph->get_size(); i++) {
                for (std::size_t j = 0; j < _graph->get_size(); j++) {
                    if (_graph->operator[](i)->operator[](j) == T(0) || _graph->operator[](i)->operator[](k) == T(0) ||
                        _graph->operator[](k)->operator[](j) == T(0)) {
                        continue;
                    }

                    path_matrix->add_edge(j, i,
                                          std::min(this->get_edge_weight(i, j), this->get_edge_weight(i, k) + this->get_edge_weight(k, j)));
                }
            }
        }

        return path_matrix;
    }

    graph<std::size_t> *get_adjency_matrix() const noexcept {
        auto adjency_matrix = new graph<std::size_t>(this->_graph->get_size(), this->is_directed);

        for (std::size_t i = 0; i < _graph->get_size(); i++) {
            for (std::size_t j = 0; j < _graph->get_size(); j++) {
                if (this->get_edge_weight(i, j) != SIZE_MAX_LOCAL) {
                    adjency_matrix->add_edge(j, i, true);
                }
            }
        }

        return adjency_matrix;
    }

    array_sequence<std::size_t> *find_minimal_spanning_tree() const noexcept {
        auto spanning_sequence = new array_sequence<T>(_graph->get_size(), SIZE_MAX_LOCAL);   // edges weight
        auto edge_end = new array_sequence<std::size_t>(_graph->get_size(), SIZE_MAX_LOCAL);  // ends of edges
        auto spanning_tree = new array_sequence<std::size_t>(_graph->get_size());  // sequence for minimal spanning tree edges(to output)
        auto is_used = new array_sequence<bool>(_graph->get_size(), false);
        spanning_tree->erase_all();
        spanning_sequence->operator[](0) = T(0);

        for (std::size_t i = 0; i < this->get_elements_quantity(); i++) {
            std::size_t vertex = INIT_CONST;

            for (std::size_t j = 0; j < this->get_elements_quantity(); j++) {
                if (!is_used->operator[](j) &&
                    (vertex == INIT_CONST || spanning_sequence->operator[](j) < spanning_sequence->operator[](vertex))) {
                    vertex = j;
                }
            }

            if (spanning_sequence->operator[](vertex) == SIZE_MAX_LOCAL) {
                delete is_used;
                delete spanning_sequence;
                delete edge_end;
                delete spanning_tree;
                return new array_sequence<std::size_t>(_graph->get_size(), SIZE_MAX_LOCAL);
            }

            is_used->operator[](vertex) = true;

            if (edge_end->operator[](vertex) != SIZE_MAX_LOCAL) {
                spanning_tree->append(edge_end->operator[](vertex));
                spanning_tree->append(vertex);
            }

            for (std::size_t j = 0; j < this->get_elements_quantity(); j++) {
                if (this->get_edge_weight(vertex, j) < spanning_sequence->operator[](j)) {
                    spanning_sequence->operator[](j) = this->get_edge_weight(vertex, j);
                    edge_end->operator[](j) = vertex;
                }
            }
        }

        delete is_used;
        delete spanning_sequence;
        delete edge_end;

        return spanning_tree;
    }

    array_sequence<std::size_t> *breadth_first_search(const std::size_t &start_pos) const noexcept {
        auto queue = new array_sequence<std::size_t>(_graph->get_size(), 0);
        auto is_used = new array_sequence<bool>(_graph->get_size(), false);
        auto paths_length = new array_sequence<std::size_t>(_graph->get_size(), std::size_t(0));

        queue->append(start_pos);
        is_used->operator[](start_pos) = true;

        while (!queue->empty()) {
            std::size_t vertex = queue->get_first();
            queue->erase(0);

            for (std::size_t i = 0; i < _graph->get_size(); i++) {
                if (!is_used->operator[](i) && this->get_edge_weight(vertex, i) != SIZE_MAX_LOCAL) {
                    is_used->operator[](i) = true;
                    queue->append(i);
                    paths_length->operator[](i) = paths_length->operator[](vertex) + 1;
                }
            }
        }

        delete is_used;
        delete queue;

        return paths_length;
    }

    void depth_first_search(const std::size_t &start_pos, array_sequence<bool> *is_used) const noexcept {
        is_used->operator[](start_pos) = true;

        for (std::size_t i = 0; i < _graph->get_size(); i++) {
            if (!is_used->operator[](i) && this->get_edge_weight(start_pos, i) != SIZE_MAX_LOCAL) {
                depth_first_search(i, is_used);
            }
        }
    }

    void topological_depth_search(const std::size_t &start_pos, array_sequence<bool> *is_used,
                                  array_sequence<std::size_t> *new_order) const noexcept {
        is_used->operator[](start_pos) = true;

        for (std::size_t i = 0; i < _graph->get_size(); i++) {
            if (!is_used->operator[](i) && this->get_edge_weight(start_pos, i) != SIZE_MAX_LOCAL) {
                topological_depth_search(i, is_used, new_order);
            }
        }

        new_order->append(start_pos);
    }

    array_sequence<array_sequence<std::size_t> *> *find_connected_components() const noexcept {
        auto connected_components_list = std::move(new array_sequence<array_sequence<std::size_t> *>(_graph->get_size()));
        connected_components_list->erase_all();
        auto is_used = new array_sequence<bool>(_graph->get_size(), false);

        for (std::size_t i = 0; i < _graph->get_size(); i++) {
            if (!is_used->operator[](i)) {
                delete is_used;
                is_used = new array_sequence<bool>(_graph->get_size(), false);

                this->depth_first_search(i, is_used);
                auto component = new array_sequence<std::size_t>(_graph->get_size(), SIZE_MAX_LOCAL);
                component->erase_all();

                for (std::size_t j = 0; j < _graph->get_size(); j++) {
                    if (is_used->operator[](j)) {
                        component->append(j);
                    }
                }

                connected_components_list->append(component);
            }
        }

        delete is_used;

        return connected_components_list;
    }

    array_sequence<std::size_t> *topological_sort() const noexcept {
        auto is_used = new array_sequence<bool>(_graph->get_size(), false);
        auto new_order_vertexes = new array_sequence<std::size_t>(_graph->get_size(), false);
        new_order_vertexes->erase_all();

        for (std::size_t i = 0; i < _graph->get_size(); i++) {
            if (!is_used->operator[](i)) {
                topological_depth_search(i, is_used, new_order_vertexes);
            }
        }

        delete is_used;

        std::reverse(new_order_vertexes->begin(), new_order_vertexes->end());

        return new_order_vertexes;
    }
};

#endif  // SRC_GRAPH_HPP_
