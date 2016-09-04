#pragma once
#include <iostream>
using namespace std;
//this file is to for 10.2-2 and 10.2-3
template <typename T>
class LLNode {
private:
    T key;
    LLNode<T>* next;
public:
    LLNode(): next(nullptr) {}
    LLNode(T k, LLNode<T>* n = nullptr): key(k), next(n) {}
    void setNextNode(LLNode<T>* n) {next = n;}
    LLNode<T>* getNextNode() {return next;}
    void setKey(T k) {key = k;}
    T getKey() {return key;}
};

template <typename T>
class LinkedList {
private:
    LLNode<T>* head;
    LLNode<T>* tail; //use for queue
public:
    LinkedList(LLNode<T>* h = nullptr, LLNode<T>* t = nullptr) : head(h), tail(head) {}
    void insert(T x);
    void enqueue(T x);
    void dequeue();
    void push(T x) {this->insert(x);}
    void pop();
    void printAll();
    void _delete(T x);
    LLNode<T>* search(T x);
};

template <typename T>
void LinkedList<T>::dequeue() {
    if (this->head) {
        LLNode<T>* temp = this->head;
        if (this->tail == temp) {
            this->head = this->tail = nullptr;
            return ;
        }
        this->head = temp->getNextNode();
    } else {
        cerr << "This queue is empty." << endl;
    }
}

//write for queue
template <typename T>
void LinkedList<T>::enqueue(T x) {
    if (this->tail) {
        this->tail->setNextNode(new LLNode<T>(x, nullptr));
        this->tail = this->tail->getNextNode();
        return ;
    }
    this->head = this->tail = new LLNode<T>(x, nullptr);
}

//write for stack
template <typename T>
void LinkedList<T>::pop() {
    if (!this->head) {
        return ;
    }
    LLNode<T>* key = this->head;
    this->head = key->getNextNode();
    delete key;
}

template <typename T>
LLNode<T>* LinkedList<T>::search(T x) {
    if (!this->head) {
        return nullptr;
    }
    LLNode<T>* key = this->head;
    while (key && key->getKey() != x) {
        key = key->getNextNode();
    }
    return key;
}

template <typename T>
void LinkedList<T>::_delete(T x) {
    if (!this->head) {
        return ;
    }
    LLNode<T>* key = this->head;
    if (key->getKey() == x) {
        this->head = this->head->getNextNode();
        delete key;
        return ;
    }
    LLNode<T>* temp;
    while (temp = key->getNextNode()) {
        if (temp->getKey() == x) {
            key->setNextNode(temp->getNextNode());
            delete temp;
            break;
        }
        key = temp;
    }
}

template <typename T>
void LinkedList<T>::insert(T x) {
    this->head = new LLNode<T>(x, this->head);
}

template <typename T>
void LinkedList<T>::printAll() {
    LLNode<T>* key = this->head;
    while (key) {
        cout << key->getKey() << ' ';
        key = key->getNextNode();
    }
    cout << endl;
}