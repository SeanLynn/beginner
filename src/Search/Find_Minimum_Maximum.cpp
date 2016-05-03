#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

pair<int, int> find_minimum_maximum(vector<int> &A){
    int size = A.size();
    int min, max;
    //assume that size > 2
    if(size%2==0){
        min = A[0];
        max = A[1];
    }else{
        min = max = A[0];
    }

    for(int i = 2; i < size; i+=2){
        if(A[i] > A[i+1]){
            if(min > A[i]){
                min = A[i];
            }
            if(max < A[i+1]){
                max = A[i+1];
            }
        }else{
            if(min > A[i+1]){
                min = A[i+1];
            }
            if(max < A[i]){
                max = A[i];
            }
        }
    }
    pair<int, int> p(min, max);
    return p;
}


int main(int argc, char const *argv[])
{
    vector<int> A(100000);
    double dur;
    clock_t start,end;
    start = clock();
    srand(unsigned(time(nullptr)));
    for(int n = 0; n < 100000; ++n){
        A[n] = rand()%10000;
    }

    pair<int, int> p(find_minimum_maximum(A));
    end = clock();
    dur = (double)(end - start);
    cout << "Use Time:" << (dur/CLOCKS_PER_SEC) << endl;
    cout << p.first << " " << p.second << endl;
    return 0;
}