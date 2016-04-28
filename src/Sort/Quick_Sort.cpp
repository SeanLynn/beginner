#include <iostream>
#include <algorithm>
using namespace std;

void print(int *A, int p, int r){
    //print A[p...r]
    while(p!=r){
        cout << A[p++] << ' ';
    }
    cout << A[p] << endl;
}

int partition(int *A, int p, int r){
    // sort A[p...r]
    int pivot_value = A[r];
    int pivot = p-1;
    for(int j = p; j < r; ++j){
        if(A[j] < pivot_value){
            swap(A[++pivot], A[j]);
        }
    }
    swap(A[++pivot], A[r]);
    return pivot;
}

void quick_sort(int *A, int p, int r){
    // sort A[p...r]
    if(p < r){
        int pivot = partition(A, p, r);
        quick_sort(A, p, pivot-1);
        quick_sort(A, pivot+1, r);
    }
}

int main(int argc, char const *argv[])
{
    int v[10] = {4,5,0,2,4,9,4,4,2,4};
    print(v, 0, 9);
    quick_sort(v, 0, 9);
    print(v, 0, 9);
    return 0;
}