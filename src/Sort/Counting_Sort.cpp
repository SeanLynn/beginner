#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <iterator>
using namespace std;

void counting_sort(vector<int>& A, vector<int> &B, int k){
    vector<int> C(k, 0);
    for(size_t i = 0; i < A.size(); ++i){
        ++C[A[i]];
    }

    for(int i = 1; i < k; ++i){
        C[i] += C[i-1];
    }

    for(int j = A.size()-1; j >= 0; --j){
        B[C[A[j]]] = A[j];
        --C[A[j]];
    }
}

void counting_sort_non_B(vector<int>& A, int k){
    vector<int> C(k, 0);
    for(size_t i = 0; i < A.size(); ++i){
        ++C[A[i]];
    }

    for(int i = 0, j = 0; i < k; ++i){
        while(C[i]-- > 0){
            A[j++] = i;
        }
    }
}

int main(int argc, char const *argv[])
{
    vector<int> A(100000);
    //vector<int> B(100000);
    double dur;
    clock_t start,end;
    start = clock();
    srand(unsigned(time(nullptr)));
    for(int n = 0; n < 100000; ++n){
        A[n] = rand()%100000;
    }
    //counting_sort(A, B, 100000);
    counting_sort_non_B(A, 100000);
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));//0.004
    //copy(B.begin(), B.end(), ostream_iterator<int>(cout, " "));
    return 0;
}