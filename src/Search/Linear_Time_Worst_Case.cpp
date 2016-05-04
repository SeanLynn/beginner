#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>
#include <vector>
#include <limits.h>
using namespace std;
//https://github.com/gzc/CLRS/blob/master/C09-Medians-and-Order-Statistics%2Fworst-case-linear-time.cpp
int fdmidian(vector<int>::iterator itl, int n){
    sort(itl, itl+n);
    return *(itl+n/2);
}

int partition(vector<int> &A, int p, int r, int med){
    int q = p;
    for(; q < r; ++q)
        if(A[q]==med)
            break;
    swap(A[q], A[r]);
    q = p-1;
    for(int j = p; j < r; ++j){
        if(A[j] < med){
            swap(A[++q], A[j]);
        }
    }
    swap(A[++q], A[r]);
    return q;
}

int linear_select(vector<int> &A, int p, int r, int index){
    if(index>0||index<=r-p+1){
        int n = r-p+1;
        int group = (n+4)/5;
        vector<int> median(group);
        int i = 0;
        for(; i < n/5; ++i){
            median[i] = fdmidian(A.begin()+p+i*5, 5);
        }

        if(i*5 < n){
            median[i] = fdmidian(A.begin()+p+i*5, n%5);
            i++;
        }

        int med_med = (i==1) ? median[i-1] : linear_select(median, 0, i-1, i/2);
        int pos = partition(A, p, r, med_med);
        if(pos-p == index-1)
            return A[pos];
        if(pos-p > index-1)
            return linear_select(A, p, pos-1, index);
        return linear_select(A, pos+1, r, index-pos+p-1);
    }
    return INT_MIN;
}
default_random_engine e(time(0));
int main(int argc, char const *argv[])
{
    vector<int> A(100000);    
    double dur;
    clock_t start,end;
    start = clock();
    
    for(int n = 0; n < 100000; ++n){
        A[n] = e()%100000;
    }
    
    int result = linear_select(A, 0, 99999, 7865);
    cout << result << endl;
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));//0.004
    return 0;
}