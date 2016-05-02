#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <algorithm>
#include <iterator>
using namespace std;

void countingSort_inside_radixSort(vector<int>& A, int d){
    vector<int> C(10, 0);
    int size = A.size();
    vector<int> tempVec(size);
    for(int i = 0; i < size; ++i){
        ++C[(A[i]/d)%10];
    }
    for(int i = 1; i < 10; ++i){
        C[i] += C[i-1];
    }

    for(int j = A.size()-1; j >= 0; --j){
        int index = (A[j]/d)%10;
        tempVec[C[index]] = A[j];
        --C[index];
    }

    A = tempVec;
}

void radix_sort(vector<int> &A, int max_value){

    for(int i = 1; max_value/i>0; i*=10){
        //use a stable sort to sort array A on digit i
        countingSort_inside_radixSort(A, i);
    }
}

int main(int argc, char const *argv[])
{
    vector<int> A(100000);
    double dur;
    clock_t start,end;
    start = clock();
    srand(unsigned(time(0)));
    for(int n = 0; n < 100000; ++n){
        A[n] = rand()%100000;
    }
    //counting_sort(A, B, 100000);
    auto max_value = max_element(A.begin(), A.end());
    radix_sort(A, *max_value);
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));//0.025
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
    return 0;
}