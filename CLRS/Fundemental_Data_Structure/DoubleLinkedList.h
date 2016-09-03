#pragma once
//double linked list with no sentinel and circulation.
#include <iostream>
using namespace std;
template <typename T>
class Node {
private:
    T key;
    Node<T>* prec;
    Node<T>* next;
public:
    Node(): prec(nullptr), next(nullptr) {}
    Node(T k, Node<T>* right = nullptr, Node<T>* left = nullptr);
    void setPrecNode(Node<T>* prec) {this->prec = prec;}
    void setNextNode(Node<T>* next) {this->next = next;}
    Node<T>* getPrecNode() {return prec;}
    Node<T>* getNextNode() {return next;}
    void setKey(T key) {this->key = key;}
    T getKey() {return key;}

};

template <typename T>
Node<T>::Node(T k, Node<T>* right, Node<T>* left) : key(k)
{
    this->setNextNode(right);
    this->setPrecNode(left);
}

template <typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
public:
    void insert(T x);
    DoubleLinkedList(Node<T>* h = nullptr): head(h) {}
    void printAll();
    void _delete(T x);
    Node<T>* search(T x);
};

template <typename T>
Node<T>* DoubleLinkedList<T>::search(T x) {
    Node<T>* key = this->head;
    while (key && key->getKey() != x) {
        key = key->getNextNode();
    }
    return key;
}

template <typename T>
void DoubleLinkedList<T>::_delete(T x) {
    Node<T>* key = this->head;
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
    Node<T>* key = this->head;
    while (key) {
        cout << key->getKey() << ' ';
        key = key->getNextNode();
    }
    cout << endl;
}

template <typename T>
void DoubleLinkedList<T>::insert(T x) {
    Node<T> *key = new Node<T>(x, this->head, nullptr);
    if (this->head) {
        this->head->setPrecNode(key);
    }
    this->head = key;
}