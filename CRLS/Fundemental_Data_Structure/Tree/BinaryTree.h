#include "TreeNode.h"
#include <stack>
template <typename T>
class BinaryTree {
protected:
    TreeNode<T>* root;
    void pre_order(TreeNode<T>* r);
    void in_order(TreeNode<T>* r);
    void post_order(TreeNode<T>* r);
    void post_order_destructor(TreeNode<T>* r);
    TreeNode<T>* search_(TreeNode<T>* t, const T& x);
public:
    TreeNode<T>* successor(TreeNode<T>* t);
    BinaryTree(TreeNode<T>* r = nullptr): root(r) {}
    ~BinaryTree();
    void insert(const T& x);
    void preOrder();
    void inOrder();
    void postOrder();
    void traversalUseStack();
    void traversalNonRecursion();
    TreeNode<T>* search(const T& x);
    TreeNode<T>* searchNonRecursion(const T& x);
    TreeNode<T>* minimum();
    TreeNode<T>* maximum();
    TreeNode<T>* predecessor(TreeNode<T>* t);
};

template <typename T>
TreeNode<T>* BinaryTree<T>::predecessor(TreeNode<T>* t) {
    if (t) {
        if (t->getLeftNode()) {
            t = t->getLeftNode();
            while (t->getRightNode()) {
                t = t->getRightNode();
            }
        } else {
            TreeNode<T>* temp = t->getParent();
            while (temp && t == temp->getLeftNode()) {
                t = temp;
                temp = temp->getParent();
            }
            t = temp;
        }
    }
    return t;
}

template <typename T>
TreeNode<T>* BinaryTree<T>::maximum() {
    TreeNode<T>* temp = this->root;
    if (temp) {
        while (temp->getRightNode()) {
            temp = temp->getRightNode();
        }
    }
    return temp;
}

template <typename T>
TreeNode<T>* BinaryTree<T>::minimum() {
    TreeNode<T>* temp = this->root;
    if (temp) {
        while (temp->getLeftNode()) {
            temp = temp->getLeftNode();
        }
    }
    return temp;
}

template <typename T>
TreeNode<T>* BinaryTree<T>::searchNonRecursion(const T& x) {
    TreeNode<T>* temp = this->root;
    while (temp && temp->getKey() == x) {
        if (x < temp->getKey()) {
            x = temp->getLeftNode();
        } else {
            x = temp->getRightNode();
        }
    }
    return temp;
}

template <typename T>
TreeNode<T>* BinaryTree<T>::search(const T& x) {
    return search_(this->root, x);
}

template <typename T>
TreeNode<T>* BinaryTree<T>::search_(TreeNode<T>* t, const T& x) {
    if (!t || t->getKey() == x) {
        return t;
    }
    if (t->getKey() > x) {
        return this->search_(t->getLeftNode(), x);
    } else {
        return this->search_(t->getRightNode(), x);
    }
}


template <typename T>
TreeNode<T>* BinaryTree<T>::successor(TreeNode<T>* t) {
    if (t) {
        if (t->getRightNode()) {
            t = t->getRightNode();
            while (t->getLeftNode()) {
                t = t->getLeftNode();
            }
        } else {
            TreeNode<T>* temp = t->getParent();
            while (temp && t == temp->getRightNode()) {
                t = temp;
                temp = temp->getParent();
            }
            t = temp;
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
    cout << endl;
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
void BinaryTree<T>::insert(const T& x) {
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
