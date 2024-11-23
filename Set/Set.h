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
  

  class iterator;
  iterator find(int value);

  class const_iterator;
  const_iterator find(int value) const;

private:
  Node *root;
  std::size_t size(Node *node) const;
  Node *insert(Node *node, int value);
  Node *contains(Node *node, int value) const;
  void erase(Node *node);
  int height(Node *node);
  Node *balance(Node *node);
  Node *left_rotation(Node *node);
  Node *right_rotation(Node *node);
  void update_height(Node *node);

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