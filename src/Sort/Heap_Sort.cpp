#include <iostream>
#include <vector>
using namespace std;

class Heap
{
private:
    int length;
    int heap_size;
    vector<int> array;
public:
    Heap(int length){
        array.resize(length+1);
        heap_size = 1;
    }
    ~Heap(){}
    
    void max_heapify(int i){
        int l = left(i);
        int r = right(i);
        int largest;
        // largest = the index of max(array[i], array[l], array[r])
        if(l <= heap_size && array[l] > array[i]){
            largest = l;
        }else{
            largest = i;
        }
        if(r <= heap_size && array[r] > array[largest]){
            largest = r;
        }

        if(largest != i){
            int temp = array[i];
            array[i] = array[largest];
            array[largest] = temp;
            max_heapify(largest);
        }
    }

    void add(int data){
        if(heap_size<length){
            array[heap_size] = data;
            ++heap_size;
        }else{
            cout << "heap is full!" << endl;
        }
    }

    void print(){
        for(int i = 1; i < heap_size; ++i){
            cout << array[i] << ' ';
        }
        cout << endl;
    }

    int parent(int i){
        return i>>1;
    }
    int left(int i){
        return i<<1;
    }
    int right(int i){
        // << priority less than +  ????
        return (i<<1) + 1;
    }
};







int main(int argc, char const *argv[])
{
    Heap h(10);
    h.add(16);
    h.add(4);
    h.add(10);
    h.add(14);
    h.add(7);
    h.add(9);
    h.add(3);
    h.add(2);
    h.add(8);
    h.add(1);
    h.print();
    h.max_heapify(2);
    h.print();
    return 0;
}