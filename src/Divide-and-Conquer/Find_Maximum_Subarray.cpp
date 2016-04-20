#include <iostream>
#include <limits.h>
using namespace std;
struct max_subarray{
    int max_left;
    int max_right;
    int sum;
};
template <typename T>
max_subarray find_max_crossing_subarray(T* a, int low, int mid, int high){
    max_subarray sub;
    int left_sum = INT_MIN;
    int sum = 0;
    for(int i = mid; i >= low; --i){
        sum += a[i];
        if(sum > left_sum){
            left_sum = sum;
            sub.max_left = i;
        }
    }
    int right_sum = INT_MIN;
    sum = 0;
    for(int j = mid+1; j <= high; ++j){
        sum = sum + a[j];
        if(sum > right_sum){
            right_sum = sum;
            sub.max_right = j;
        }
    }
    sub.sum = left_sum+right_sum;
    return sub;
}

template <typename T>
max_subarray find_maximum_subarray(T* a, int low, int high){
    if(high == low){
        max_subarray sub = {low, high, a[low]};
        return sub;
    }
    else{
        int mid = (low+high)/2;
        max_subarray left_sum = find_maximum_subarray(a, low, mid);
        max_subarray right_sum = find_maximum_subarray(a, mid+1, high);
        max_subarray cross_sum = find_max_crossing_subarray(a, low, mid, high);
        if(left_sum.sum >= right_sum.sum  && left_sum.sum  >= cross_sum.sum ){
            return left_sum;
        }else if(right_sum.sum  >= left_sum.sum  && right_sum.sum  >= cross_sum.sum ){
            return right_sum;
        }else{
            return cross_sum;
        }
    }
}

template <typename T>
max_subarray find_maximum_subarray_linear_time(T* a, int low, int high){
    T max_so_far = a[low];
    T max_ending_here = a[low];

    int max_start_index = low;
    int max_ending_index = low;

    for(int i = low+1; i <= high; ++i){
        max_ending_here += a[i];
        if(max_ending_here < 0){
            max_ending_here = 0;
            max_start_index = i;
        }else if(max_ending_here > max_so_far){
            max_so_far = max_ending_here;
            max_ending_index = i;
        }
    }

    if(max_so_far > 0){
        max_subarray sub = {max_start_index, max_ending_index, max_so_far};
        return sub;
    }
    else{
        max_subarray sub = {-1,-1,0};
        return sub;
    }
}

int main(int argc, char const *argv[])
{
    int a[16] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
    max_subarray result =  find_maximum_subarray_linear_time(a, 0, 15);
    cout << result.sum  << endl;
    return 0;
}
