// Create a custom vector class that would support all the functionality
// given in main.cpp.

// Again: Declare your functions inside your class, but define them outside of it.

// #include <vector>
#pragma once
#include <iostream>
#include <algorithm>
#include <initializer_list>
template <typename T>
// using Vector = std::vector<T>;
class Vector
{

public:
    Vector(std::size_t capacity = 0) : m_capacity(capacity), m_size(capacity)
    {
        m_vec = new T[m_capacity];
        for (std::size_t i = 0; i < m_capacity; i++)
        {
            m_vec[i] = T();
        }
    }
    Vector(std::size_t capacity, T elem) : m_capacity(capacity), m_size(capacity)
    {
        m_vec = new T[m_capacity];
        for (std::size_t i = 0; i < m_capacity; i++)
        {
            m_vec[i] = elem;
        }
    }
    Vector(std::initializer_list<T> list) : m_capacity(list.size()), m_size(list.size())
    {
        m_vec = new T[m_capacity];
        std::size_t i = 0;
        for (auto &it : list)
        {
            m_vec[i] = it;
            i++;
        }
    }
    Vector(const Vector &other) : m_capacity(other.m_capacity), m_size(other.m_size)
    {
        m_vec = new T[m_capacity];
        for (std::size_t i = 0; i < m_size; i++)
        {
            m_vec[i] = other.m_vec[i];
        }
    }

    const T &operator[](std::size_t index) const
    {
        if (index >= m_size)
        {
            throw std::out_of_range("there is no such element");
        }
        return m_vec[index];
    }
    T &operator[](std::size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("there is no such element");
        }
        return m_vec[index];
    }

    std::size_t size()
    {
        return m_size;
    }
    std::size_t capacity()
    {
        return m_capacity;
    }

    void push_back(T elem)
    {
        if (m_capacity == m_size)
        {
            if (m_capacity == 0)
            {
                T *temp = new T[1];
                // delete[] m_vec;
                m_capacity = 1;
                m_vec = temp;
            }
            else
            {
                T *temp = new T[m_capacity * 2];
                for (std::size_t i = 0; i < m_size; i++)
                {
                    temp[i] = m_vec[i];
                }
                delete[] m_vec;
                m_size = m_capacity;
                m_capacity = m_capacity * 2;
                m_vec = temp;
            }
        }

        m_vec[m_size++] = elem;
    }
    void pop_back()
    {
        if (m_size == 0)
        {
            throw std::out_of_range("there is no more element in vector");
        }
        m_size--;
    }

    void clear()
    {

        m_size = 0;
    }
    bool empty()
    {
        if (m_size == 0)
        {
            return true;
        }
        return false;
    }

    bool operator==(const Vector &other)
    {
        if (m_capacity != other.m_capacity && m_size != other.m_size)
        {
            return false;
        }
        for (std::size_t i = 0; i < m_size; i++)
        {
            if (m_vec[i] != other.m_vec[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Vector &other)
    {
        if (*this == other)
        {
            return false;
        }
        return true;
    }

    Vector &operator=(const Vector &other)
    {
        if (*this == other)
        {
            return *this;
        }
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_vec = new T[m_capacity];
        for (std::size_t i = 0; i < m_size; i++)
        {
            m_vec[i] = other.m_vec[i];
        }
        return (*this);
    }

    T &at(std::size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("cant reach this element");
        }
        return m_vec[index];
    }
    T &front()
    {
        if (m_size == 0)
        {
            throw std::logic_error("there is no elements");
        }
        return m_vec[0];
    }
    T &back()
    {
        if (m_size == 0)
        {
            throw std::logic_error("there is no elements");
        }
        return m_vec[m_size - 1];
    }
    T *data()
    {
        return m_vec;
    }

    void reserve(std::size_t min_capacity)
    {
        if (min_capacity <= m_capacity)
        {
            return;
        }
        T *temp = new T[min_capacity];
        for (std::size_t i = 0; i < m_size; i++)
        {
            temp[i] = m_vec[i];
        }
        delete[] m_vec;
        m_capacity = min_capacity;
        m_vec = temp;
    }
    void shrink_to_fit()
    {
        if (m_size == m_capacity)
        {
            return;
        }
        T *temp = new T[m_size];
        for (std::size_t i = 0; i < m_size; i++)
        {
            temp[i] = m_vec[i];
        }
        delete[] m_vec;
        m_capacity = m_size;
        m_vec = temp;
    }

    template <typename... Args>
    T &emplace_back(Args &&...args)
    {
        new (&m_vec[size]) T(std::forward<Args>(args)...);
        ++size;
    }

    void swap(Vector &other)
    {
        std::swap(m_vec, other.m_vec);
        std::swap(m_capacity, other.m_capacity);
        // std::cout << m_capacity << std::endl;
        std::swap(m_size, other.m_size);
        // std::cout << m_size << std::endl;
    }

    ~Vector()
    {
        delete[] m_vec;
    }

private:
    T *m_vec = nullptr;
    std::size_t m_capacity;
    std::size_t m_size;
};