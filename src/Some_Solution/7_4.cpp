#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

void print(int *A, int p, int r){
    //print A[p...r]
    while(p!=r){
        cout << A[p++] << ' ';
    }
    cout << A[p] << endl;
}

int tail_partition(int *A, int p, int r){
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

void tail_recursive_quick_sort(int *A, int p, int r){
    //sort A[p...r]
    // the worst condition may cause the depth of stack be n
    while(p < r){
        int pivot = tail_partition(A, p, r);
        tail_recursive_quick_sort(A, p, pivot-1);
        p = pivot + 1;
    }
}

int RANDOM(int l, int r){
    srand((int)time(0));
    return l+rand()%(r-l+1);
}

int randomized_partition(int* A, int p, int r){
    int i = RANDOM(p, r);
    swap(A[r], A[i]);
    return tail_partition(A, p, r);
}

void randomized_quick_sort(int *A, int p, int r){
// sort A[p...r]
    while(p < r){
        int pivot = randomized_partition(A, p, r);
        if(r-pivot > pivot-p){
            randomized_quick_sort(A, p, pivot-1);
            p = pivot + 1;
        }else{
            randomized_quick_sort(A, pivot+1, r);
            r = pivot-1;
        }
    }
}

int v[100000];

int main(int argc, char const *argv[])
{
    double dur;
    clock_t start,end;
    start = clock();
    random_device rd;
    for(int n = 0; n < 100000; ++n){
        v[n] = rd()%1000000;
    }
    //print(v, 0, 999);
    //tail_recursive_quick_sort(v, 0, 99999);
    randomized_quick_sort(v, 0, 99999);
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));
    //print(v, 0, 99999);
    return 0;
}