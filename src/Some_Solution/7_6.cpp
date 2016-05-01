#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
using namespace std;

class Overlap
{
public:
    int left;
    int right;
    Overlap(int l = 0, int r = 0){
        left = l; right = r;
    }

    friend ostream& operator<<(ostream& os ,const Overlap& self){
        os << "left: " << self.left << "  right: " << self.right << endl;
        return os;
    }

    Overlap get_overlap(Overlap& cmp){
        return Overlap(max(left, cmp.left), min(right, cmp.right));
    }

    bool is_valid(){
        return left <= right;
    }

    friend bool operator < (const Overlap& self, const Overlap& cmp){
        return self.right < cmp.left;
    }
};

int partition(Overlap* A, int p, int r){
    Overlap pivot_value = A[r];
    for(int k = p; k < r; ++k){
        Overlap next_Overlap = pivot_value.get_overlap(A[k]);
        if(next_Overlap.is_valid()){
            pivot_value = next_Overlap;
        }
    }
    int pivot = p-1;
    for(int k = p; k < r; ++k){
        if(A[k] < pivot_value){
            swap(A[++pivot], A[k]);
        }
    }
    swap(A[++pivot], A[r]);
    int j = pivot;
    for(int k = pivot+1; k <= r; ++k){
        if(pivot_value.get_overlap(A[k]).is_valid()){
            swap(A[++j], A[k]);
        }
    }
    return (pivot+j)/2;
}

int random(int l, int r){
    srand((int)time(0));
    return l+rand()%(r-l+1);
}

int randomized_partition(Overlap* A, int p, int r){
    swap(A[r], A[random(p, r)]);
    return partition(A, p, r);
}

void quick_sort(Overlap* A, int p, int r){
    if(p < r){
        int pivot(randomized_partition(A, p, r));
        quick_sort(A, p, pivot-1);
        quick_sort(A, pivot+1, r);
    }
}

void print(Overlap *ov, int l, int r){
    while(l != r){
        cout << ov[l++];
    }
    cout << ov[l];
}

Overlap *ov; 
int main(int argc, char const *argv[])
{
    double dur;
    clock_t start,end;
    start = clock();
    random_device rd;
    ov = new Overlap[100000]();
    for(int n = 0; n < 100000; ++n){
        int l = rd()%1000000;
        int r = rd()%1000000;
        if(l > r){
            swap(l, r);
        }
        ov[n].left = l;
        ov[n].right = r;
    }
    //print(v, 0, 99999);
    quick_sort(ov, 0, 99999);
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));
    print(ov, 0, 99999);
    return 0;
}