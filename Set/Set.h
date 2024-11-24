#pragma once
#include <iostream>
#include <initializer_list>
#include <cstddef>
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
  Set(Set &&other);

  bool empty() const;
  std::size_t size() const;

  bool contains(int value) const;
  void insert(int value);
  void erase(int value);
  void clear();

  bool operator==(const Set &other) const;
  bool operator!=(const Set &other) const;
  Set &operator=(const Set &other);

  ~Set();

  class iterator;
  iterator find(int value);
  void erase(iterator it);

  iterator begin();
  iterator end();

  iterator lower_bound(int value);
  iterator upper_bound(int value);

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
  void clear(Node *node);

public:
  class iterator
  {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = const int;
    iterator();
    const int &operator*() const;
    int *operator->() const;
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    friend class Set;

  private:
    Node *m_iterator;
    iterator(Node *ptr);
  };
};