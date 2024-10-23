// Create a custom singly linked list class that would support all the functionality
// given in main.cpp.

// Again: Declare your functions inside your class, but define them outside of it.
#pragma once
#include <iostream>
#include <optional>
template <typename T>
class ForwardList
{
public:
    ForwardList();
    ForwardList(std::size_t size);
    ForwardList(std::size_t size, const T &value);
    ForwardList(const ForwardList &other);
    ForwardList(ForwardList &&other) noexcept;
    ForwardList(std::initializer_list<T> list);
    template <std::input_iterator iter>
    ForwardList(iter begin, iter end);

    T &front();
    const T &front() const;
    bool empty() const;
    void clear();

    void push_front(const T &value);
    void pop_front();
    template <typename... Args>
    T &emplace_front(Args &&...args);

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
    iterator erase_after(const_iterator pos);
    iterator insert_after(const_iterator pos, const T &value);

private:
    struct Node
    {
        std::optional<T> data;
        Node *next;
        Node();
        template <class... Args>
        Node(Args &&...args);
        Node(std::nullopt_t, Node *t_next = nullptr);
    };
    Node *fake_head;
    std::size_t m_size;

public:
    class iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        iterator(Node *ptr);
        iterator(const const_iterator &other);
        iterator(const iterator &other);
        bool operator==(const iterator &other) const;
        bool operator!=(const iterator &other) const;
        // prefix
        iterator &operator++();
        // postfix
        iterator operator++(int);
        T *operator->() const;
        T &operator*() const;
        iterator &operator=(const const_iterator &other);
        iterator &operator=(const iterator &other);
        friend class const_iterator;
        friend class ForwardList;

    private:
        Node *m_iterator;
    };
    class const_iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        const_iterator(Node *ptr);
        const_iterator(const const_iterator &other);
        const_iterator(const iterator &other);
        bool operator==(const const_iterator &other) const;
        bool operator!=(const const_iterator &other) const;
        // prefix
        const_iterator &operator++();
        // postfix
        const_iterator operator++(int);
        const T *operator->() const;
        const T &operator*() const;
        const_iterator &operator=(const const_iterator &other);
        const_iterator &operator=(const iterator &other);
        friend class iterator;
        friend class ForwardList;

    private:
        Node *m_iterator;
    };
};

template <typename T>
ForwardList<T>::ForwardList() : m_size(0)
{
    fake_head = new Node(std::nullopt);
}

template <typename T>
ForwardList<T>::ForwardList(std::size_t size) : m_size(size)
{
    fake_head = new Node(std::nullopt);
    Node *curNode = new Node(T());
    fake_head->next = curNode;
    for (std::size_t i = 0; i < m_size - 1; i++)
    {
        curNode->next = new Node(T());
        curNode = curNode->next;
    }
    Node *m_tail;
    m_tail = curNode;
    m_tail->next = nullptr;
}

template <typename T>
ForwardList<T>::ForwardList(std::size_t size, const T &value) : m_size(size)
{
    fake_head = new Node(std::nullopt);
    Node *curNode = new Node(value);
    fake_head->next = curNode;
    for (std::size_t i = 0; i < m_size - 1; i++)
    {
        curNode->next = new Node(value);
        curNode = curNode->next;
    }
    Node *m_tail;
    m_tail = curNode;
    m_tail->next = nullptr;
}

template <typename T>
ForwardList<T>::ForwardList(const ForwardList<T> &other) : m_size(other.m_size)
{
    fake_head = new Node(std::nullopt);
    Node *curNode = new Node(other.fake_head->next->data.value());
    fake_head->next = curNode;
    Node *curNodeOther = other.fake_head->next;
    while (curNodeOther->next != nullptr)
    {
        curNodeOther = curNodeOther->next;
        curNode->next = new Node(curNodeOther->data.value());
        curNode = curNode->next;
    }
    Node *m_tail;
    m_tail = curNode;
    m_tail->next = nullptr;
}

template <typename T>
ForwardList<T>::ForwardList(ForwardList<T> &&other) noexcept : ForwardList()
{
    std::swap(fake_head, other.fake_head);
    std::swap(m_size, other.m_size);
}
template <typename T>
ForwardList<T>::ForwardList(std::initializer_list<T> list) : m_size(list.size())
{
    fake_head = new Node(std::nullopt);
    Node *curNode = fake_head;
    std::size_t j = 0;
    for (auto &i : list)
    {
        curNode->next = new Node(i);
        curNode = curNode->next;
        j++;
    }
    Node *m_tail;
    m_tail = curNode;
    m_tail->next = nullptr;
}

template <typename T>
template <std::input_iterator iter>
ForwardList<T>::ForwardList(iter begin, iter end) : m_size(0)
{
    if (begin == end)
    {
        return;
    }
    fake_head = new Node(std::nullopt);
    fake_head->next = nullptr;
    fake_head->next = new Node(*begin);
    Node *m_tail;
    m_tail = fake_head->next;
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
    return fake_head->next->data.value();
}

template <typename T>
const T &ForwardList<T>::front() const
{
    return fake_head->next->data.value();
}

template <typename T>
bool ForwardList<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
void ForwardList<T>::clear()
{
    Node *curNode = fake_head->next;
    while (curNode != nullptr)
    {
        Node *nextNode = curNode->next;
        delete curNode;
        curNode = nextNode;
    }
    fake_head->next = nullptr;
    m_size = 0;
}

template <typename T>
void ForwardList<T>::push_front(const T &value)
{
    Node *temp = fake_head->next;
    fake_head->next = new Node(value);
    fake_head->next->next = temp;
    m_size++;
}

template <typename T>
void ForwardList<T>::pop_front()
{
    if (fake_head->next == nullptr)
    {
        return;
    }
    Node *temp = fake_head->next;
    fake_head->next = fake_head->next->next;
    delete temp;
    m_size--;
}

template <typename T>
template <typename... Args>
T &ForwardList<T>::emplace_front(Args &&...args)
{
    Node *temp = fake_head->next;
    fake_head->next = new Node(std::forward<Args>(args)...);
    fake_head->next->next = temp;
    m_size++;
    return fake_head->next->data.value();
}

template <typename T>
ForwardList<T>::~ForwardList()
{
    Node *curNode = fake_head->next;
    while (curNode != nullptr)
    {
        Node *nextNode = curNode->next;
        delete curNode;
        curNode = nextNode;
    }
    fake_head->next = nullptr;
    m_size = 0;
}

template <typename T>
bool operator==(const ForwardList<T> &lhs, const ForwardList<T> &rhs)
{
    if (lhs.begin() == lhs.end() && rhs.begin() == rhs.end())
    {
        return true;
    }
    auto itL = lhs.begin();
    auto itR = rhs.begin();
    while (itL != lhs.end() && itR != rhs.end())
    {
        if (*itL != *itR)
        {
            return false;
        }
        itL++;
        itR++;
    }
    return itL == lhs.end() && itR == rhs.end();
}

template <typename T>
bool operator!=(const ForwardList<T> &lhs, const ForwardList<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
ForwardList<T> &ForwardList<T>::operator=(const ForwardList<T> &other)
{
    Node *curNode = new Node(other.fake_head->next->data.value());
    fake_head->next = curNode;
    Node *curNodeOther = other.fake_head->next;
    while (curNodeOther->next != nullptr)
    {
        curNodeOther = curNodeOther->next;
        curNode->next = new Node(curNodeOther->data.value());
        curNode = curNode->next;
    }
    Node *m_tail;
    m_tail = curNode;
    m_tail->next = nullptr;
    m_size = other.m_size;
    return *this;
}

template <typename T>
ForwardList<T> &ForwardList<T>::operator=(ForwardList<T> &&other) noexcept
{
    std::swap(fake_head, other.fake_head);
    std::swap(m_size, other.m_size);
    return (*this);
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::begin()
{
    return iterator(fake_head->next);
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
    return const_iterator(fake_head->next);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::cbegin() const
{
    return const_iterator(fake_head->next);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::cend() const
{
    return const_iterator(nullptr);
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::before_begin()
{
    return iterator(fake_head);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::before_begin() const
{
    return const_iterator(fake_head);
}

template <typename T>
typename ForwardList<T>::const_iterator ForwardList<T>::cbefore_begin() const
{
    return const_iterator(fake_head);
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::insert_after(const_iterator pos, const T &value)
{
    if (pos.m_iterator == nullptr)
    {
        throw std::invalid_argument("invalid iterator");
    }
    Node *curNode = new Node(value);
    Node *temp = pos.m_iterator->next;
    pos.m_iterator->next = curNode;
    curNode->next = temp;
    m_size++;
    return iterator(curNode);
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::erase_after(const_iterator pos)
{
    if (pos.m_iterator == nullptr)
    {
        throw std::invalid_argument("invalid iterator");
    }
    if (pos.m_iterator->next == nullptr)
    {
        return nullptr;
    }
    Node *temp = pos.m_iterator->next->next;
    delete pos.m_iterator->next;
    pos.m_iterator->next = temp;
    m_size--;
    return iterator(temp);
}
template <typename T>
bool ForwardList<T>::iterator::operator==(const iterator &other) const
{
    return m_iterator == other.m_iterator;
}
template <typename T>
bool ForwardList<T>::iterator::operator!=(const iterator &other) const
{
    return m_iterator != other.m_iterator;
}

template <typename T>
ForwardList<T>::iterator &ForwardList<T>::iterator::operator++()
{
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return *this;
}

template <typename T>
ForwardList<T>::iterator ForwardList<T>::iterator::operator++(int)
{
    iterator temp(*this);
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return temp;
}
template <typename T>
T *ForwardList<T>::iterator::operator->() const
{
    return &(m_iterator->data.value());
}
template <typename T>
T &ForwardList<T>::iterator::operator*() const
{
    return m_iterator->data.value();
}
template <typename T>
ForwardList<T>::iterator &ForwardList<T>::iterator::operator=(const const_iterator &other)
{
    m_iterator = other.m_iterator;
    return (*this);
}
template <typename T>
ForwardList<T>::iterator &ForwardList<T>::iterator::operator=(const iterator &other)
{
    m_iterator = other.m_iterator;
    return (*this);
}

template <typename T>
bool ForwardList<T>::const_iterator::operator==(const const_iterator &other) const
{
    return m_iterator == other.m_iterator;
}
template <typename T>
bool ForwardList<T>::const_iterator::operator!=(const const_iterator &other) const
{
    return m_iterator != other.m_iterator;
}

template <typename T>
ForwardList<T>::const_iterator &ForwardList<T>::const_iterator::operator++()
{
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return *this;
}

template <typename T>
ForwardList<T>::const_iterator ForwardList<T>::const_iterator::operator++(int)
{
    const_iterator temp(*this);
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return temp;
}
template <typename T>
const T *ForwardList<T>::const_iterator::operator->() const
{
    return &(m_iterator->data.value());
}
template <typename T>
const T &ForwardList<T>::const_iterator::operator*() const
{
    return m_iterator->data.value();
}
template <typename T>
ForwardList<T>::const_iterator &ForwardList<T>::const_iterator::operator=(const const_iterator &other)
{
    m_iterator = other.m_iterator;
    return (*this);
}
template <typename T>
ForwardList<T>::const_iterator &ForwardList<T>::const_iterator::operator=(const iterator &other)
{
    m_iterator = other.m_iterator;
    return (*this);
}
template <typename T>
ForwardList<T>::Node::Node() : data(std::in_place){};

template <typename T>
template <class... Args>
ForwardList<T>::Node::Node(Args &&...args) : data(std::in_place, std::forward<Args>(args)...){};

template <typename T>
ForwardList<T>::Node::Node(std::nullopt_t, Node *t_next) : data(std::nullopt), next(t_next){};

template <typename T>
ForwardList<T>::iterator::iterator(Node *ptr) : m_iterator(ptr) {}
template <typename T>
ForwardList<T>::iterator::iterator(const const_iterator &other) : m_iterator(other.m_iterator) {}
template <typename T>
ForwardList<T>::iterator::iterator(const iterator &other) : m_iterator(other.m_iterator) {}

template <typename T>
ForwardList<T>::const_iterator::const_iterator(Node *ptr) : m_iterator(ptr) {}
template <typename T>
ForwardList<T>::const_iterator::const_iterator(const const_iterator &other) : m_iterator(other.m_iterator) {}
template <typename T>
ForwardList<T>::const_iterator::const_iterator(const iterator &other) : m_iterator(other.m_iterator) {}