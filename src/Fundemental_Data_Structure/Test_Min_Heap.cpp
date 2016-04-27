#include <iostream>
#include "Min_Heap.h"
using namespace std;
int main(int argc, char const *argv[])
{
    Min_Heap min_heap(10);
    min_heap.add(5);
    min_heap.add(13);
    min_heap.add(2);
    min_heap.add(25);
    min_heap.add(7);
    min_heap.add(17);
    min_heap.add(20);
    min_heap.add(8);
    min_heap.add(4);
    min_heap.print();
    min_heap.build_min_heap();
    min_heap.print();
    min_heap.heap_extract_min();
    min_heap.print();
    min_heap.min_heap_insert(10);
    min_heap.print();
    min_heap.heap_sort();
    min_heap.print();
    return 0;
}