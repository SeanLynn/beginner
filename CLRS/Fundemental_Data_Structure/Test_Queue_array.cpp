#include "Queue_array.h"

int main(int argc, char const *argv[])
{
    ArrayQueue array(2);
    array.enqueue(15);
    array.enqueue(2);
    array.enqueue(3);
    array.printAll();
    array.dequeue();
    array.dequeue();
    array.dequeue();
    array.printAll();
    return 0;
}