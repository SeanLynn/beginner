#include "ArrayDeque.h"

int main(int argc, char const *argv[])
{
    ArrayDeque deque({1, 2, 3, 4, 5, 6});
    deque.addTail(7);
    deque.addHead(0);
    deque.printAll();
    deque.removeTail();
    deque.removeHead();
    deque.printAll();
    return 0;
}