#include <iostream>

template <typename T>
class TreeNode {
private:
    T key;
    TreeNode<T>* parent;
    TreeNode<T>* left;
    TreeNode<T>* right;
public:
    TreeNode(): parent(nullptr), left(nullptr), right(nullptr) {}
    TreeNode(T k, TreeNode<T>* p, TreeNode<T>* l, TreeNode<T>* r)
        : key(k), parent(p), left(l), right(r) {}
    void setKey(T k) {key = k;}
    void setParent(TreeNode<T>* p) {parent = p;}
    void setLeftNode(TreeNode<T>* l) {left = l;}
    void setRightNode(TreeNode<T>* r) {right = r;}
    T getKey() {return key;}
    TreeNode<T>* getParent() {return parent;}
    TreeNode<T>* getLeftNode() {return left;}
    TreeNode<T>* getRightNode() {return right;}
};