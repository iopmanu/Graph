#ifndef SRC_GRAPH_HPP_
#define SRC_GRAPH_HPP_

#include "ArraySequence.hpp"
#include <iostream>

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
};

#endif  // SRC_GRAPG_HPP_
