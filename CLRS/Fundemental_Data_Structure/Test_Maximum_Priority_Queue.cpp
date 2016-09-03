#include <iostream>
#include "Maximum_priority_queue.h"
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> vc(10);
    vc.push_back(5);
    vc.push_back(13);
    vc.push_back(2);
    vc.push_back(25);
    vc.push_back(7);
    vc.push_back(17);
    vc.push_back(20);
    vc.push_back(8);
    vc.push_back(4);
    Maximum_priority_queue mpq(vc);
    cout << mpq.maximum() << endl;
    cout << mpq.extract_max() << endl;
    mpq.increase_key(5,30);
    cout << mpq.maximum() << endl;
    return 0;
}