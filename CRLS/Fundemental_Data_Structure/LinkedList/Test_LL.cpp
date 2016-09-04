#include "LinkedList.h"

int main(int argc, char const *argv[])
{
    LinkedList<int> ll;
    for (int i = 0; i < 20; i++) {
        ll.insert(i);
    }
    ll.printAll();
    ll._delete(19);
    ll._delete(0);
    ll._delete(12);
    ll.printAll();
    LLNode<int>* temp = ll.search(12);
    if (temp) {
        cout << temp->getKey() << endl;
    } else {
        cerr << "This linked list doesn't have 12" << endl;
    }
    return 0;
}