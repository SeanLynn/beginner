#include "SentinelCircularDLL.h"

int main(int argc, char const *argv[])
{
    SentinelCircularDLL<int> scdll;
    scdll.insert(1);
    scdll.insert(13);
    scdll.insert(14214);
    scdll.insert(2131);
    scdll.insert(3);
    scdll.printAll();
    scdll.printAllInverse();
    scdll._delete(3);
    scdll.printAll();
    scdll.printAllInverse();
    DLLNode<int>* temp = scdll.search(2131);
    if (temp) {
        cout << temp->getKey() << endl;
    } else {
        cerr << "This Linked List doesn't have 13" << endl;
    }
    SentinelCircularDLL<int> anoScdll;
    anoScdll.insert(99);
    anoScdll.insert(98);
    anoScdll.insert(97);
    anoScdll.insert(96);
    scdll.link(&anoScdll);
    scdll.printAll();
    scdll.printAllInverse();
    return 0;
}