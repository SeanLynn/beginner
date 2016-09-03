#include <iostream>
#include <vector>
#include <climits>
#define SIZE 100
using namespace std;

class D_Ary_Heaps
{
private:
    int d;
    vector<int> A; // count from 1
    int length;
    int heap_size;

    int parent(int i){
        return (i+1)/d;
    }

    int child(int i, int c){
        return (i-1)*d+c+1;
    }

    void max_heapify_loop(int i){
        int largest = i;
        while(true){
            int base_child = child(i, 1);
            for(int k = 0; k < d; ++k){
                int current_child = base_child+k;
                if(current_child <= heap_size && A[current_child] > A[largest]){
                    largest = current_child;
                }
            }
            if(largest != i){
                swap(A[largest], A[i]);
                i = largest;
            }else{
                break;
            }
        }
    }

    void build_max_heap(){
        for(int i = (heap_size+1)/d; i > 0; --i){
            max_heapify_loop(i);
        }
    }
public:
    D_Ary_Heaps(int _d, vector<int> arr, int _length)
        :d(_d), A(arr), length(_length), heap_size(arr.size()-1){
            build_max_heap();
        }
    ~D_Ary_Heaps(){}
    int extract_max(){
        int max = A[1];
        A[1] = A[heap_size];
        cout << "heap_size:" << heap_size << endl;
        --heap_size;
        max_heapify_loop(1);
        return max;
    }

    void increase_key(int i, int key){
        if(A[i] > key){
            cout << "new key is smaller than current key" << endl;
            return ;
        }

        while(i > 1 && A[parent(i)] < key){
            A[i] = A[parent(i)];
            i = parent(i);
        }
        A[i] = key;
    }

    void insert(int key){
        add(INT_MIN);
        increase_key(heap_size, key);
    }

    void add(int key){
        if(heap_size >= length){
            A.resize(2*length);
            length <<= 1;
        }
        ++heap_size;
        A[heap_size] = key;
    }

    void print(){
        for(int i = 1; i <= heap_size; ++i){
            cout << A[i] << ' ';
        }
    }
};

int main(int argc, char const *argv[])
{
    vector<int> vc;
    vc.push_back(INT_MIN);
    for(int i = 1; i <= 20; ++i){
        vc.push_back(i);
    }
    D_Ary_Heaps dh(3, vc, 30);
    dh.print();
    cout << dh.extract_max() << endl;
    return 0;
}