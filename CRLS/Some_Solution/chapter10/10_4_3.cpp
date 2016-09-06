#include "../../Fundemental_Data_Structure/Tree/BinaryTree.h"

int main(int argc, char const *argv[])
{
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(213);
    tree.insert(21);
    tree.insert(1);
    tree.insert(2);
    tree.insert(121);
    tree.insert(9);
    tree.traversalUseStack();
    return 0;
}