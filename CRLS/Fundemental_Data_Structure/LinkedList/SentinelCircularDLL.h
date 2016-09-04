#pragma once
#include <iostream>
#include "DoubleLinkedList.h"
using namespace std;

template <typename T>
class SentinelCircularDLL {
private:
    DLLNode<T>* nil;
public:
    SentinelCircularDLL();
    void insert(T x);
    void _delete(T x);
    DLLNode<T>* search(T x);
    void printAll();
    void printAllInverse();
};

template <typename T>
SentinelCircularDLL<T>::SentinelCircularDLL() {
    this->nil = new DLLNode<T>();
    this->nil->setPrecNode(this->nil);
    this->nil->setNextNode(this->nil);
}

template <typename T>
void SentinelCircularDLL<T>::insert(T x) {
    DLLNode<T>* key = new DLLNode<T>(x, this->nil->getNextNode(), this->nil);
    this->nil->setNextNode(key);
    key->getNextNode()->setPrecNode(key);
}

template <typename T>
void SentinelCircularDLL<T>::printAll() {
    DLLNode<T>* key = this->nil->getNextNode();
    while (key != this->nil) {
        cout << key->getKey() << ' ';
        key = key->getNextNode();
    }
    cout << endl;
}

template <typename T>
void SentinelCircularDLL<T>::_delete(T x) {
    DLLNode<T>* key = this->search(x);
    if (!key) {
        cerr << "This Linked List doesn't have " << x << endl;
        return ;
    }
    key->getPrecNode()->setNextNode(key->getNextNode());
    key->getNextNode()->setPrecNode(key->getPrecNode());
    delete key;
}

template <typename T>
DLLNode<T>* SentinelCircularDLL<T>::search(T x) {
    DLLNode<T>* key = this->nil->getNextNode();
    while (key != this->nil) {
        if (key->getKey() == x)
            break;
        key = key->getNextNode();
    }
    if (key == this->nil)
        key = nullptr;
    return key;
}

template <typename T>
void SentinelCircularDLL<T>::printAllInverse() {
    DLLNode<T>* key = this->nil->getPrecNode();
    while (key != this->nil) {
        cout << key->getKey() << ' ';
        key = key->getPrecNode();
    }
    cout << endl;
}
