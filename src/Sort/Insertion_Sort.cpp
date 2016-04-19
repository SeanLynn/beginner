#include <iostream>

using namespace std;

template <typename T>
void insertion_sort_increase(T* a, int begin, int end){
    // a is the reference to the array
    // sort [begin, end) in a non-decrease sequence
    if(begin == end){
        return;
    }
    for(int j = begin+1; j < end; j++){
        T key = a[j];
        // Insert a[j] into the sorted sequence a[begin..j-1]
        int i = j - 1;
        while(i>=begin && a[i]>key){
            a[i+1] = a[i];
            --i;
        }
        a[i+1] = key;
    }
}
template <typename T>
void insertion_sort_decrease(T* a, int begin, int end){
    // a is the reference to the array
    // sort [begin, end) in a non-increase sequence
    if(begin == end){
        return;
    }
    for(int j = begin+1; j < end; j++){
        T key = a[j];
        // Insert a[j] into the sorted sequence a[begin..j-1]
        int i = j - 1;
        while(i>=begin && a[i]<key){
            a[i+1] = a[i];
            --i;
        }
        a[i+1] = key;
    }
}


int main() {
    int a[10] = {4,1,3,9,6,2,5,0,8,7};
    for(int i = 0; i < 10; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
    insertion_sort_decrease(a, 0, 10);
    for(int i = 0; i < 10; i++){
        cout << a[i] << ' ';
    }
    return 0;
}