#pragma once
#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;
class QueueImplStack {
private:
    queue<int> queueA;
    queue<int> queueB;
public:
    void push(int x);
    int pop();
    size_t size();
    bool empty();
    int top();
    void printAll();
};

void QueueImplStack::push(int x) {
    if (queueA.empty()) {
        queueA.push(x);
        while (!queueB.empty()) {
            queueA.push(queueB.front());
            queueB.pop();
        }
    } else {
        queueB.push(x);
        while (!queueA.empty()) {
            queueB.push(queueA.front());
            queueA.pop();
        }
    }
}

int QueueImplStack::pop() {
    int x = INT_MIN;
    if (!this->empty()) {
        if (!queueA.empty()) {
            x = queueA.front();
            queueA.pop();
        } else {
            x = queueB.front();
            queueB.pop();
        }
    } else {
        cerr << "the stack is empty" << endl;
    }
    return x;
}

size_t QueueImplStack::size() {
    return queueA.size() + queueB.size();
}

bool QueueImplStack::empty() {
    return this->size() == 0;
}

int QueueImplStack::top() {
    int x = INT_MIN;
    if (!this->empty()) {
        if (!queueA.empty()) {
            x = queueA.front();
        } else {
            x = queueB.front();
        }
    } else {
        cerr << "the stack is empty()" << endl;
    }
    return x;
}

void QueueImplStack::printAll() {
    if (!this->empty()) {
        if (!queueA.empty()) {
            while (!queueA.empty()) {
                cout << queueA.front() << ' ';
                queueB.push(queueA.front());
                queueA.pop();
            }
        } else {
            while (!queueB.empty()) {
                cout << queueB.front() << ' ';
                queueA.push(queueB.front());
                queueB.pop();
            }
        }
        cout << endl;
    } else {
        cerr << "the stack is empty" << endl;
    }
}
