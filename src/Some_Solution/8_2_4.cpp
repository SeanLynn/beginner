#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <time.h>
using namespace std;

void preprocessing(vector<int>& A, vector<int> &C, int k){
    for(size_t i = 0; i < A.size(); ++i){
        C[A[i]] = C[A[i]]+1;
    }

    for(int i = 1; i < k; ++i){
        C[i] = C[i] + C[i-1];
    }
}

int main(int argc, char const *argv[])
{
    vector<int> A(100000);
    vector<int> C(10000, 0);
    srand((time(nullptr)));
    random_device rd;
    for(int n = 0; n < 100000; ++n){
        A[n] = rand()%10000;
    }

    preprocessing(A, C, 10000);
    int a = 2323;
    int b = 7878;
    cout << "[2323,7878]: " << C[b]-C[a]+1 << endl; 
    //copy(B.begin(), B.end(), ostream_iterator<int>(cout, " "));
    return 0;
}