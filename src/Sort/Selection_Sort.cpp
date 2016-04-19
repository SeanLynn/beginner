#include <iostream>

using namespace std;

template <typename T>
void selection_sort(T* a, int begin, int end){
    // a is the reference to the array
    // sort [begin, end) in a non-decrease sequence
    if(begin == end){
        return ;
    }
    for(int i = begin; i < end-1; i++){
        int min = i;
        for(int j = i; j < end; j++){
            if(a[j] < a[min]){
                min = j;
            }
        }
        auto temp = a[min];
        a[min] = a[i];
        a[i] = temp;
    }
}

int main() {
    int a[10] = {4,1,3,9,6,2,5,0,8,7};
    for(int i = 0; i < 10; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
    selection_sort(a, 0, 10);
    for(int i = 0; i < 10; i++){
        cout << a[i] << ' ';
    }
    return 0;
}