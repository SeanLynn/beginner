#include "10_1_6.h"

int main(int argc, char const *argv[])
{
    StackImplQueue queue;
    for (int i = 0; i < 20; i++) {
        queue.push(i);
    }
    queue.printAll();
    cout << queue.top() << endl;
    queue.pop();
    queue.pop();
    queue.push(100);
    cout << queue.top() << endl;
    queue.printAll();
    return 0;
}