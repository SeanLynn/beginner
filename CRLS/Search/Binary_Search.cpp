#include <iostream>
using namespace std;

template <typename T>
int binary_search(T *a, T data, int begin, int end){
    // a is the reference to the array
    // search from [begin, end)
    int low = begin;
    int high = end-1;
    while(low <= high){
        int mid = (low+high)/2;
        if(a[mid]==data){
            return mid;
        }else if(a[mid] > data){
            high = mid;
        }else{
            low = mid;
        }
    }
    return -1;
}

int main() {
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    cout << binary_search(a, 9, 0, 10) << endl;
    return 0;
}
