#include "../../Fundemental_Data_Structure/LinkedList/LinkedList.h"

int main(int argc, char const *argv[])
{
    LinkedList<int> stack;
    stack.push(0);
    stack.push(12);
    stack.push(4124);
    stack.push(4);
    stack.printAll();
    stack.pop();
    stack.printAll();
    stack.pop();
    stack.printAll();
    return 0;
}