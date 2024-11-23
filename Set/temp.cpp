#pragma once
#include <iostream>
/*
  Your task here is to define a set of int egers. Since this is not a template class
  you must declare your functions in the header file and define them in .cpp file.
*/

class Set
{
public:
  Set();
  bool empty() const;
  std::size_t size() const;
  bool contains(int value) const;
  void insert(int value);
  // template<std::input_iterator iter>
  void erase(int value);

private:
  struct Node
  {
    int value;
    Node *left;
    Node *right;
    int height;
    Node(int data);
  };
  Node *root;
  std::size_t nodes(Node *node) const;
  Node *addNode(Node *node, int value);
  Node *contain(Node *node, int value) const;
  void deleteNode(Node *node);

public:
  class iterator
  {
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    iterator();
    iterator(Node *ptr);

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


#include "Set.h"
#include <iostream>

Set::Node::Node(int data) : value(data), left(nullptr), right(nullptr), height(1) {}

Set::Set() : root(nullptr) {}

bool Set::empty() const
{
    return root == nullptr;
}

std::size_t Set::size() const
{
    return nodes(root);
}

std::size_t Set::nodes(Node *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return nodes(node->left) + nodes(node->right) + 1;
}

bool Set::contains(int value) const
{
    if (contain(root, value) == nullptr)
    {
        return false;
    }
    return true;
}

void Set::insert(int value)
{
    root = addNode(root, value);
}

// template <std::input_iterator iter>
void Set::erase(int value)
{
    Node *node = contain(root, value);
    if (node != nullptr)
    {
        deleteNode(node);
    }
}

Set::Node *Set::addNode(Node *node, int value)
{
    if (node == nullptr)
    {
        return new Node(value);
    }
    if (node->value > value)
    {
        node->left = addNode(node->left, value);
    }
    else if (node->value < value)
    {
        node->right = addNode(node->right, value);
    }
    else
    {
        return node;
    }
    return node;
}

Set::Node *Set::contain(Node *node, int value) const
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->value > value)
    {
        return contain(node->left, value);
    }
    if (node->value < value)
    {
        return contain(node->right, value);
    }
    return node;
}

void Set::deleteNode(Node *node)
{
    if (node->left == nullptr && node->right == nullptr)
    {
        delete node;
        return;
    }
    if (node->left != nullptr && node->right == nullptr)
    {
        Node *temp = node->left;
        delete node;
        node = temp;
        return;
    }
    if (node->right != nullptr && node->left == nullptr)
    {
        Node *temp = node->right;
        delete node;
        node = temp;
        return;
    }
    Node **successor = &(node->right);
    while ((*successor)->left != nullptr)
    {
        successor = &((*successor)->left);
    }
    node->value = std::move((*successor)->value);
    deleteNode(*successor);
}