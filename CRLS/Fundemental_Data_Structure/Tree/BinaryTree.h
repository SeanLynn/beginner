#include "TreeNode.h"
#include <stack>
template <typename T>
class BinaryTree {
private:
    TreeNode<T>* root;
    void pre_order(TreeNode<T>* r);
    void in_order(TreeNode<T>* r);
    void post_order(TreeNode<T>* r);
    void post_order_destructor(TreeNode<T>* r);
    TreeNode<T>* successor(TreeNode<T>* t);
public:
    BinaryTree(TreeNode<T>* r = nullptr): root(r) {}
    ~BinaryTree();
    void insert(T x);
    void preOrder();
    void inOrder();
    void postOrder();
    void traversalUseStack();
    void traversalNonRecursion();
};

template <typename T>
TreeNode<T>* BinaryTree<T>::successor(TreeNode<T>* t) {
    if (t) {
        if (t->getRightNode()) {
            t = t->getRightNode();
            while (t->getLeftNode()) {
                t = t->getLeftNode();
            }
        } else if (t == this->root) {
            return nullptr;
        } else if (t->getParent()->getLeftNode() == t) {
            t = t->getParent();
        } else {
            while (t->getParent() && t->getParent()->getRightNode() == t) {
                t = t->getParent();
            }
            if (!t->getParent()) {
                return nullptr;
            }
            t = t->getParent();
        }
    }
    return t;
}

template <typename T>
void BinaryTree<T>::traversalNonRecursion() {
    if (this->root) {
        TreeNode<T>* current = this->root;
        while (current->getLeftNode()) {
            current = current->getLeftNode();
        }
        while (current) {
            cout << current->getKey() << ' ';
            current = this->successor(current);
        }
    }
}

template <typename T>
void BinaryTree<T>::traversalUseStack() {
    if (this->root) {
        stack<TreeNode<T>*> assistStack;
        TreeNode<T>* current = this->root;
        while (current || !assistStack.empty()) {
            while (current) {
                assistStack.push(current);
                current = current->getLeftNode();
            }
            current = assistStack.top();
            assistStack.pop();
            cout << current->getKey() << ' ';
            current = current->getRightNode();
        }
    }
    cout << endl;
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    if (this->root) {
        post_order_destructor(this->root);
    }
}

template <typename T>
void BinaryTree<T>::post_order_destructor(TreeNode<T>* r) {
    if (r) {
        this->post_order_destructor(r->getLeftNode());
        this->post_order_destructor(r->getRightNode());
        delete r;
    }
}

template <typename T>
void BinaryTree<T>::postOrder() {
    if (this->root) {
        post_order(this->root);
    }
    cout << endl;
}

template <typename T>
void BinaryTree<T>::post_order(TreeNode<T>* r) {
    if (r) {
        this->post_order(r->getLeftNode());
        this->post_order(r->getRightNode());
        cout << r->getKey() << ' ';
    }
}

template <typename T>
void BinaryTree<T>::inOrder() {
    if (this->root)
        in_order(this->root);
    cout << endl;
}

template <typename T>
void BinaryTree<T>::in_order(TreeNode<T>* r) {
    if (r) {
        this->in_order(r->getLeftNode());
        cout << r->getKey() << ' ';
        this->in_order(r->getRightNode());
    }
}

template <typename T>
void BinaryTree<T>::preOrder() {
    if (this->root)
        pre_order(this->root);
    cout << endl;
}

template <typename T>
void BinaryTree<T>::pre_order(TreeNode<T>* r) {
    if (r) {
        cout << r->getKey() << ' ';
        this->pre_order(r->getLeftNode());
        this->pre_order(r->getRightNode());
    }
}

template <typename T>
void BinaryTree<T>::insert(T x) {
    if (!this->root) {
        this->root = new TreeNode<T>(x);
        return ;
    }
    TreeNode<T>* current = this->root;
    while (true) {
        if (current->getKey() > x) {
            if (current->getLeftNode()) {
                current = current->getLeftNode();
            } else {
                TreeNode<T>* key = new TreeNode<T>(x, current);
                current->setLeftNode(key);
                break;
            }
        } else {
            if (current->getRightNode()) {
                current = current->getRightNode();
            } else {
                TreeNode<T>* key = new TreeNode<T>(x, current);
                current->setRightNode(key);
                break;
            }
        }
    }
}
