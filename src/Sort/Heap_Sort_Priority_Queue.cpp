#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
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
        heap_size = 0;
    }
    ~Heap(){}
    
    int heap_maximum(){
        // the max element
        return array[1];
    }

    void max_heap_insert(int key){
        if(add(INT_MIN)){
            heap_increase_key(heap_size, key);
        }
    }

    int heap_extract_max(){
        // remove the max element, return it, and adjust the structure
        if(heap_size < 1){
            cout << "heap underflow" << endl;
            return 0;
        }
        int max = array[1];
        array[1] = array[heap_size];
        --heap_size;
        max_heapify_loop(1);
        return max;
    }

    void heap_increase_key(int i, int key){
        if(key < array[i]){
            cout << "new key is smaller than current key" << endl;
            return ;
        }
        array[i] = key;
        while(i > 1 && array[parent(i)] < array[i]){
            swap(array[parent(i)], array[i]);
            i = parent(i);
        }
    }

    void heap_sort(){
        build_max_heap();
        int size = heap_size;
        for(int i = heap_size; i > 1; --i){
            swap(array[i], array[1]);
            --heap_size;
            max_heapify_loop(1);
        }
        heap_size = size;
    }

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
    bool add(int data){
        if(heap_size<length){
            ++heap_size;
            array[heap_size] = data;
            return true;
        }else{
            //the exception can be handled by resize the length of the heap
            cout << "heap is full!" << endl;
            return false;
        }
    }

    void print(){
        for(int i = 1; i <= heap_size; ++i){
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
    //1,
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
    
    //2,
    // h.add(4);
    // h.add(1);
    // h.add(3);
    // h.add(2);
    // h.add(16);
    // h.add(9);
    // h.add(10);
    // h.add(14);
    // h.add(8);
    // h.add(7);

    //3,
    h.add(5);
    h.add(13);
    h.add(2);
    h.add(25);
    h.add(7);
    h.add(17);
    h.add(20);
    h.add(8);
    h.add(4);
    h.print();
    h.build_max_heap();
    h.print();
    h.heap_extract_max();
    h.print();
    h.max_heap_insert(26);
    h.print();
    h.heap_sort();
    h.print();
    return 0;
}
