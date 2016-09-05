#pragma once
//double linked list with no sentinel and circulation.
#include <iostream>
using namespace std;
template <typename T>
class DLLNode {
private:
    T key;
    DLLNode<T>* prec;
    DLLNode<T>* next;
public:
    DLLNode(): prec(nullptr), next(nullptr) {}
    DLLNode(T k, DLLNode<T>* right = nullptr, DLLNode<T>* left = nullptr);
    void setPrecNode(DLLNode<T>* p) {prec = p;}
    void setNextNode(DLLNode<T>* n) {next = n;}
    DLLNode<T>* getPrecNode() {return prec;}
    DLLNode<T>* getNextNode() {return next;}
    void setKey(T k) {key = k;}
    T getKey() {return key;}
};

template <typename T>
DLLNode<T>::DLLNode(T k, DLLNode<T>* right, DLLNode<T>* left) : key(k)
{
    this->setNextNode(right);
    this->setPrecNode(left);
}

template <typename T>
class DoubleLinkedList {
private:
    DLLNode<T>* head;
public:
    DoubleLinkedList(DLLNode<T>* h = nullptr): head(h) {}
    ~DoubleLinkedList();
    void insert(T x);
    void printAll();
    void _delete(T x);
    DLLNode<T>* search(T x);
};

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    if (!this->head) {
        return ;
    }
    DLLNode<T>* key = this->head->getNextNode();
    while (key) {
        DLLNode<T>* temp = key->getNextNode();
        delete key;
        temp = key;
    }
}

template <typename T>
DLLNode<T>* DoubleLinkedList<T>::search(T x) {
    DLLNode<T>* key = this->head;
    while (key && key->getKey() != x) {
        key = key->getNextNode();
    }
    return key;
}

template <typename T>
void DoubleLinkedList<T>::_delete(T x) {
    DLLNode<T>* key = this->head;
    while (key && key->getKey() != x) {
        key = key->getNextNode();
    }
    if (key) {
        if (key->getPrecNode())
            key->getPrecNode()->setNextNode(key->getNextNode());
        else
            this->head = key->getNextNode();
        if (key->getNextNode())
            key->getNextNode()->setPrecNode(key->getPrecNode());
        delete key;
    } else {
        cerr << "delete " << x << " failure. The Linked List doesn't have it." << endl;
    }
}

template <typename T>
void DoubleLinkedList<T>::printAll() {
    DLLNode<T>* key = this->head;
    while (key) {
        cout << key->getKey() << ' ';
        key = key->getNextNode();
    }
    cout << endl;
}

template <typename T>
void DoubleLinkedList<T>::insert(T x) {
    DLLNode<T> *key = new DLLNode<T>(x, this->head, nullptr);
    if (this->head) {
        this->head->setPrecNode(key);
    }
    this->head = key;
}