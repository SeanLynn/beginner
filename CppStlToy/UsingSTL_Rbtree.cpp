#include <iostream>
#include <bits/stl_tree.h>
using namespace std;

int main(int argc, char const *argv[])
{
    _Rb_tree<int, int, _Identity<int>, less<int>> itree;
    cout << itree.size() << endl;
    itree._M_insert_unique(10);
    itree._M_insert_unique(7);
    itree._M_insert_unique(8);
    itree._M_insert_unique(15);
    itree._M_insert_unique(5);
    itree._M_insert_unique(6);
    itree._M_insert_unique(11);
    itree._M_insert_unique(13);
    itree._M_insert_unique(12);
    cout << itree.size() << endl;

    auto ite1 = itree.begin();
    auto ite2 = itree.end();
    for(; ite1 != ite2; ++ite1)
        cout << *ite1 << ' '; // 5 6 7 8 10 11 12 13 15
    cout << endl;
    
    ite1 = itree.begin();
    for(; ite1 != ite2; ++ite1){
        auto rbite = _Rb_tree_iterator<int>(ite1);
        cout << *ite1 << '(' << rbite._M_node->_M_color << ") "; 
    } // 5(0) 6(1) 7(0) 8(1) 10(1) 11(0) 12(0) 13(1) 15(0)
    return 0;
}
