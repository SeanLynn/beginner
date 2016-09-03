#include <iostream>

using namespace std;

template <typename T>
int MERGE(T* a, int begin, int mid, int end) {
    // no guard
    int inversion = 0;
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
            inversion += n1-i;
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
    return inversion;
}
template <typename T>
int merge_sort(T* a, int begin, int end){
    // a is the reference to the array
    // sort [begin, end) in a non-increase sequence
    int inversion = 0;
    if(begin < end-1){
        int mid = (begin + end) / 2;
        inversion += merge_sort(a, begin, mid);
        inversion += merge_sort(a, mid, end);
        inversion += MERGE(a, begin, mid, end);
    }
    return inversion;
}

int main(int argc, char const *argv[])
{
    int a[10] = {2,3,8,6,1};
    for(int i = 0; i < 5; i++){
        cout << a[i] << ' ';
    }
    cout << endl;
    int inversion = merge_sort(a, 0, 5);
    cout << inversion << endl;
    return 0;
}