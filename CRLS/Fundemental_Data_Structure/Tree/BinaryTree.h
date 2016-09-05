#include "TreeNode.h"

template <typename T>
class BinaryTree {
private:
    TreeNode<T>* root;
public:
    BinaryTree(TreeNode<T>* r = nullptr): root(r) {}
    void insert(T x);
};