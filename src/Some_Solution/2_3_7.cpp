#include <iostream>
#include <unordered_map>
using namespace std;
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
bool two_Sum_1(int* a, int data, int length){
    merge_sort(a, 0, length);
    int l = 0;
    int r = length-1;
    
    while(l != r){
        if(a[l]+a[r] > data){
            --r;
        }else if(a[l]+a[r] < data){
            ++l;
            //cout << l << endl;
        }else{
            return true;
        }
    }
    return false;
}
bool two_Sum_2(int* a, int data, int length){
    // using hashtable
    unordered_map<int, int> m;
    for(int i = 0; i < length; i++){
        int remain = data - a[i];
        if(m.count(remain) > 0){
            return true;
        }else{
            m[a[i]] = i+1;
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
    int a[10] = {4,1,3,9,6,2,5,0,8,7};
    cout << two_Sum_2(a, 16, 10) << endl;
    return 0;
}
