#pragma once
#include <iostream>
#include <memory>
#include <limits.h>
using namespace std;

class ArrayQueue
{
public:
    ArrayQueue(int size = 15);
    bool empty();
    bool full();
    void enqueue(int element);
    int dequeue();
    void printAll();
    ~ArrayQueue() {}
private:
    unique_ptr<int> array;
    int head;
    int tail;
    int capacity;
    int size;
};

ArrayQueue::ArrayQueue(int size) : array(new int[size]) {
    this->capacity = size;
    this->head = this->tail = this->size = 0;
}

bool ArrayQueue::empty() {
    return size == 0;
}

bool ArrayQueue::full() {
    return size == capacity;
}

void ArrayQueue::enqueue(int element) {
    if (full()) {
        cerr << "The array queue is full and has " << size << " elements." << endl;
    } else {
        array.get()[tail++] = element;
        if (tail == capacity)
            tail = 0;
        size++;
    }
}

int ArrayQueue::dequeue() {
    if (empty()) {
        cerr << "The array queue is empty." << endl;
        return INT_MIN;
    } else {
        int x = array.get()[head++];
        if (head == capacity)
            head = 0;
        size--;
        return x;
    }
}

void ArrayQueue::printAll() {
    for (int i = 0; i < size; i++) {
        cout << array.get()[(head + i) % capacity] << ' ';
    }
    cout << endl;
}