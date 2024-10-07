// Create a custom vector class that would support all the functionality
// given in main.cpp.

// Again: Declare your functions inside your class, but define them outside of it.

// #include <vector>
#pragma once
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <new>
// using Vector = std::vector<T>;
template <typename T>
class Vector
{
public:
    Vector();
    Vector(std::size_t size);
    Vector(std::size_t size, T elem);
    Vector(std::initializer_list<T> list);
    Vector(const Vector &other);
    Vector(Vector &&other) noexcept;

    const T &operator[](std::size_t index) const;
    T &operator[](std::size_t index);

    std::size_t size() const;
    std::size_t capacity() const;

    void push_back(T elem);
    void pop_back();

    void clear();
    bool empty() const;

    Vector &operator=(Vector &&other) noexcept;
    Vector &operator=(const Vector &other);

    T &at(std::size_t index) const;
    T &front() const;
    T &back() const;
    T *data() const;

    void reserve(std::size_t min_capacity);
    void shrink_to_fit();

    template <typename... Args>
    void emplace_back(Args &&...args);

    void swap(Vector &other);

    ~Vector();

private:
    T *m_vec;
    std::size_t m_capacity;
    std::size_t m_size;
    void reAllocate(std::size_t new_capacity);
};

template <typename T>
void Vector<T>::reAllocate(std::size_t new_capacity)
{
    T *temp = static_cast<T *>(std::aligned_alloc(alignof(T), sizeof(T) * new_capacity));
    for (std::size_t i = 0; i < m_size; i++)
    {
        new (&temp[i]) T(std::move(m_vec[i]));
    }
    std::free(m_vec);
    m_capacity = new_capacity;
    m_vec = temp;
}

template <typename T>
Vector<T>::Vector() : m_vec(nullptr), m_capacity(0), m_size(0) {}

template <typename T>
Vector<T>::Vector(std::size_t size) : m_capacity(size), m_size(size)
{
    m_vec = static_cast<T *>(std::aligned_alloc(alignof(T), sizeof(T) * m_capacity));
    for (std::size_t i = 0; i < m_size; i++)
    {
        new (&m_vec[i]) T();
    }
}

template <typename T>
Vector<T>::Vector(std::size_t size, T elem) : m_capacity(size), m_size(size)
{
    m_vec = static_cast<T *>(std::aligned_alloc(alignof(T), sizeof(T) * m_capacity));
    for (std::size_t i = 0; i < m_size; i++)
    {
        new (&m_vec[i]) T(elem);
    }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> list) : m_capacity(list.size()), m_size(list.size())
{
    m_vec = static_cast<T *>(std::aligned_alloc(alignof(T), sizeof(T) * m_capacity));
    std::size_t i = 0;
    for (auto &it : list)
    {
        new (&m_vec[i]) T(it);
        i++;
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T> &other) : m_capacity(other.m_capacity), m_size(other.m_size)
{
    m_vec = static_cast<T *>(std::aligned_alloc(alignof(T), sizeof(T) * m_capacity));
    for (std::size_t i = 0; i < m_size; i++)
    {
        new (&m_vec[i]) T(other.m_vec[i]);
    }
}

template <typename T>
Vector<T>::Vector(Vector<T> &&other) noexcept : m_vec(other.m_vec), m_capacity(other.m_capacity), m_size(other.m_size)
{
    other.m_vec = nullptr;
    other.m_capacity = 0;
    other.m_size = 0;
}

template <typename T>
const T &Vector<T>::operator[](std::size_t index) const
{
    if (index >= m_size)
    {
        throw std::out_of_range("there is no such element");
    }
    return m_vec[index];
}

template <typename T>
T &Vector<T>::operator[](std::size_t index)
{
    if (index >= m_size)
    {
        throw std::out_of_range("there is no such element");
    }
    return m_vec[index];
}

template <typename T>
std::size_t Vector<T>::size() const
{
    return m_size;
}

template <typename T>
std::size_t Vector<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
void Vector<T>::push_back(T elem)
{
    if (m_capacity == m_size)
    {
        if (m_capacity == 0)
        {
            reAllocate(1);
        }
        else
        {
            reAllocate(m_capacity * 2);
        }
    }
    new (&m_vec[m_size++]) T(std::move(elem));
}

template <typename T>
void Vector<T>::pop_back()
{
    if (m_size == 0)
    {
        throw std::out_of_range("there is no more element in vector");
    }
    m_vec[m_size - 1].~T();
    m_size--;
}

template <typename T>
void Vector<T>::clear()
{
    for (std::size_t i = 0; i < m_size; i++)
    {
        m_vec[i].~T();
    }
    m_size = 0;
}

template <typename T>
bool Vector<T>::empty() const
{
    return (m_size == 0);
}

template <typename T>
bool operator==(const Vector<T> &lhs, const Vector<T> &rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }
    for (std::size_t i = 0; i < lhs.size(); i++)
    {
        if (!(lhs[i] == rhs[i]))
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!=(const Vector<T> &lhs, const Vector<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept
{
    if (m_vec == other.m_vec)
    {
        return *this;
    }
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    T *temp = static_cast<T *>(std::aligned_alloc(alignof(T), sizeof(T) * other.m_capacity));
    for (std::size_t i = 0; i < m_size; i++)
    {
        new (&temp[i]) T(std::move(other.m_vec[i]));
    }
    other.m_vec = nullptr;
    other.m_capacity = 0;
    other.m_size = 0;
    free(m_vec);
    m_vec = temp;
    return (*this);
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    if (m_vec == other.m_vec)
    {
        return *this;
    }
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    T *temp = static_cast<T *>(std::aligned_alloc(alignof(T), sizeof(T) * other.m_capacity));
    for (std::size_t i = 0; i < m_size; i++)
    {
        new (&temp[i]) T(other.m_vec[i]);
    }
    free(m_vec);
    m_vec = temp;
    return (*this);
}

template <typename T>
T &Vector<T>::at(std::size_t index) const
{
    if (index >= m_size)
    {
        throw std::out_of_range("cant reach this element");
    }
    return m_vec[index];
}

template <typename T>
T &Vector<T>::front() const
{
    if (m_size == 0)
    {
        throw std::logic_error("there are no elements");
    }
    return m_vec[0];
}

template <typename T>
T &Vector<T>::back() const
{
    if (m_size == 0)
    {
        throw std::logic_error("there are no elements");
    }
    return m_vec[m_size - 1];
}

template <typename T>
T *Vector<T>::data() const
{
    return m_vec;
}

template <typename T>
void Vector<T>::reserve(std::size_t min_capacity)
{
    if (min_capacity > m_capacity)
    {
        reAllocate(min_capacity);
    }
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
    if (m_size < m_capacity)
    {
        reAllocate(m_size);
    }
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace_back(Args &&...args)
{
    if (m_size == m_capacity)
    {
        if (m_capacity == 0)
        {
            reAllocate(1);
        }
        else
        {
            reAllocate(m_capacity * 2);
        }
    }
    new (&m_vec[m_size++]) T(std::forward<Args>(args)...);
}

template <typename T>
void Vector<T>::swap(Vector<T> &other)
{
    std::swap(m_vec, other.m_vec);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_size, other.m_size);
}

template <typename T>
Vector<T>::~Vector()
{
    if (m_vec)
    {
        for (std::size_t i = 0; i < m_size; i++)
        {
            m_vec[i].~T();
        }
        std::free(m_vec);
    }
}