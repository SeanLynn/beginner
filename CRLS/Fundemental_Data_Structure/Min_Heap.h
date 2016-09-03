#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;
class Min_Heap
{
private:
    int length;
    int heap_size;
    vector<int> array;
public:
    Min_Heap(int length){
        // array[0] is empty
        array.resize(length+1);
        heap_size = 0;
    }
    ~Min_Heap(){}
    
    // delete i(th) element
    void heap_delete(int i){
        array[i] = array[heap_size];
        --heap_size;
        min_heapify_loop(i);
    }

    //get the minimum element of the heap
    int heap_minimum(){
        // the min element
        return array[1];
    }

    // insert key into heap
    void min_heap_insert(int key){
        add(INT_MAX);
        heap_decrease_key(heap_size, key);
    }

    //delete and return the minimum element
    int heap_extract_min(){
        // remove the min element, return it, and adjust the structure
        if(heap_size < 1){
            cout << "heap underflow" << endl;
            return 0;
        }
        int min = array[1];
        array[1] = array[heap_size];
        --heap_size;
        min_heapify_loop(1);
        return min;
    }

    // decrease i(th) to key(<= array[i])
    void heap_decrease_key(int i, int key){
        if(key > array[i]){
            cout << "new key is larger than current key" << endl;
            return ;
        }
        //judge decrease i(th) if above i illegal first
        while(i > 1 && array[parent(i)] > key){
            array[i] = array[parent(i)];
            i = parent(i);
        }
        array[i] = key;
    }

    // sort the heap in non-increasing order  O(n lg n)
    void heap_sort(){
        build_min_heap();
        int size = heap_size;
        for(int i = heap_size; i > 1; --i){
            swap(array[i], array[1]);
            --heap_size;
            min_heapify_loop(1);
        }
        heap_size = size;
    }
    //maintain the feature of max heap in recursive way
    void min_heapify_recursive(int i){
        int l = left(i);
        int r = right(i);
        int largest;
        // largest = the index of max(array[i], array[l], array[r])
        if(l <= heap_size && array[l] < array[i]){
            largest = l;
        }else{
            largest = i;
        }
        if(r <= heap_size && array[r] < array[largest]){
            largest = r;
        }

        if(largest != i){
            int temp = array[i];
            array[i] = array[largest];
            array[largest] = temp;
            min_heapify_recursive(largest);
        }
    }
    
    //maintain the feature of max heap in loop way
    void min_heapify_loop(int i){
        while(true){
            int l = left(i);
            int r = right(i);
            int least;
            if(l <= heap_size && array[l] < array[i]){
                least = l;
            }else{
                least = i;
            }
            if(r <= heap_size && array[r] < array[least]){
                least = r;
            }

            if(least != i){
                swap(array[i], array[least]);
                i = least;
            }else{
                break;
            }
        }
    }

    //build a max heap
    void build_min_heap(){
        for(int i = heap_size/2; i > 0; --i){
            min_heapify_loop(i); 
        }
    }

    //add data on the tail of the heap;
    void add(int data){
        if(heap_size>=length){
            array.resize(2*length);
            length <<= 1;
        }
        ++heap_size;
        array[heap_size] = data;
    }

    // print all element in one line
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