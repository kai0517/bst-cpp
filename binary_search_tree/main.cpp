#include <iostream>
#include "bst.h"

int main(void)
{
    BinarySearchTree<int> tree = { 30, 20, 10, 80, 40, 60, 120, 50, 100, 140, 70, 130, 150 };
    std::cout << tree;
    std::cout << "Remove node 30..." << std::endl;
    tree.remove(30);
    std::cout << tree;
    std::cout << "Insert node 18, 15, 27, 32..." << std::endl;
    tree.insert(18);
    tree.insert(15);
    tree.insert(27);
    tree.insert(32);
    std::cout << tree;

    return 0;
}
