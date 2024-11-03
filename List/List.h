
#pragma once

#include <initializer_list>
#include <optional>
#include <stdexcept>

template <typename T>
class List
{
public:
    List();
    List(std::size_t size);
    List(std::size_t size, const T &value);
    List(const List &other);
    List(List &&other) noexcept;
    List(std::initializer_list<T> init);
    template <std::input_iterator iter>
    List(iter begin, iter end);

    List &operator=(const List &other);
    List &operator=(List &&other) noexcept;

    bool empty() const;
    T &front();
    const T &front() const;
    T &back();
    const T &back() const;

    void push_back(const T &value);
    void push_front(const T &value);
    void pop_back();
    void pop_front();

    template <typename... Args>
    void emplace_back(Args &&...args);

    std::size_t size() const;
    void clear();

    bool operator==(const List &other) const;
    bool operator!=(const List &other) const;

    void merge(List &other);
    void sort();

    ~List();

    class iterator;
    iterator begin();
    iterator end();

    class const_iterator;
    const_iterator begin() const;
    const_iterator cbegin() const;
    const_iterator end() const;
    const_iterator cend() const;

    iterator erase(iterator pos);
    const_iterator erase(const_iterator pos);

    template <typename... Args>
    iterator emplace(const_iterator pos, Args &&...args);
    iterator insert(iterator pos, const T &value);

    class reverse_iterator;
    reverse_iterator rbegin();
    reverse_iterator rend();

    class const_reverse_iterator;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

private:
    struct Node
    {
        Node *next;
        Node *previous;
        std::optional<T> value;
        Node();
        template <class... Args>
        Node(Args &&...args);
        Node(std::nullopt_t, Node *_next = nullptr, Node *_prev = nullptr);
    };
    Node *fake_head;
    Node *fake_tail;

public:
    class iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        iterator();
        iterator(Node *ptr);
        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);
        bool operator==(const iterator &other) const;
        bool operator!=(const iterator &other) const;
        T *operator->() const;
        T &operator*() const;
        friend class List;

    private:
        Node *m_iterator;
    };
    ///////////////////////
    class const_iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        const_iterator();
        const_iterator(Node *ptr);
        const_iterator(const iterator &other);
        const_iterator &operator++();
        const_iterator operator++(int);
        const_iterator &operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator &other) const;
        bool operator!=(const const_iterator &other) const;
        bool operator==(const iterator &other) const;
        bool operator!=(const iterator &other) const;
        const T *operator->() const;
        const T &operator*() const;
        friend class List;

    private:
        Node *m_iterator;
    };
    ////////////////////////
    class reverse_iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        reverse_iterator();
        reverse_iterator(Node *ptr);
        reverse_iterator &operator++();
        reverse_iterator operator++(int);
        reverse_iterator &operator--();
        reverse_iterator operator--(int);
        bool operator==(const reverse_iterator &other) const;
        bool operator!=(const reverse_iterator &other) const;
        T *operator->() const;
        T &operator*() const;
        friend class List;

    private:
        Node *m_iterator;
    };
    ////////////////////////
    class const_reverse_iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        const_reverse_iterator();
        const_reverse_iterator(Node *ptr);
        const_reverse_iterator &operator++();
        const_reverse_iterator operator++(int);
        const_reverse_iterator &operator--();
        const_reverse_iterator operator--(int);
        bool operator==(const const_reverse_iterator &other) const;
        bool operator!=(const const_reverse_iterator &other) const;
        T *operator->() const;
        T &operator*() const;
        friend class List;

    private:
        Node *m_iterator;
    };
};

template <typename T>
List<T>::iterator::iterator()
{
    m_iterator = nullptr;
}

template <typename T>
List<T>::iterator::iterator(Node *ptr)
{
    m_iterator = ptr;
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator++()
{

    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    iterator temp(*this);
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return temp;
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator--()
{
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->previous;
    }
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    iterator temp(*this);
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->previous;
    }
    return temp;
}

template <typename T>
bool List<T>::iterator::operator==(const iterator &other) const
{
    return m_iterator == other.m_iterator;
}

template <typename T>
bool List<T>::iterator::operator!=(const iterator &other) const
{
    return (m_iterator != other.m_iterator);
}

template <typename T>
T *List<T>::iterator::operator->() const
{
    return &(m_iterator->value.value());
}

template <typename T>
T &List<T>::iterator::operator*() const
{
    return m_iterator->value.value();
}

template <typename T>
List<T>::const_iterator::const_iterator()
{
    m_iterator = nullptr;
}

template <typename T>
List<T>::const_iterator::const_iterator(Node *ptr)
{
    m_iterator = ptr;
}

template <typename T>
List<T>::const_iterator::const_iterator(const iterator &other)
{
    m_iterator = other.m_iterator;
}

template <typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator++()
{

    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
    const_iterator temp(*this);
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return temp;
}

template <typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator--()
{
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->previous;
    }
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
    const_iterator temp(*this);
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->previous;
    }
    return temp;
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &other) const
{
    return m_iterator == other.m_iterator;
}

template <typename T>
bool List<T>::const_iterator::operator==(const iterator &other) const
{
    return m_iterator == other.m_iterator;
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &other) const
{
    return (m_iterator != other.m_iterator);
}

template <typename T>
bool List<T>::const_iterator::operator!=(const iterator &other) const
{
    return (m_iterator != other.m_iterator);
}

template <typename T>
const T *List<T>::const_iterator::operator->() const
{
    return &(m_iterator->value.value());
}

template <typename T>
const T &List<T>::const_iterator::operator*() const
{
    return m_iterator->value.value();
}

template <typename T>
List<T>::reverse_iterator::reverse_iterator()
{
    m_iterator = nullptr;
}

template <typename T>
List<T>::reverse_iterator::reverse_iterator(Node *ptr)
{
    m_iterator = ptr;
}

template <typename T>
typename List<T>::reverse_iterator &List<T>::reverse_iterator::operator++()
{

    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->previous;
    }
    return *this;
}

template <typename T>
typename List<T>::reverse_iterator List<T>::reverse_iterator::operator++(int)
{
    reverse_iterator temp(*this);
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->previous;
    }
    return temp;
}

template <typename T>
typename List<T>::reverse_iterator &List<T>::reverse_iterator::operator--()
{
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return *this;
}

template <typename T>
typename List<T>::reverse_iterator List<T>::reverse_iterator::operator--(int)
{
    reverse_iterator temp(*this);
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return temp;
}

template <typename T>
bool List<T>::reverse_iterator::operator==(const reverse_iterator &other) const
{
    return m_iterator == other.m_iterator;
}

template <typename T>
bool List<T>::reverse_iterator::operator!=(const reverse_iterator &other) const
{
    return (m_iterator != other.m_iterator);
}

template <typename T>
T *List<T>::reverse_iterator::operator->() const
{
    return &(m_iterator->value);
}

template <typename T>
T &List<T>::reverse_iterator::operator*() const
{
    return m_iterator->value.value();
}

template <typename T>
List<T>::const_reverse_iterator::const_reverse_iterator()
{

    m_iterator = nullptr;
}

template <typename T>
List<T>::const_reverse_iterator::const_reverse_iterator(Node *ptr)
{
    m_iterator = ptr;
}

template <typename T>
typename List<T>::const_reverse_iterator &List<T>::const_reverse_iterator::operator++()
{

    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->previous;
    }
    return *this;
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator++(int)
{
    const_reverse_iterator temp(*this);
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->previous;
    }
    return temp;
}

template <typename T>
typename List<T>::const_reverse_iterator &List<T>::const_reverse_iterator::operator--()
{
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return *this;
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator--(int)
{
    const_reverse_iterator temp(*this);
    if (m_iterator != nullptr)
    {
        m_iterator = m_iterator->next;
    }
    return temp;
}

template <typename T>
bool List<T>::const_reverse_iterator::operator==(const const_reverse_iterator &other) const
{
    return m_iterator == other.m_iterator;
}

template <typename T>
bool List<T>::const_reverse_iterator::operator!=(const const_reverse_iterator &other) const
{
    return (m_iterator != other.m_iterator);
}

template <typename T>
T *List<T>::const_reverse_iterator::operator->() const
{
    return &(m_iterator->value);
}

template <typename T>
T &List<T>::const_reverse_iterator::operator*() const
{
    return m_iterator->value.value();
}

template <typename T>
List<T>::Node::Node() : value(std::in_place) {}

template <typename T>
template <class... Args>
List<T>::Node::Node(Args &&...args) : value(std::in_place, std::forward<Args>(args)...){};

template <typename T>
List<T>::Node::Node(std::nullopt_t, Node *_next, Node *_prev) : value(std::nullopt), next(_next), previous(_prev){};

template <typename T>
List<T>::List()
{

    fake_head = new Node(std::nullopt);
    fake_tail = new Node(std::nullopt);
    fake_head->next = fake_tail;
    fake_tail->previous = fake_head;
}

template <typename T>
List<T>::List(std::size_t size) : List()
{
    for (std::size_t i = 0; i < size; i++)
    {
        push_back(T());
    }
}

template <typename T>
List<T>::List(std::size_t size, const T &value) : List()
{
    for (std::size_t i = 0; i < size; i++)
    {
        push_back(value);
    }
}

template <typename T>
List<T>::List(std::initializer_list<T> init) : List()
{
    for (auto &i : init)
    {
        push_back(i);
    }
}
template <typename T>
template <std::input_iterator iter>
List<T>::List(iter begin, iter end) : List()
{
    for (auto it = begin; it != end; ++it)
    {
        push_back(*it);
    }
}

template <typename T>
List<T>::List(const List<T> &other) : List()
{
    Node *curNode = other.fake_head->next;
    while (curNode != other.fake_tail)
    {
        push_back(curNode->value.value());
        curNode = curNode->next;
    }
}

template <typename T>
List<T>::List(List &&other) noexcept : fake_head(other.fake_head), fake_tail(other.fake_tail)
{
    other.fake_head = nullptr;
    other.fake_tail = nullptr;
}

template <typename T>
List<T> &List<T>::operator=(const List &other)
{
    if (this != &other)
    {
        clear();
        Node *curNode = other.fake_head->next;
        while (curNode != other.fake_tail)
        {
            push_back(curNode->value.value());
            curNode = curNode->next;
        }
    }
    return *this;
}

template <typename T>
List<T> &List<T>::operator=(List &&other) noexcept
{
    if (this != &other)
    {
        clear();
        delete fake_head;
        delete fake_tail;

        fake_head = other.fake_head;
        fake_tail = other.fake_tail;

        other.fake_head = nullptr;
        other.fake_tail = nullptr;
    }
    return *this;
}

template <typename T>
std::size_t List<T>::size() const
{
    std::size_t size = 0;
    Node *curNode = fake_head->next;
    while (curNode != fake_tail)
    {
        curNode = curNode->next;
        size++;
    }
    return size;
}

template <typename T>
bool List<T>::empty() const
{
    return fake_head->next == fake_tail;
}

template <typename T>
T &List<T>::front()
{
    if (empty())
    {
        throw std::out_of_range("there are no elements");
    }
    return fake_head->next->value.value();
}

template <typename T>
const T &List<T>::front() const
{
    if (empty())
    {
        throw std::out_of_range("there are no elements");
    }
    return fake_head->next->value.value();
}

template <typename T>
T &List<T>::back()
{
    if (empty())
    {
        throw std::out_of_range("there is no elements");
    }
    return fake_tail->previous->value.value();
}

template <typename T>
const T &List<T>::back() const
{
    if (empty())
    {
        throw std::out_of_range("there is no elements");
    }
    return fake_tail->previous->value.value();
}

template <typename T>
void List<T>::push_back(const T &value)
{
    Node *newNode = new Node(value);
    newNode->previous = fake_tail->previous;
    newNode->next = fake_tail;
    fake_tail->previous->next = newNode;
    fake_tail->previous = newNode;
}

template <typename T>
void List<T>::push_front(const T &value)
{
    Node *newNode = new Node(value);
    newNode->next = fake_head->next;
    newNode->previous = fake_head;
    fake_head->next->previous = newNode;
    fake_head->next = newNode;
}

template <typename T>
void List<T>::pop_back()
{
    if (empty())
    {
        throw std::out_of_range("there are no elements");
    }
    Node *oldNode = fake_tail->previous;
    oldNode->previous->next = fake_tail;
    fake_tail->previous = oldNode->previous;
    delete oldNode;
}

template <typename T>
void List<T>::pop_front()
{
    if (empty())
    {
        throw std::out_of_range("there are no elements");
    }
    Node *oldNode = fake_head->next;
    fake_head->next = oldNode->next;
    oldNode->next->previous = fake_head;
    delete oldNode;
}

template <typename T>
template <typename... Args>
void List<T>::emplace_back(Args &&...args)
{
    Node *newNode = new Node(std::forward<Args>(args)...);
    newNode->previous = fake_tail->previous;
    newNode->next = fake_tail;
    fake_tail->previous->next = newNode;
    fake_tail->previous = newNode;
}

template <typename T>
void List<T>::clear()
{
    while (!empty())
    {
        pop_back();
    }
}

template <typename T>
bool List<T>::operator==(const List<T> &other) const
{
    Node *curThis = fake_head->next;
    Node *curOther = other.fake_head->next;
    while (curThis != fake_tail && curOther != other.fake_tail)
    {
        if (curThis->value != curOther->value)
        {
            return false;
        }
        curThis = curThis->next;
        curOther = curOther->next;
    }
    return (curThis == fake_tail && curOther == other.fake_tail);
}

template <typename T>
bool List<T>::operator!=(const List<T> &other) const
{
    return !(*this == other);
}

template <typename T>
void List<T>::merge(List &other)
{
    if (*this == other)
        return;

    auto it = begin();
    auto otherit = other.begin();
    while (otherit != other.end())
    {
        if (it == end() || *it >= *otherit)
        {
            insert(it, *otherit);
            otherit++;
        }
        else
        {
            if (it != end())
            {
                it++;
            }
        }
    }
}

template <typename T>
void List<T>::sort()
{
    if (fake_head->next == fake_tail || fake_head->next->next == fake_tail)
    {
        return;
    }
    bool swapped;
    Node *curNode = fake_head->next;
    while (curNode != fake_tail->previous)
    {
        Node *curNode2 = fake_head->next;
        while (curNode2 != fake_tail->previous)
        {
            if (curNode2->value.value() > curNode2->next->value.value())
            {
                std::swap(curNode2->value, curNode2->next->value);
                swapped = true;
            }
            curNode2 = curNode2->next;
        }
        if (swapped == false)
        {
            return;
        }
        curNode = curNode->next;
    }
}

template <typename T>
List<T>::~List()
{
    clear();
    delete fake_head;
    delete fake_tail;
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator pos)
{
    if (pos.m_iterator == fake_head || pos.m_iterator == fake_tail)
    {
        throw std::out_of_range("no element");
    }
    Node *nodeRemove = pos.m_iterator;
    Node *nextNode = nodeRemove->next;
    nodeRemove->previous->next = nextNode;
    nextNode->previous = nodeRemove->previous;
    delete nodeRemove;
    return iterator(nextNode);
}

template <typename T>
typename List<T>::const_iterator List<T>::erase(const_iterator pos)
{
    if (pos.m_iterator == fake_head || pos.m_iterator == fake_tail)
    {
        throw std::out_of_range("no element");
    }
    Node *nodeRemove = pos.m_iterator;
    Node *nextNode = nodeRemove->next;
    nodeRemove->previous->next = nextNode;
    nextNode->previous = nodeRemove->previous;
    delete nodeRemove;
    return const_iterator(nextNode);
}

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::emplace(const_iterator pos, Args &&...args)
{
    Node *curNode = pos.m_iterator;
    Node *newNode = new Node(std::forward<Args>(args)...);
    newNode->next = curNode;
    newNode->previous = curNode->previous;
    curNode->previous->next = newNode;
    curNode->previous = newNode;
    return iterator(newNode);
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos, const T &value)
{
    return emplace(pos, value);
}

template <typename T>
typename List<T>::iterator List<T>::begin()
{
    return iterator(fake_head->next);
}

template <typename T>
typename List<T>::iterator List<T>::end()
{
    return iterator(fake_tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return const_iterator(fake_head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::cbegin() const
{
    return const_iterator(fake_head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const
{
    return const_iterator(fake_tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::cend() const
{
    return const_iterator(fake_tail);
}

template <typename T>
typename List<T>::reverse_iterator List<T>::rbegin()
{
    return reverse_iterator(fake_tail->previous);
}

template <typename T>
typename List<T>::reverse_iterator List<T>::rend()
{
    return reverse_iterator(fake_head);
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::rbegin() const
{
    return const_reverse_iterator(fake_tail->previous);
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::crbegin() const
{
    return const_reverse_iterator(fake_tail->previous);
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::rend() const
{
    return const_reverse_iterator(fake_head);
}

template <typename T>
typename List<T>::const_reverse_iterator List<T>::crend() const
{
    return const_reverse_iterator(fake_head);
}