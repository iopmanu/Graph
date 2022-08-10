#ifndef SRC_SEQUENCE_HPP_
#define SRC_SEQUENCE_HPP_

#include <cstddef>

template <typename T>
class sequence {
public:
    virtual inline std::size_t get_size() const noexcept = 0;
    virtual std::size_t find(const T&) noexcept = 0;

    virtual inline T& get_first() const = 0;
    virtual inline T& get_last() const = 0;

    virtual inline bool empty() const noexcept = 0;

    virtual void clear() noexcept = 0;
    virtual void append(const T&) = 0;
    virtual void prepend(const T&) = 0;
    virtual void insert(const T&, std::size_t) = 0;
    virtual void pop_back() = 0;
    virtual void erase(std::size_t) = 0;
};

#endif  // SRC_SEQUENCE_HPP_
