#include <iostream>
#include "Max_Heap.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Max_Heap max_heap(10);
    max_heap.add(5);
    max_heap.add(13);
    max_heap.add(2);
    max_heap.add(25);
    max_heap.add(7);
    max_heap.add(17);
    max_heap.add(20);
    max_heap.add(8);
    max_heap.add(4);
    max_heap.print();
    max_heap.build_max_heap();
    max_heap.print();
    max_heap.heap_extract_max();
    max_heap.print();
    max_heap.max_heap_insert(26);
    max_heap.print();
    max_heap.heap_sort();
    max_heap.print();
    return 0;
}