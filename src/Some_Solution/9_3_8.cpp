#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <algorithm>
using namespace std;

int find_median(vector<int> &A, vector<int> &B){
    int length = A.size();
    int l1 = 0, r1 = length-1, l2 = 0, r2 = r1;
    int size = r1+1;
    while(size>2){
        int median1, median2;
        if(size%2==0){
            median1 = l1+size/2 - 1;
            median2 = l2+size/2 - 1;
        }else{
            median1 = l1+size/2;
            median2 = l2+size/2;
        }
        if(A[median1] < B[median2]){
            //I don't know how to solve this extra code
            if(length%2==0)
                l1 = median1+1;
            else
                l1 = median1;
            r2 = median2;
        }else if(A[median1] > B[median2]){
            r1 = median1;
            if(length%2==0)
                l2 = median2+1;
            else
                l2 = median2;
        }else{
            return A[median1];
        }
        size = r1-l1+1;
    }
    int result = A[l1] < B[l2] ? min(A[r1], B[l2]) : min(A[l1], B[r2]);
}

int main(int argc, char const *argv[])
{
    vector<int> A{1,2,3,6,7,8,19,23,51,78,89};
    vector<int> B{3,4,5,6,7,9,10,11,17,20,39};
    // vector<int> A{1,2,3,6,7,8,19,23,51,78,89,100};
    // vector<int> B{3,4,5,6,7,9,10,11,17,20,39,70};
    int result = find_median(A, B);
    cout << result << endl;
    return 0;
}