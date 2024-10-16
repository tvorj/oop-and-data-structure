// Create a custom singly linked list class that would support all the functionality
// given in main.cpp.

// Again: Declare your functions inside your class, but define them outside of it.
#pragma once
#include <iostream>
#include <iterator>
#include <optional>
template <typename T>
class ForwardList
{
public:
    ForwardList();
    ForwardList(std::size_t size);
    ForwardList(std::size_t size, const T &value);
    ForwardList(const ForwardList &other);
    ForwardList(ForwardList &&other) noexcept; // add this realisation
    ForwardList(std::initializer_list<T> list);
    template <std::input_iterator iter>
    ForwardList(iter begin, iter end);
    T &front();
    const T &front() const;
    bool empty() const;
    void clear();

    void push_front(const T &value);
    void push_fornt(T &&value); // add this realisation
    void pop_front();
    template <typename... Args>
    T &emplace_front(Args... args);

    bool operator==(const ForwardList &other);
    bool operator!=(const ForwardList &other);

    ForwardList &operator=(const ForwardList &other);
    ForwardList &operator=(ForwardList &&other) noexcept;

    ~ForwardList();

    class iterator;
    iterator begin();
    iterator end();
    iterator before_begin();

    class const_iterator;
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator before_begin() const;
    const_iterator cbefore_begin() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

private:
    struct Node
    {
        // std::optional<T> data;
        T data;
        Node *next;
        Node() = default;
        template <class... Args>
        Node(Args &&...args) : data(std::forward<Args>(args)...){};
        // Node(Args &&...args) : data(std::in_place, std::forward<Args>(args)...){};
        //  Node(std::nullopt_t) : data(std::nullopt) {};
    };
    // remove m_head use instead fake_head->next
    Node *m_head;
    // realizovat' 4erez std::optional
    // Node *fake_head;
    std::size_t m_size;

public:
    class iterator
    {
    public:
        iterator(Node *ptr) : m_iterator(ptr) {}
        bool operator==(const iterator &other) const
        {
            return m_iterator == other.m_iterator;
        }
        bool operator!=(const iterator &other) const
        {
            return m_iterator != other.m_iterator;
        }
        // prefix
        iterator &operator++()
        {
            if (m_iterator)
                m_iterator = m_iterator->next;
            return *this;
        }
        // postfix
        iterator operator++(int)
        {
            iterator temp(*this);
            m_iterator = m_iterator->next;
            return temp;
        }
        T *operator->() const
        {
            return &(m_iterator->data);
        }
        T &operator*() const
        {
            return m_iterator->data;
        }
        iterator &operator=(const const_iterator &other)
        {
            m_iterator = other.m_iterator;
            return (*this);
        }
        iterator &operator=(const iterator &other)
        {
            m_iterator = other.m_iterator;
            return (*this);
        }
        friend class const_iterator;

    private:
        Node *m_iterator;
    };
    // static_assert(std::forward_iterator<iterator>);
    class const_iterator
    {
    public:
        const_iterator(Node *ptr) : m_iterator(ptr) {}
        const_iterator(const const_iterator &other) : m_iterator(other.m_iterator) {}
        const_iterator(const iterator &other) : m_iterator(other.m_iterator) {}
        bool operator==(const const_iterator &other) const
        {
            return m_iterator == other.m_iterator;
        }
        bool operator!=(const const_iterator &other) const
        {
            return m_iterator != other.m_iterator;
        }
        // prefix
        const_iterator &operator++()
        {
            if (m_iterator)
                m_iterator = m_iterator->next;
            return *this;
        }
        // postfix
        const_iterator operator++(int)
        {
            const_iterator temp(*this);
            m_iterator = m_iterator->next;
            return temp;
        }
        const T *operator->() const
        {
            return &(m_iterator->data);
        }
        const T &operator*() const
        {
            return m_iterator->data;
        }
        const_iterator &operator=(const const_iterator &other)
        {
            m_iterator = other.m_iterator;
            return (*this);
        }
        const_iterator &operator=(const iterator &other)
        {
            m_iterator = other.m_iterator;
            return (*this);
        }
        friend class iterator;

    private:
        Node *m_iterator;
    };
    // static_assert(std::input_iterator<const_iterator>);
};

template <typename T>
ForwardList<T>::ForwardList() : m_head(nullptr), m_size(0) {} //, fake_head(std::nullopt)

template <typename T>
ForwardList<T>::ForwardList(std::size_t size) : m_size(size)
{
    Node *curNode = new Node(T());
    m_head = curNode;
    for (std::size_t i = 0; i < m_size - 1; i++)
    {
        curNode->next = new Node(T());
        curNode = curNode->next;
    }
    Node *m_tail;
    m_tail = curNode;
    m_tail->next = nullptr;
    // Node **curNode = &m_head;
    // for (std::size_t i = 0; i < size; i++)
    // {
    //     *curNode = new Node(T());
    //     curNode = &(*current)->next;
    // }
}

template <typename T>
ForwardList<T>::ForwardList(std::size_t size, const T &value) : m_size(size) // ForwardList(size)
{
    Node *curNode = new Node(value);
    // Node *curNode = Node(value);
    m_head = curNode;
    for (std::size_t i = 0; i < m_size - 1; i++)
    {
        curNode->next = new Node(value);
        // curNode->next = Node(value);
        curNode = curNode->next;
    }
    Node *m_tail;
    m_tail = curNode;
    m_tail->next = nullptr;
}

template <typename T>
ForwardList<T>::ForwardList(const ForwardList<T> &other) : m_size(other.m_size)
{
    Node *curNode = new Node(other.m_head->data);
    m_head = curNode;
    Node *curNodeOther = other.m_head;
    while (curNodeOther->next != nullptr)
    {
        curNodeOther = curNodeOther->next;
        curNode->next = new Node(curNodeOther->data);
        curNode = curNode->next;
    }
    Node *m_tail;
    m_tail = curNode;
    m_tail->next = nullptr;
}
template <typename T>
ForwardList<T>::ForwardList(std::initializer_list<T> list) : m_size(list.size())
{
    Node *curNode = m_head;
    std::size_t j = 0;
    for (auto &i : list)
    {
        curNode = new Node(i);
        if (j == m_size - 1)
        {
            break;
        }
        if (j == 0)
        {
            m_head = curNode;
        }
        curNode = curNode->next;
        j++;
    }
    Node *m_tail;
    m_tail = curNode;
    m_tail->next = nullptr;
}

template <typename T>
template <std::input_iterator iter>
ForwardList<T>::ForwardList(iter begin, iter end) : m_head(nullptr), m_size(0)
{
    if (begin == end)
    {
        return;
    }
    m_head = new Node(*begin);
    Node *m_tail;
    m_tail = m_head;
    ++begin;
    ++m_size;
    for (; begin != end; ++begin)
    {
        m_tail->next = new Node(*begin);
        m_tail = m_tail->next;
        ++m_size;
    }

    m_tail->next = nullptr;
}

template <typename T>
T &ForwardList<T>::front()
{
    return m_head->data;
}

template <typename T>
const T &ForwardList<T>::front() const
{
    return m_head->data;
}

template <typename T>
bool ForwardList<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
void ForwardList<T>::clear()
{
    Node *curNode = m_head;
    while (curNode != nullptr)
    {
        Node *nextNode = curNode->next;
        delete curNode;
        curNode = nextNode;
    }
    m_head = nullptr;
    m_size = 0;
}

template <typename T>
void ForwardList<T>::push_front(const T &value)
{
    Node *temp = m_head;
    m_head = new Node(value);
    m_head->next = temp;
    m_size++;
}

template <typename T>
void ForwardList<T>::pop_front()
{
    Node *temp = m_head;
    m_head = m_head->next;
    delete temp;
    m_size--;
}

template <typename T>
template <typename... Args>
T &ForwardList<T>::emplace_front(Args... args)
{
    Node *temp = m_head;
    m_head = new Node(std::forward<Args>(args)...);
    m_head->next = temp;
    m_size++;
    return m_head->data;
}

template <typename T>
ForwardList<T>::~ForwardList()
{
    Node *curNode = m_head;
    while (curNode != nullptr)
    {
        Node *nextNode = curNode->next;
        delete curNode;
        curNode = nextNode;
    }
    m_head = nullptr;
    m_size = 0;
}

template <typename T>
bool ForwardList<T>::operator==(const ForwardList<T> &other)
{
    if (m_size != other.m_size)
    {
        return false;
    }
    Node *curNodeL = m_head;
    Node *curNodeR = other.m_head;
    while (curNodeL != nullptr && curNodeR != nullptr)
    {
        if (curNodeL->data != curNodeR->data)
        {
            return false;
        }
        curNodeL = curNodeL->next;
        curNodeR = curNodeR->next;
    }
    return true;
    // return std::equal(begin(), end(), other.begin(), other.end());
}

template <typename T>
bool ForwardList<T>::operator!=(const ForwardList<T> &other)
{
    if (*this == other)
    {
        return false;
    }
    return true;
}

template <typename T>
ForwardList<T> &ForwardList<T>::operator=(const ForwardList<T> &other)
{
    Node *curNode = new Node(other.m_head->data);
    m_head = curNode;
    Node *curNodeOther = other.m_head;
    while (curNodeOther->next != nullptr)
    {
        curNodeOther = curNodeOther->next;
        curNode->next = new Node(curNodeOther->data);
        curNode = curNode->next;
    }
    Node *m_tail;
    m_tail = curNode;
    m_tail->next = nullptr;
    m_size = other.m_size;
    return *this;
}
// change to move assignment!!!!
template <typename T>
ForwardList<T> &ForwardList<T>::operator=(ForwardList<T> &&other) noexcept
{
    Node *curNode = new Node(other.m_head->data);
    m_head = curNode;
    Node *curNodeOther = other.m_head;
    while (curNodeOther->next != nullptr)
    {
        curNodeOther = curNodeOther->next;
        curNode->next = new Node(curNodeOther->data);
        curNode = curNode->next;
    }
    Node *m_tail;
    m_tail = curNode;
    m_tail->next = nullptr;
    m_size = other.m_size;
    return *this;
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::begin()
{
    return iterator(m_head);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::end() const
{
    return const_iterator(nullptr);
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::end()
{
    return iterator(nullptr);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::begin() const
{
    return const_iterator(m_head);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::cbegin() const
{
    return const_iterator(m_head);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::cend() const
{
    return iterator(nullptr);
}