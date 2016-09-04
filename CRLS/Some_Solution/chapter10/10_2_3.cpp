#include "../../Fundemental_Data_Structure/LinkedList/LinkedList.h"

int main(int argc, char const *argv[])
{
    LinkedList<int> queue;
    queue.enqueue(0);
    queue.enqueue(2131);
    queue.enqueue(2);
    queue.enqueue(42154);
    queue.enqueue(9);
    queue.printAll();
    queue.dequeue();
    queue.dequeue();
    queue.printAll();
    return 0;
}