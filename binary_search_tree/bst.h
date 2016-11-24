#pragma once
#include <initializer_list>

template <typename T>
class BinarySearchTree
{
    friend std::ostream& operator<<(std::ostream& out, BinarySearchTree<T> const& tree)
    {
        return tree.print(out);
    }

public:
    BinarySearchTree();
    BinarySearchTree(std::initializer_list<T> l);
    ~BinarySearchTree();

    BinarySearchTree(BinarySearchTree const&) = delete;
    BinarySearchTree& operator=(BinarySearchTree const&) = delete;
    BinarySearchTree(BinarySearchTree const&&) = delete;
    BinarySearchTree& operator=(BinarySearchTree const&&) = delete;

    void insert(T const& val);
    void remove(T const& val);
    bool search(T const& val);

private:
    struct Node
    {
        Node(T const& val) : val(val), left(nullptr), right(nullptr) {};
        ~Node() {};
        
        Node(Node const&) = delete;
        Node& operator=(Node const&) = delete;
        Node(Node const&&) = delete;
        Node& operator=(Node const&&) = delete;

        T     val;
        Node* left;
        Node* right;
    };

    void remove_node(Node* node, Node* parent);
    void swap_successor(Node* node);
    void swap_predecessor(Node* node);

    void release_tree(Node* root);

    std::ostream& print(std::ostream& out) const;
    void print_inorder(std::ostream& out, Node const* node) const;
    void print_preorder(std::ostream& out, Node const* node) const;
    void print_postorder(std::ostream& out, Node const* node) const;

    Node* m_root;
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
    : m_root(nullptr)
{}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(std::initializer_list<T> l)
    : m_root(nullptr)
{
    for (auto const& val : l)
    {
        insert(val);
    }
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    release_tree(m_root);
}

template <typename T>
void BinarySearchTree<T>::release_tree(BinarySearchTree<T>::Node* root)
{
    if (root)
    {
        release_tree(root->left);
        release_tree(root->right);
        delete root;
    }
}

template <typename T>
std::ostream& BinarySearchTree<T>::print(std::ostream& out) const
{
    out << "Preorder:\t";
    print_preorder(out, m_root);
    out << std::endl;

    out << "Inorder:\t";
    print_inorder(out, m_root);
    out << std::endl;

    out << "Postorder:\t";
    print_postorder(out, m_root);
    out << std::endl;

    return out;
}

template <typename T>
void BinarySearchTree<T>::print_preorder(std::ostream& out, Node const* root) const
{
    if (root)
    {
        out << ' ' << root->val;
        print_preorder(out, root->left);
        print_preorder(out, root->right);
    }
}

template <typename T>
void BinarySearchTree<T>::print_inorder(std::ostream& out, Node const* root) const
{
    if (root)
    {
        print_inorder(out, root->left);
        out << ' ' << root->val;
        print_inorder(out, root->right);
    }
}

template <typename T>
void BinarySearchTree<T>::print_postorder(std::ostream& out, Node const* root) const
{
    if (root)
    {
        print_postorder(out, root->left);
        print_postorder(out, root->right);
        out << ' ' << root->val;
    }
}

template <typename T>
void BinarySearchTree<T>::insert(T const& val)
{
    if (!m_root)
    {
        m_root = new Node(val);
    }
    else
    {
        Node* ptr = m_root;
        Node* parent = nullptr;
        while (ptr)
        {
            parent = ptr;
            if (val > ptr->val)
            {
                ptr = ptr->right;
            }
            else
            {
                ptr = ptr->left;
            }
        }

        if (val > parent->val)
        {
            parent->right = new Node(val);
        }
        else
        {
            parent->left = new Node(val);
        }
    }
}

template <typename T>
void BinarySearchTree<T>::remove(T const& val)
{
    Node* parent = nullptr;
    Node* ptr = m_root;
    while (ptr)
    {
        parent = ptr;
        if (val > ptr->val)
        {
            ptr = ptr->right;
        }
        else if (val < ptr->val)
        {
            ptr = ptr->left;
        }
        else
        {
            break;
        }
    }
    remove_node(ptr, parent);
}

template <typename T>
void BinarySearchTree<T>::swap_successor(BinarySearchTree<T>::Node* node)
{
    Node* ptr_parent = node;
    Node* ptr = node->right;
    while (ptr->left)
    {
        ptr_parent = ptr;
        ptr = ptr->left;
    }

    // Swap value of the node rather than the node object
    node->val = ptr->val;

    if (node == ptr_parent)
    {
        ptr_parent->right = ptr->right;
    }
    else
    {
        ptr_parent->left = ptr->right;
    }
    delete ptr;
}

template <typename T>
void BinarySearchTree<T>::swap_predecessor(BinarySearchTree<T>::Node* node)
{
    Node* ptr_parent = node;
    Node* ptr = node->left;
    while (ptr->right)
    {
        ptr_parent = ptr;
        ptr = ptr->right;
    }

    // Swap value of the node rather than the node object
    node->val = ptr->val;

    if (node == ptr_parent)
    {
        ptr_parent->left = ptr->left;
    }
    else
    {
        ptr_parent->right = ptr->left;
    }
    delete ptr;
}

template <typename T>
void BinarySearchTree<T>::remove_node(
    BinarySearchTree<T>::Node* node, BinarySearchTree<T>::Node* parent)
{
    if (node->right)    // Find successor
    {
        swap_successor(node);
    }
    else if (node->left)    // Find predecessor
    {
        swap_predecessor(node);
    }
    else
    {
        if (node->val > parent->val)
        {
            parent->right = nullptr;
        }
        else
        {
            parent->left = nullptr;
        }
        delete node;
    }
}
