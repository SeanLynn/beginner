#include "DoubleLinkedList.h"

int main(int argc, char const *argv[])
{
    DoubleLinkedList<int> dll;
    for (int i = 0; i < 20; i++) {
        dll.insert(i);
    }
    dll.printAll();
    dll._delete(19);
    dll._delete(18);
    dll._delete(0);
    dll.printAll();
    dll._delete(22);
    DLLNode<int>* temp = dll.search(22);
    if (temp)
        cout << temp->getKey() << endl;
    else
        cout << "The Linked List doesn't have 22." << endl;
    return 0;
}