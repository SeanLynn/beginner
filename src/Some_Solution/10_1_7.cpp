#include "10_1_7.h"

int main(int argc, char const *argv[])
{
    QueueImplStack stack;
    for (int i = 0; i < 20; i++) {
        stack.push(i);
    }
    stack.printAll();
    cout << stack.top() << endl;
    stack.pop();
    stack.pop();
    stack.push(100);
    cout << stack.top() << endl;
    stack.printAll();
    return 0;
}