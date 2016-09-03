#include <iostream>
#include <limits.h>
using namespace std;

template <typename T>
void MERGE_Guard(T* a, int begin, int mid, int end){
    // has guard(哨兵)
    int n1 = mid - begin;
    int n2 = end - mid;
    T L[n1+1];
    T R[n2+1];
    for(int i = 0; i < n1; i++){
        L[i] = a[begin+i];
    }
    for(int i = 0; i < n2; i++){
        R[i] = a[mid+i];
    }
    L[n1] = R[n2] = INT_MAX; // INT_MAX as mark

    for(int i = 0, j = 0, k = begin; k != end; k++){
        if(L[i] <= R[j]){
            a[k] = L[i];
            ++i;
        }else{
            a[k] = R[j];
            ++j;
        }
    }
}

template <typename T>
void MERGE(T* a, int begin, int mid, int end) {
    // no guard
    int n1 = mid - begin;
    int n2 = end - mid;
    T L[n1];
    T R[n2];
    for(int i = 0; i < n1; i++){
        L[i] = a[begin+i];
    }
    for(int i = 0; i < n2; i++){
        R[i] = a[mid+i];
    }

    int i = 0, j = 0;
    int k = begin;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            a[k] = L[i];
            ++i;
        }else{
            a[k] = R[j];
            ++j;
        }
        ++k;
    }
    // if L array has element(i < n1) copy the left elements
    if(i < n1){
        while(k < end){
            a[k] = L[i];
            ++k; ++i;
        }
    }
}
template <typename T>
void merge_sort(T* a, int begin, int end){
    // a is the reference to the array
    // sort [begin, end) in a non-increase sequence
    if(begin < end-1){
        int mid = (begin + end) / 2;
        merge_sort(a, begin, mid);
        merge_sort(a, mid, end);
        MERGE(a, begin, mid, end);
    }
}

int main() {
    int a[10] = {4,1,3,9,6,2,5,0,8,7};
    for(int i = 0; i < 10; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
    merge_sort(a, 0, 10);
    for(int i = 0; i < 10; i++){
        cout << a[i] << ' ';
    }
    return 0;
}
