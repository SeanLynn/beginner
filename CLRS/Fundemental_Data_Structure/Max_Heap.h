#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;
class Max_Heap
{
private:
    int length;
    int heap_size;
    vector<int> array;

    //maintain the feature of max heap in recursive way
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
    
    //maintain the feature of max heap in loop way
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
public:
    Max_Heap(int length){
        // array[0] is empty
        array.resize(length+1);
        heap_size = 0;
    }
    ~Max_Heap(){}
    
    // delete i(th) element
    void heap_delete(int i){
        array[i] = array[heap_size];
        --heap_size;
        max_heapify_loop(i);
    }

    //get the maximum element of the heap
    int heap_maximum(){
        // the max element
        return array[1];
    }

    // insert key into heap
    void max_heap_insert(int key){
        add(INT_MIN);
        heap_increase_key(heap_size, key);
    }

    //delete and return the maximum element
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

    // increase i(th) to key(>= array[i])
    void heap_increase_key(int i, int key){
        if(key < array[i]){
            cout << "new key is smaller than current key" << endl;
            return ;
        }
        //judge increase i(th) if above i illegal first
        while(i > 1 && array[parent(i)] < key){
            array[i] = array[parent(i)];
            i = parent(i);
        }
        array[i] = key;
    }

    // sort the heap in non-decreasing order  O(n lg n)
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
    

    //build a max heap
    void build_max_heap(){
        for(int i = heap_size/2; i > 0; --i){
            max_heapify_loop(i); 
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

    
};
