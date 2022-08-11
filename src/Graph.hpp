#ifndef SRC_GRAPH_HPP_
#define SRC_GRAPH_HPP_

#include "ArraySequence.hpp"
#include <iostream>
#define SIZE_MAX_LOCAL 32535
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
            _graph->operator[](i) = new array_sequence<T>(elements_count);
        }
    }

    explicit graph(const std::size_t &elements_count, const bool &direction, const T &init_value) noexcept
        : _graph(new array_sequence<array_sequence<T> *>(elements_count)), is_directed(direction) {
        for (std::size_t i = 0; i < _graph->get_size(); i++) {
            _graph->operator[](i) = new array_sequence<T>(elements_count, init_value);
        }
    }

    ~graph() = default;

    /*==================================OPERATORS==================================*/

    friend std::ostream &operator<<(std::ostream &out, graph<T> *source) noexcept {
        out << " ";

        for (std::size_t i = 0; i < source->_graph->get_size(); i++) {
            out << " " << i;
        }

        out << std::endl;

        for (std::size_t i = 0; i < source->_graph->get_size(); i++) {
            out << i << " " << source->_graph->operator[](i);
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
        this->_graph->operator[](second_element)->operator[](first_element) = std::move(T(0));
        if (this->is_directed == false) {
            this->_graph->operator[](first_element)->operator[](second_element) = std::move(T(0));
        }
    }

    const T &get_edge_weight(const std::size_t &first_element, const std::size_t &second_element) const noexcept {
        return this->_graph->operator[](first_element)->operator[](second_element);
    }

    array_sequence<std::size_t> *find_shortest_path_djkstra(const std::size_t &started_element) const {
        auto path_sequence = new array_sequence<std::size_t>(_graph->get_size(), SIZE_MAX_LOCAL);
        auto parents_sequence = new array_sequence<std::size_t>(_graph->get_size());
        auto visited_sequence = new array_sequence<bool>(_graph->get_size(), false);

        path_sequence->operator[](started_element) = 0;

        for (std::size_t i = 0; i < this->get_elements_quantity(); i++) {
            std::size_t vertex = 4;

            for (std::size_t j = 0; j < this->get_elements_quantity(); j++) {
                if (!visited_sequence->operator[](j) && (vertex == 4 || path_sequence->operator[](j) < path_sequence->operator[](vertex))) {
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

    return path_sequence;
}

graph<std::size_t>
    *get_adjency_matrix() const noexcept {
    auto adjency_matrix = new graph<std::size_t>(this->_graph->get_size(), this->is_directed);

    for (std::size_t i = 0; i < _graph->get_size(); i++) {
        for (std::size_t j = 0; j < _graph->get_size(); j++) {
            if (this->_graph->operator[](i)->operator[](j) != T(0)) {
                adjency_matrix->add_edge(i, j, true);
            }
        }
    }

    return adjency_matrix;
}
}
;

#endif  // SRC_GRAPH_HPP_
