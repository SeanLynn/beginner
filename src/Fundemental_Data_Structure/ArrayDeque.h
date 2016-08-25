#include <iostream>
#include <memory>
using namespace std;

class ArrayDeque
{
public:
    ArrayDeque(int capacity = 20);
    ~ArrayDeque() {}
    bool empty();
    bool full();
    void addHead(int element);
    void addTail(int element);
    int removeHead();
    int removeTail();
    void printAll();
private:
    unique_ptr<int[]> array;
    int head;
    int tail;
    int size;
    int capacity;
};

ArrayDeque::ArrayDeque(int capacity) : array(new int[capacity]) {
    this->capacity = capacity;
    this->head = this->tail = this->size = 0;
}

bool ArrayDeque::empty() {
    return size == 0;
}

bool ArrayDeque::full() {
    return size == capacity;
}

void ArrayDeque::addHead(int element) {
    if (full()) {
        cerr << "The array is full and has " << size << " elements." << endl;
    } else {
        head = head == 0 ? capacity - 1 : head - 1;
        array[head] = element;
        size++;
    }
}

void ArrayDeque::addTail(int element) {
    if (full()) {
        cerr << "The array is full and has " << size << " elements." << endl;
    } else {
        array[tail] = element;
        tail = tail == capacity - 1 ? 0 : tail + 1;
        size++;
    }
}

int ArrayDeque::removeHead() {
    if (empty()) {
        cerr << "The array queue is empty." << endl;
        return INT_MIN;
    } else {
        int x = array[head];
        head = head == capacity - 1 ? 0 : head + 1;
        size--;
        return x;
    }
}

int ArrayDeque::removeTail() {
    if (empty()) {
        cerr << "The array queue is empty." << endl;
        return INT_MIN;
    }
}