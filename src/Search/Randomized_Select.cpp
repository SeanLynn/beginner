#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <algorithm>
#include <iterator>
using namespace std;
default_random_engine e(time(0));
int randomized_partition(vector<int> &A, int p, int r){
    int q = p + e()%(r-p+1);
    swap(A[q], A[r]);
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

int randomized_select(vector<int> A, int p, int r, int i){
    if(p==r){
        return A[p];
    }
    int q = randomized_partition(A, p, r);
    int k = q-p+1;
    if(i==k){
        return A[q];
    }else if(i<k){
        return randomized_select(A, p, q-1, i);
    }else{
        return randomized_select(A, q+1, r, i-k);
    }
}

int main(int argc, char const *argv[])
{
    vector<int> A(100000);    
    double dur;
    clock_t start,end;
    start = clock();
    
    for(int n = 0; n < 100000; ++n){
        A[n] = e();
    }
    
    int result = randomized_select(A, 0, 99999, 1);
    cout << result << endl;
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));//0.004
    
    return 0;
}