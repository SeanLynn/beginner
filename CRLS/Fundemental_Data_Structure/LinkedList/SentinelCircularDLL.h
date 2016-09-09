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
    ~SentinelCircularDLL();
    void insert(T x);
    void _delete(T x);
    DLLNode<T>* search(T x);
    void link(SentinelCircularDLL<T>* anDLL);
    void printAll();
    void printAllInverse();
    DLLNode<T>* getNil() {return this->nil;}
};

template <typename T>
void SentinelCircularDLL<T>::link(SentinelCircularDLL<T> *anDLL) {
    DLLNode<T>* anNil = anDLL->getNil();
    this->nil->getPrecNode()->setNextNode(anNil->getNextNode());
    anNil->getNextNode()->setPrecNode(this->nil->getPrecNode());
    this->nil->setPrecNode(anNil->getPrecNode());
    anNil->getPrecNode()->setNextNode(this->nil);
    anNil->setNextNode(anNil);
    anNil->setPrecNode(anNil);
}

template <typename T>
SentinelCircularDLL<T>::~SentinelCircularDLL() {
    DLLNode<T>* key = this->nil->getNextNode();
    while (key != this->nil) {
        DLLNode<T>* temp = key->getNextNode();
        delete key;
        key = temp;
    }
    delete key;
}

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

//the solution to CLRS 10.2-4
template <typename T>
DLLNode<T>* SentinelCircularDLL<T>::search(T x) {
    this->nil->setKey(x);
    DLLNode<T>* key = this->nil->getNextNode();
    while (key->getKey() != x) {
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
