#include "Set.h"
#include <iostream>

Set::Node::Node(int data) : value(data), left(nullptr), right(nullptr), parent(nullptr), height(1) {}

Set::Set() : root(nullptr) {}

Set::Set(std::initializer_list<int> init)
{
    for (auto &i : init)
    {
        insert(i);
    }
}

Set::Set(const Set &other)
{
}

bool Set::empty() const
{
    return root == nullptr;
}

std::size_t Set::size() const
{
    return size(root);
}

std::size_t Set::size(Node *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return size(node->left) + size(node->right) + 1;
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
    root = insert(root, value);
}

void Set::erase(int value)
{
    Node *node = contains(root, value);
    if (node != nullptr)
    {
        erase(node);
    }
}

Set::Node *Set::insert(Node *node, int value)
{
    
    if (node == nullptr)
    {
        return new Node(value);
    }
    if (node->value > value)
    {
        node->left = insert(node->left, value);
    }
    else if (node->value < value)
    {
        node->right = insert(node->right, value);
    }
    else
    {
        return node;
    }
    node->height = 1 + std::max(height(node->left), height(node->right));
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
        delete node;
        node = nullptr;
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
        if (height(node->left->left) >= height(node->left->right))
        {
            return right_rotation(node);
        }
        else
        {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
    }

    if (balance_factor < -1)
    {
        if (height(node->right->right) >= height(node->right->left))
        {
            return left_rotation(node);
        }
        else
        {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }
    }
    return node;
}

Set::Node *Set::right_rotation(Node *node)
{
    Node *left = node->left;
    Node *leftright = left->right;
    left->right = node;
    node->left = leftright;
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
    update_height(node);
    update_height(right);
    return right;
}

void Set::update_height(Node *node)
{
    node->height = std::max(height(node->left), height(node->right)) + 1;
}