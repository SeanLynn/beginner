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
    bool isRoot(T& x) {return this->root ? this->root->getKey() == x : false;}
    bool isLeftNode(TreeNode<T>* r) {return r ? ( r->getParent() ? ( r->getParent()->getLeftNode() == r) : false) : false;}
    bool isRightNode(TreeNode<T>* r) {return r ? ( r->getParent() ? ( r->getParent()->getRightNode() == r) : false) : false;}
    void transplant(TreeNode<T>* v, TreeNode<T>* u); //v replace u
    TreeNode<T>* minimum(TreeNode<T>* r);
public:
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
    TreeNode<T>* minimum() {return minimum(this->root);}
    TreeNode<T>* maximum();
    TreeNode<T>* successor(TreeNode<T>* t);
    TreeNode<T>* predecessor(TreeNode<T>* t);
    void deleteNode(T& x);
    void deleteNodeUsingTransplant(T& x);
};

template <typename T>
void BinaryTree<T>::deleteNodeUsingTransplant(T& x) {
    TreeNode<T>* key = this->searchNonRecursion(x);
    if (!key) {
        return ;
    }
    if (!key->getLeftNode()) {
        this->transplant(key->getRightNode(), key);
    } else if (!key->getRightNode()) {
        this->transplant(key->getLeftNode(), key);
    } else {
        TreeNode<T>* temp = this->minimum(key->getRightNode());
        if (temp->getParent() != key) {
            this->transplant(temp->getRightNode(), temp);
            temp->setRightNode(key->getRightNode());
            temp->getRightNode()->setParent(temp);
        }
        this->transplant(temp, key);
        temp->setLeftNode(key->getLeftNode());
        temp->getLeftNode()->setParent(temp);
    }
    delete key;
}


template <typename T>
void BinaryTree<T>::transplant(TreeNode<T>* v, TreeNode<T>* u) { //v replace u
    if (!u->getParent()) {
        this->root = v;
    } else if (this->isLeftNode(u)) {
        u->getParent()->setLeftNode(v);
    } else {
        u->getParent()->setRightNode(v);
    }
    if (v) {
        v->setParent(u->getParent());
    }
}

template <typename T>
void BinaryTree<T>::deleteNode(T& x) {
    TreeNode<T>* key = this->searchNonRecursion(x);
    if (!key) {
        return ;
    }
    if (!key->getLeftNode()) {
        if (this->root == key) {
            this->root = key->getRightNode();
        } else {
            this->isLeftNode(key) ? key->getParent()->setLeftNode(key->getRightNode()) : key->getParent()->setRightNode(key->getRightNode());
        }
        key->getRightNode()->setParent(key->getParent());
    } else if (!key->getRightNode()) {
        if (this->root == key) {
            this->root = key->getLeftNode();
        } else {
            this->isLeftNode(key) ? key->getParent()->setLeftNode(key->getLeftNode()) : key->getParent()->setRightNode(key->getLeftNode());
        }
        key->getLeftNode()->setParent(key->getParent());
    } else {
        TreeNode<T>* next = this->successor(key);
        next->setLeftNode(key->getLeftNode());
        next->getLeftNode()->setParent(next);
        if (next != key->getRightNode()) {
            next->getParent()->setLeftNode(next->getRightNode());
            if (next->getRightNode()) {
                next->getRightNode()->setParent(next->getParent());
            }
            next->setRightNode(key->getRightNode());
            next->getRightNode()->setParent(next);
        }
        if (key != this->root) {
            this->isLeftNode(key) ? key->getParent()->setLeftNode(next) : key->getParent()->setRightNode(next);
        } else {
            this->root = next;
        }
        next->setParent(key->getParent());
    }
    delete key;
}


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
TreeNode<T>* BinaryTree<T>::minimum(TreeNode<T>* r) {
    if (r) {
        while (r->getLeftNode()) {
            r = r->getLeftNode();
        }
    }
    return r;
}

template <typename T>
TreeNode<T>* BinaryTree<T>::searchNonRecursion(const T& x) {
    TreeNode<T>* temp = this->root;
    while (temp && temp->getKey() != x) {
        if (x < temp->getKey()) {
            temp = temp->getLeftNode();
        } else {
            temp = temp->getRightNode();
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
    if (!t) {
        return t;
    }
    if (t->getRightNode()) {
        t = this->minimum(t->getRightNode());
    } else {
        TreeNode<T>* temp = t->getParent();
        while (temp && t == temp->getRightNode()) {
            t = temp;
            temp = temp->getParent();
        }
        t = temp;
    }
    return t;
}

template <typename T>
void BinaryTree<T>::traversalNonRecursion() {
    TreeNode<T>* current = this->minimum();
    while (current) {
        cout << current->getKey() << ' ';
        current = this->successor(current);
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
    TreeNode<T>* current = this->root;
    TreeNode<T>* currentP = nullptr;
    while (current) {
        currentP = current;
        if (current->getKey() > x) {
            current = current->getLeftNode();
        } else {
            current = current->getRightNode();
        }
    }
    TreeNode<T>* newNode = new TreeNode<T>(x, currentP);
    if (!currentP) {
        this->root = newNode;
    } else if (currentP->getKey() > x) {
        currentP->setLeftNode(newNode);
    } else {
        currentP->setRightNode(newNode);
    }
}
