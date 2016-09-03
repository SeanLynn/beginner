#include <iostream>
#include <vector>
#include <list>
#include <time.h>
#include <random>
#include <iterator>
using namespace std;

void bucket_sort(vector<int> &A, int bucket){
    int A_size = A.size();
    vector<list<int>*> B(bucket, (list<int>*)nullptr);
    for(int i = 0; i < A_size; ++i){
        int index = A[i]/10;
        if(nullptr!=B[index]){
            B[index]->push_back(A[i]);
        }else{
            B[index] = new list<int>();
            B[index]->push_back(A[i]);
        }
    }
    for(int i = 0; i < bucket; ++i){
        if(nullptr!=B[i]){
            B[i]->sort();
        }
    }
    auto iterator = A.begin();
    for(int i = 0; i < bucket; ++i){
        if(nullptr!=B[i]){
            copy(B[i]->begin(), B[i]->end(), iterator);
            iterator += distance(B[i]->begin(), B[i]->end());
        }
    }
}

int main(int argc, char const *argv[])
{
    //assume that data distribute between [0,10000]
    //bucket distribute between [0.,1000]
    vector<int> A(100000);
    double dur;
    clock_t start,end;
    start = clock();
    srand(unsigned(time(nullptr)));
    for(int n = 0; n < 100000; ++n){
        A[n] = rand()%10000;
    }
    int bucket = 1000;
    bucket_sort(A, bucket);
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));//0.004
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
    return 0;
}