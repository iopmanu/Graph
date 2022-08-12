#ifndef SRC_DYNAMIC_ARRAY_HPP_
#define SRC_DYNAMIC_ARRAY_HPP_

#include "Graph.hpp"
#include "Sequence.hpp"

#include <assert.h>
#include <cstddef>
#include <iostream>

#define SIZE_MAX_LOCAL 32535

template <typename T>
class array_sequence : virtual public sequence<T> {
private:
    T* data;
    std::size_t capacity;
    std::size_t size;

    using iterator = T*;

public:
    /*==================================CONSTRUCTORS==================================*/
    explicit array_sequence() noexcept : data(new T[0]), capacity(0), size(0) {}

    explicit array_sequence(std::size_t _capacity) noexcept : data(new T[_capacity]), capacity(_capacity), size(_capacity) {}

    array_sequence(std::size_t _capacity, const T& value) noexcept : data(new T[_capacity]), capacity(_capacity), size(_capacity) {
        for (std::size_t i = 0; i < _capacity; i++) {
            this->data[i] = value;
        }
    }

    array_sequence(T* source, std::size_t count) noexcept : capacity(count), size(count) { data = std::move(source); }

    /*==================================OPERATORS==================================*/
    inline T& operator[](const std::size_t& index) {
        assert(index < this->size);
        return this->data[index];
    }

    array_sequence& operator=(array_sequence<T>&& source) noexcept {
        size = std::move(source.size);
        capacity = std::move(source.capacity);

        data = std::move(source.data);

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, array_sequence<T>* source) noexcept {
        for (iterator it = source->begin(); it != source->end(); ++it) {
            if (*it == SIZE_MAX_LOCAL) {
                out << "\t∞";
            } else {
                out << "\t" << *it;
            }
        }
        out << std::endl;

        return out;
    }

    /*==================================ITERATORS==================================*/
    iterator begin() const noexcept { return data; }

    iterator end() const noexcept { return data + this->size; }

    /*==================================INLINE_FUNCTIONS==================================*/
    inline std::size_t get_size() const noexcept { return this->size; }

    inline std::size_t get_capacity() const noexcept { return this->capacity; }

    inline bool empty() const noexcept { return this->size == 0; }

    inline T& get_first() const {
        assert(!this->empty());
        return this->data[0];
    }

    inline T& get_last() const {
        assert(!this->empty());
        return this->data[this->size - 1];
    }

    /*==================================METHODS==================================*/
    void resize(const std::size_t _capacity) {
        auto new_data = new T[_capacity];

        std::copy(this->begin(), this->end(), new_data);
        this->capacity = _capacity;

        data = std::move(new_data);
    }

    void append(const T& source) {
        if (this->size == this->capacity) {
            this->resize(capacity * 2);
        }

        this->data[size++] = source;
    }

    void prepend(const T& source) {
        if (this->size == this->capacity) {
            this->resize(capacity * 2);
        }

        auto new_data = new T[capacity];
        assert(new_data != NULL);

        new_data[0] = source;
        std::copy(this->begin(), this->end(), new_data + 1);
        data = std::move(new_data);
        this->size++;
    }

    void insert(const T& value, std::size_t index) {
        if (index >= this->size) {
            this->append(value);
            return;
        }

        if (this->size == this->capacity) {
            this->resize(capacity * 2);
        }

        auto new_data = new T[capacity];
        assert(new_data != NULL);

        new_data[index] = value;
        std::copy(this->begin(), this->begin() + index, new_data);
        std::copy(this->begin() + index, this->end(), new_data + index + 1);
        data = std::move(new_data);
        this->size++;
    }

    void erase(std::size_t index) {
        assert(index < this->size);
        assert(!this->empty());

        std::copy(this->begin() + index + 1, this->end(), this->begin() + index);
        this->size--;
    }

    std::size_t find(const T& value) noexcept {
        std::size_t i = 0;

        for (; i < this->size; i++) {
            if (this->data[i] == value) {
                break;
            }
        }

        return i;
    }

    void pop_back() { erase(this->size - 1); }

    void clear() noexcept {
        delete[] data;
        data = NULL;

        size = 0;
        capacity = 0;
    }
};

#endif  // SRC_DYNAMIC_ARRAY_HPP
