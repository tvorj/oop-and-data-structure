#pragma once
#include <iostream>
#include <initializer_list>
/*
  Your task here is to define a set of integers. Since this is not a template class
  you must declare your functions in the header file and define them in .cpp file.
*/

class Set
{
private:
  struct Node
  {
    int value;
    Node *left;
    Node *right;
    Node *parent;
    int height;
    Node(int data);
  };

public:
  Set();
  Set(std::initializer_list<int> init);
  Set(const Set &other);
  bool empty() const;
  std::size_t size() const;
  bool contains(int value) const;
  void insert(int value);
  void erase(int value);
  bool operator==(const Set &other) const;
  bool operator!=(const Set &other) const;

  class iterator;
  iterator find(int value);
  iterator begin();
  iterator end();

  class const_iterator;
  const_iterator find(int value) const;

private:
  Node *root;
  std::size_t node_count;
  Node *insert(Node *node, int value, Node *parent);
  Node *contains(Node *node, int value) const;
  void erase(Node *node);
  int height(Node *node);
  Node *balance(Node *node);
  Node *left_rotation(Node *node);
  Node *right_rotation(Node *node);
  void update_height(Node *node);
  Node *copy(Node *other, Node *parent);
  bool equal(Node *current, Node *other) const;

public:
  class iterator
  {
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    iterator();
    iterator(Node *ptr);
    int &operator*() const;
    iterator &operator++();
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    friend class Set;

  private:
    Node *m_iterator;
  };
  class const_iterator
  {
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    const_iterator();
    const_iterator(Node *ptr);

  private:
    Node *m_iterator;
  };
  class reverse_iterator
  {
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    reverse_iterator();
    reverse_iterator(Node *ptr);

  private:
    Node *m_iterator;
  };
  class const_reverse_iterator
  {
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    const_reverse_iterator();
    const_reverse_iterator(Node *ptr);

  private:
    Node *m_iterator;
  };
};


Set::Node::Node(int data) : value(data), left(nullptr), right(nullptr), parent(nullptr), height(1) {}

Set::Set() : root(nullptr), node_count(0) {}

Set::Set(std::initializer_list<int> init)
{
    for (auto &i : init)
    {
        insert(i);
    }
}

Set::Set(const Set &other) : root(nullptr), node_count(0)
{
    if (other.root != nullptr)
    {
        root = copy(other.root, nullptr);
        node_count = other.node_count;
    }
}

bool Set::empty() const
{
    return root == nullptr;
}

std::size_t Set::size() const
{
    return node_count;
}

bool Set::contains(int value) const
{
    if (contains(root, value) == nullptr)
    {
        return false;
    }
    return true;
}

void Set::insert(int value)
{
    root = insert(root, value, nullptr);
}

void Set::erase(int value)
{
    Node *node = contains(root, value);
    if (node != nullptr)
    {
        erase(node);
    }
}

Set::Node *Set::insert(Node *node, int value, Node *parent)
{
    if (node == nullptr)
    {
        node_count++;
        Node *new_node = new Node(value);
        new_node->parent = parent;
        return new_node;
    }
    if (node->value > value)
    {
        node->left = insert(node->left, value, node);
    }
    else if (node->value < value)
    {
        node->right = insert(node->right, value, node);
    }
    else
    {
        return node;
    }
    return balance(node);
}

Set::Node *Set::contains(Node *node, int value) const
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->value > value)
    {
        return contains(node->left, value);
    }
    if (node->value < value)
    {
        return contains(node->right, value);
    }
    return node;
}

void Set::erase(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->left == nullptr && node->right == nullptr)
    {
        if (node->parent != nullptr)
        {
            if (node->parent->left == node)
            {
                node->parent->left = nullptr;
            }
            else
            {
                node->parent->right = nullptr;
            }
        }
        else
        {
            root = nullptr;
        }
        delete node;
        node_count--;
        return;
    }
    if (node->left == nullptr || node->right == nullptr)
    {
        Node *child = (node->left != nullptr) ? node->left : node->right;

        child->parent = node->parent;

        if (node->parent != nullptr)
        {
            if (node->parent->left == node)
            {
                node->parent->left = child;
            }
            else
            {
                node->parent->right = child;
            }
        }
        else
        {
            root = child;
        }
        delete node;
        node_count--;
        return;
    }
    Node **successor = &(node->right);
    while ((*successor)->left != nullptr)
    {
        successor = &((*successor)->left);
    }
    node->value = std::move((*successor)->value);
    erase(*successor);
}

int Set::height(Node *node)
{
    return node == nullptr ? 0 : node->height;
}

Set::Node *Set::balance(Node *node)
{
    update_height(node);
    int balance_factor = height(node->left) - height(node->right);
    if (balance_factor > 1)
    {
        if (height(node->left->left) < height(node->left->right))
        {
            node->left = left_rotation(node->left);
            if (node->left != nullptr)
            {
                node->left->parent = node;
            }
        }
        return right_rotation(node);
    }

    if (balance_factor < -1)
    {
        if (height(node->right->right) < height(node->right->left))
        {
            node->right = right_rotation(node->right);
            if (node->right != nullptr)
            {
                node->right->parent = node;
            }
        }
        return left_rotation(node);
    }
    return node;
}

Set::Node *Set::right_rotation(Node *node)
{
    Node *left = node->left;
    Node *leftright = left->right;
    left->right = node;
    node->left = leftright;
    if (leftright != nullptr)
    {
        leftright->parent = node;
    }
    left->parent = node->parent;
    node->parent = left;
    update_height(node);
    update_height(left);
    return left;
}

Set::Node *Set::left_rotation(Node *node)
{
    Node *right = node->right;
    Node *rightleft = right->left;
    right->left = node;
    node->right = rightleft;
    if (rightleft != nullptr)
    {
        rightleft->parent = node;
    }
    right->parent = node->parent;
    node->parent = right;
    update_height(node);
    update_height(right);
    return right;
}

void Set::update_height(Node *node)
{
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

Set::Node *Set::copy(Node *other, Node *parent)
{
    if (other == nullptr)
    {
        return nullptr;
    }

    Node *new_node = new Node(other->value);
    new_node->parent = parent;

    new_node->left = copy(other->left, new_node);
    new_node->right = copy(other->right, new_node);

    // Возвращаем скопированный узел
    return new_node;
}

bool Set::operator==(const Set &other) const
{
    return equal(root, other.root);
}

bool Set::operator!=(const Set &other) const
{
    return !(*this == other);
}

bool Set::equal(Node *current, Node *other) const
{
    if (current == nullptr && other == nullptr)
        return true;
    if (current == nullptr || other == nullptr)
        return false;
    return current->value == other->value && equal(current->left, other->left) && equal(current->right, other->right);
}

Set::iterator::iterator() : m_iterator(nullptr) {}

Set::iterator::iterator(Node *ptr) : m_iterator(ptr) {}

int &Set::iterator::operator*() const
{
    return m_iterator->value;
}

Set::iterator &Set::iterator::operator++()
{
    if (m_iterator == nullptr)
    {
        throw std::out_of_range("Iterator cannot be incremented");
    }

    if (m_iterator->right != nullptr)
    {
        m_iterator = m_iterator->right;
        while (m_iterator->left != nullptr)
        {
            m_iterator = m_iterator->left;
        }
    }
    else
    {
        Node *parent = m_iterator->parent;
        while (parent != nullptr && m_iterator == parent->right)
        {
            m_iterator = parent;
            parent = parent->parent;
        }
        m_iterator = parent;
    }

    return *this;
}

bool Set::iterator::operator==(const iterator &other) const
{
    return m_iterator == other.m_iterator;
}

bool Set::iterator::operator!=(const iterator &other) const
{
    return !(*this == other);
}

Set::iterator Set::begin()
{
    Node *current = root;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return iterator(current);
}

Set::iterator Set::end()
{
    return iterator(nullptr);
}