#include <iostream>
using namespace std;

template <typename T>
void bubble_sort(T* a, int begin, int end){
    // a is the reference to the array
    // sort [begin, end) in a non-increase sequence
    for(int i = begin; i < end-1; i++){
        for(int j = end-1; j > i; --j){
            if(a[j] < a[j-1]){
                auto temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
            }
        }
    }
}

int main() {
    int a[10] = {4,1,3,9,6,2,5,0,8,7};
    for(int i = 0; i < 10; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
    bubble_sort(a, 0, 10);
    for(int i = 0; i < 10; i++){
        cout << a[i] << ' ';
    }
    return 0;
}