#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <initializer_list>

/**
 * @brief Custom Dynamic Array Data Structure for learning Data Structures in C++.
 * Demonstrates manual memory management, geometric capacity scaling,
 * element shifting for insert/delete, and Rule-of-Five compliance.
 *
 * @tparam T The element type stored in the array.
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

    // Constructor with initial capacity
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

    // Destructor
    ~DynamicArray() {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    // Copy Constructor
    DynamicArray(const DynamicArray& other)
        : m_data(new T[other.m_capacity]),
          m_size(other.m_size),
          m_capacity(other.m_capacity) {
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    // Copy Assignment Operator
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

    // Move Constructor
    DynamicArray(DynamicArray&& other) noexcept
        : m_data(other.m_data),
          m_size(other.m_size),
          m_capacity(other.m_capacity) {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // Move Assignment Operator
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
    T& operator[](size_t index) {
        return m_data[index];
    }

    const T& operator[](size_t index) const {
        return m_data[index];
    }

    T& at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("DynamicArray::at - index out of range");
        }
        return m_data[index];
    }

    const T& at(size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("DynamicArray::at - index out of range");
        }
        return m_data[index];
    }

    T& front() {
        if (m_size == 0) throw std::out_of_range("DynamicArray::front - array is empty");
        return m_data[0];
    }

    const T& front() const {
        if (m_size == 0) throw std::out_of_range("DynamicArray::front - array is empty");
        return m_data[0];
    }

    T& back() {
        if (m_size == 0) throw std::out_of_range("DynamicArray::back - array is empty");
        return m_data[m_size - 1];
    }

    const T& back() const {
        if (m_size == 0) throw std::out_of_range("DynamicArray::back - array is empty");
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
        if (m_size < m_capacity) {
            size_t newCap = m_size > 0 ? m_size : DEFAULT_CAPACITY;
            reallocate(newCap);
        }
    }

    // Modifiers
    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            reserve(m_capacity * GROWTH_FACTOR);
        }
        m_data[m_size++] = value;
    }

    void push_back(T&& value) {
        if (m_size >= m_capacity) {
            reserve(m_capacity * GROWTH_FACTOR);
        }
        m_data[m_size++] = std::move(value);
    }

    void pop_back() {
        if (m_size > 0) {
            --m_size;
        }
    }

    /**
     * @brief Insert an element at a given index, shifting existing elements right (O(N)).
     */
    void insert_at(size_t index, const T& value) {
        if (index > m_size) {
            throw std::out_of_range("DynamicArray::insert_at - index out of range");
        }
        if (m_size >= m_capacity) {
            reserve(m_capacity * GROWTH_FACTOR);
        }
        for (size_t i = m_size; i > index; --i) {
            m_data[i] = std::move(m_data[i - 1]);
        }
        m_data[index] = value;
        ++m_size;
    }

    /**
     * @brief Remove an element at a given index, shifting trailing elements left (O(N)).
     */
    void remove_at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("DynamicArray::remove_at - index out of range");
        }
        for (size_t i = index; i < m_size - 1; ++i) {
            m_data[i] = std::move(m_data[i + 1]);
        }
        --m_size;
    }

    void clear() noexcept {
        m_size = 0;
    }

    // Iterators for standard range-based for loops
    T* begin() noexcept { return m_data; }
    T* end() noexcept { return m_data + m_size; }
    const T* begin() const noexcept { return m_data; }
    const T* end() const noexcept { return m_data + m_size; }
    const T* cbegin() const noexcept { return m_data; }
    const T* cend() const noexcept { return m_data + m_size; }
};

#endif // DYNAMIC_ARRAY_HPP
