#include <iostream>
#include <algorithm>

template <typename T>
struct Node
{
    T value;
    Node *left;
    Node *right;
    int height;
    Node(const T &data) : value(data), height(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class AVL
{
public:
    AVL() : root(nullptr) {}

    void insert(const T &data, int (*compare)(T, T))
    {
        root = add_node(root, data, compare);
    }

    int height(Node<T> *node)
    {
        return node == nullptr ? 0 : node->height;
    }

    void update_height(Node<T> *node)
    {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    Node<T> *right_rotation(Node<T> *node)
    {
        Node<T> *left = node->left;
        Node<T> *leftright = left->right;
        left->right = node;
        node->left = leftright;
        update_height(node);
        update_height(left);
        return left;
    }

    Node<T> *left_rotation(Node<T> *node)
    {
        Node<T> *right = node->right;
        Node<T> *rightleft = right->left;
        right->left = node;
        node->right = rightleft;
        update_height(node);
        update_height(right);
        return right;
    }

    Node<T> *balance(Node<T> *node)
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

    void in_order_traversal()
    {
        in_order_recursive(root);
    }

private:
    Node<T> *root;
    void in_order_recursive(Node<T> *node)
    {
        if (node != nullptr)
        {
            in_order_recursive(node->left);
            std::cout << node->value << std::endl;
            in_order_recursive(node->right);
        }
    }
    Node<T> *add_node(Node<T> *node, const T &data, int (*compare)(T, T))
    {
        if (node == nullptr)
        {
            return new Node<T>(data);
        }

        if (compare(data, node->value) < 0)
        {
            node->left = add_node(node->left, data, compare);
        }
        else if (compare(data, node->value) > 0)
        {
            node->right = add_node(node->right, data, compare);
        }
        else
        {
            return node;
        }
        return balance(node);
    }
};

template <typename T>
int compare(T a, T b)
{
    return b - a;
}

int main()
{
    AVL<int> tree;

    tree.insert(5, compare);
    tree.insert(1, compare);
    tree.insert(5, compare);
    tree.insert(2, compare);
    tree.insert(9, compare);
    tree.insert(3, compare);
    tree.insert(10, compare);
    tree.in_order_traversal();
    return 0;
}
