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
        // array[0] is empty
        array.resize(length+1);
        heap_size = 1;
    }
    ~Heap(){}
    
    void max_heapify_recursive(int i){
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
            max_heapify_recursive(largest);
        }
    }
    //6.2-5
    void max_heapify_loop(int i){
        while(true){
            int l = left(i);
            int r = right(i);
            int largest;
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
                i = largest;
            }else{
                break;
            }
        }
    }

    //6.2-2 MIN-HEAPIFY(int)
    void min_heapify(int i){
        int l = left(i);
        int r = right(i);
        int least;
        // least = the index of min(array[i], array[l], array[r])
        if(l <= heap_size && array[i] < array[i]){
            least = l;
        }else{
            least = i;
        }
        if(r <= heap_size && array[r] < array[least]){
            least = r;
        }

        if(least != i){
            int temp = array[i];
            array[i] = array[least];
            array[least] = temp;
            min_heapify(least);
        }
    }

    //6.3
    void build_max_heap(){
        for(int i = heap_size/2; i > 0; --i){
            max_heapify_loop(i);

        }
    }

    //for initialize the vector
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
    // h.add(16);
    // h.add(4);
    // h.add(10);
    // h.add(14);
    // h.add(7);
    // h.add(9);
    // h.add(3);
    // h.add(2);
    // h.add(8);
    // h.add(1);
    h.add(4);
    h.add(1);
    h.add(3);
    h.add(2);
    h.add(16);
    h.add(9);
    h.add(10);
    h.add(14);
    h.add(8);
    h.add(7);
    h.print();
    h.build_max_heap();
    h.print();
    // h.max_heapify_loop(2);
    // h.print();
    // h.min_heapify(1);
    // h.print();
    return 0;
}
