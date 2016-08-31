#pragma once
#include <iostream>
#include <stack>
#include <limits.h>
using namespace std;
//Show how to implement a queue using two stacks. Analyze the running time of the queue operations.
class StackImplQueue {
private:
    stack<int> stackA;
    stack<int> stackB;
    int stackA2B();
public:
    void push(int x);
    int pop();
    size_t size();
    bool empty();
    int top();
    void printAll();
};

void StackImplQueue::push(int x) {
    stackA.push(x);
}

int StackImplQueue::pop() {
    int x = INT_MIN;
    if (!this->empty()) {
        if (stackB.empty()) {
            stackA2B();
        }
        x = stackB.top();
        stackB.pop();
    } else {
        cerr << "the queue is empty" << endl;
    }
    return x;
}

size_t StackImplQueue::size() {
    return stackA.size() + stackB.size();
}

bool StackImplQueue::empty() {
    return this->size() == 0;
}

int StackImplQueue::top() {
    if (this->empty()) {
        cerr << "the queue is empty" << endl;
        return INT_MIN;
    }
    if (stackB.empty()) {
        this->stackA2B();
    }
    return stackB.top();
}

int StackImplQueue::stackA2B() {
    int size = stackA.size();
    for (int i = 0; i < size; i++) {
        stackB.push(stackA.top());
        stackA.pop();
    }
}

void StackImplQueue::printAll() {
    if (!this->empty()) {
        StackImplQueue temp;
        while (this->size()) {
            cout << this->top() << ' ';
            temp.push(this->pop());
        }
        cout << endl;
        while (temp.size()) {
            this->push(temp.pop());
        }
    } else {
        cerr << "the queue is empty()" << endl;
    }
}