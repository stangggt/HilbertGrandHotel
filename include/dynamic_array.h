#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <initializer_list>

/**
 * @brief Custom Dynamic Array Data Structure for Academic Coursework.
 * Demonstrates manual heap memory management, geometric capacity scaling (2x),
 * Rule-of-Five compliance, and STL-compatible forward iterators.
 *
 * @tparam T The element type.
 */
template <typename T>
class DynamicArray {
private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    static constexpr size_t DEFAULT_CAPACITY = 8;
    static constexpr size_t GROWTH_FACTOR = 2;

    void reallocate(size_t newCapacity) {
        if (newCapacity < m_size) {
            newCapacity = m_size;
        }
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < m_size; ++i) {
            newData[i] = std::move(m_data[i]);
        }
        delete[] m_data;
        m_data = newData;
        m_capacity = newCapacity;
    }

public:
    // Default constructor
    DynamicArray()
        : m_data(new T[DEFAULT_CAPACITY]), m_size(0), m_capacity(DEFAULT_CAPACITY) {}

    // Explicit constructor with initial capacity
    explicit DynamicArray(size_t initialCapacity)
        : m_data(new T[initialCapacity > 0 ? initialCapacity : DEFAULT_CAPACITY]),
          m_size(0),
          m_capacity(initialCapacity > 0 ? initialCapacity : DEFAULT_CAPACITY) {}

    // Initializer list constructor
    DynamicArray(std::initializer_list<T> initList)
        : m_data(new T[initList.size() > 0 ? initList.size() : DEFAULT_CAPACITY]),
          m_size(initList.size()),
          m_capacity(initList.size() > 0 ? initList.size() : DEFAULT_CAPACITY) {
        size_t idx = 0;
        for (const auto& item : initList) {
            m_data[idx++] = item;
        }
    }

    // Destructor (Rule of Five: 1/5)
    ~DynamicArray() {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    // Copy Constructor (Rule of Five: 2/5)
    DynamicArray(const DynamicArray& other)
        : m_data(new T[other.m_capacity]),
          m_size(other.m_size),
          m_capacity(other.m_capacity) {
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    // Copy Assignment Operator (Rule of Five: 3/5)
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            T* newData = new T[other.m_capacity];
            for (size_t i = 0; i < other.m_size; ++i) {
                newData[i] = other.m_data[i];
            }
            delete[] m_data;
            m_data = newData;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
        }
        return *this;
    }

    // Move Constructor (Rule of Five: 4/5)
    DynamicArray(DynamicArray&& other) noexcept
        : m_data(other.m_data),
          m_size(other.m_size),
          m_capacity(other.m_capacity) {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // Move Assignment Operator (Rule of Five: 5/5)
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] m_data;
            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    // Element Access
    T& operator[](size_t index) { return m_data[index]; }
    const T& operator[](size_t index) const { return m_data[index]; }

    T& at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("DynamicArray::at: Index out of range");
        }
        return m_data[index];
    }

    const T& at(size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("DynamicArray::at: Index out of range");
        }
        return m_data[index];
    }

    T& front() {
        if (empty()) throw std::out_of_range("DynamicArray::front: Array is empty");
        return m_data[0];
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("DynamicArray::front: Array is empty");
        return m_data[0];
    }

    T& back() {
        if (empty()) throw std::out_of_range("DynamicArray::back: Array is empty");
        return m_data[m_size - 1];
    }

    const T& back() const {
        if (empty()) throw std::out_of_range("DynamicArray::back: Array is empty");
        return m_data[m_size - 1];
    }

    T* data() noexcept { return m_data; }
    const T* data() const noexcept { return m_data; }

    // Capacity & Size
    size_t size() const noexcept { return m_size; }
    size_t capacity() const noexcept { return m_capacity; }
    bool empty() const noexcept { return m_size == 0; }

    void reserve(size_t newCapacity) {
        if (newCapacity > m_capacity) {
            reallocate(newCapacity);
        }
    }

    void shrink_to_fit() {
        if (m_capacity > m_size) {
            reallocate(m_size > 0 ? m_size : DEFAULT_CAPACITY);
        }
    }

    // Modifiers
    void push_back(const T& value) {
        if (m_size == m_capacity) {
            reallocate(m_capacity * GROWTH_FACTOR);
        }
        m_data[m_size++] = value;
    }

    void push_back(T&& value) {
        if (m_size == m_capacity) {
            reallocate(m_capacity * GROWTH_FACTOR);
        }
        m_data[m_size++] = std::move(value);
    }

    template <typename... Args>
    T& emplace_back(Args&&... args) {
        if (m_size == m_capacity) {
            reallocate(m_capacity * GROWTH_FACTOR);
        }
        m_data[m_size] = T(std::forward<Args>(args)...);
        return m_data[m_size++];
    }

    void pop_back() {
        if (empty()) {
            throw std::underflow_error("DynamicArray::pop_back: Array is empty");
        }
        --m_size;
    }

    void clear() noexcept {
        m_size = 0;
    }

    // Iterators for range-based for loops
    T* begin() noexcept { return m_data; }
    const T* begin() const noexcept { return m_data; }
    const T* cbegin() const noexcept { return m_data; }

    T* end() noexcept { return m_data + m_size; }
    const T* end() const noexcept { return m_data + m_size; }
    const T* cend() const noexcept { return m_data + m_size; }
};

#endif // DYNAMIC_ARRAY_H
