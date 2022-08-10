#ifndef SRC_GRAPH_HPP_
#define SRC_GRAPH_HPP_

#include "ArraySequence.hpp"
#include <iostream>

/*typename T is element weight*/
template <typename T>
class graph {
private:
    array_sequence<array_sequence<T> *> *_graph = NULL;

public:
    /*==================================CONSTRUCTORS==================================*/

    explicit graph() noexcept : _graph(new array_sequence<sequence<T> *>) {}

    explicit graph(const std::size_t &elements_count) noexcept : _graph(new array_sequence<array_sequence<T> *>(elements_count)) {
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

    void add_edge(const std::size_t &first_element, const std::size_t &second_element, const T &weight) {
        this->_graph->operator[](first_element)->operator[](second_element) = std::move(weight);
        this->_graph->operator[](second_element)->operator[](first_element) = std::move(weight);
    }

    void delete_edge(const std::size_t &first_element, const std::size_t &second_element) {
        this->_graph->operator[](first_element)->operator[](second_element) = std::move(T(0));
        this->_graph->operator[](second_element)->operator[](first_element) = std::move(T(0));
    }
};

#endif  // SRC_GRAPG_HPP_
