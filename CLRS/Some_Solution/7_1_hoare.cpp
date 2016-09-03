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

int hoare_partition(int *A, int p, int r){
    int x = A[p];
    int i = p-1;
    int j = r+1;
    while(true){
        do{
            --j;
        }while(A[j]>x);
        do{
            ++i;
        }while(A[i]<x);
        if(i<j){
            swap(A[i], A[j]);
        }else{
            return j;
        }
    }
}

void hoare_quick_sort(int *A, int p, int r){
// sort A[p...r]
    if(p < r){
        int pivot = hoare_partition(A, p, r);
        hoare_quick_sort(A, p, pivot-1);
        hoare_quick_sort(A, pivot+1, r);
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
    hoare_quick_sort(v, 0, 99999);
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));
    print(v, 0, 99999);
    
    return 0;
}