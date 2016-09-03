#include <iostream>
#include <queue>
#include <time.h>
#include <random>
using namespace std;
//https://github.com/gzc/CLRS/blob/master/C09-Medians-and-Order-Statistics/exercise_code/second-smallest.cpp
struct Node
{
    int v;
    Node *left;
    Node *right;
    bool dir;    // 0 mean left, 1 mean right
    Node() : v(-1),left(nullptr),right(nullptr){}
    Node(int _v, bool d) : v(_v),left(nullptr),right(nullptr),dir(d){}
};


int second_smallest_element(int arr[], int n)
{
    queue<Node*> q;
    for(int i = 0;i < n;i++)
    {
        Node *new_node = new Node(arr[i], 0);
        q.push(new_node);
    }
    
    Node *root(nullptr);
    while(!q.empty())
    {
        int size = q.size();
        if(size == 1)
        {
            root = q.front();
            break;
        }
        for(int i = 0;i < size;i += 2)
        {
            if(i == size - 1)
            {
                Node *n1 = q.front(); q.pop();
                q.push(n1);
                break;
            } else {
                Node *n1 = q.front(); q.pop();
                Node *n2 = q.front(); q.pop();
                int smaller = 0;
                bool dir;
                if(n1 -> v <= n2 -> v)
                {
                    smaller = n1->v;
                    dir = false;
                } else {
                    smaller = n2->v;
                    dir = true;
                }
                
                Node *new_node = new Node(smaller,dir);
                new_node->left = n1;
                new_node->right = n2;
                q.push(new_node);
            }
        }
    }
    
    int minium = root->v;
    int result(INT_MAX);
    while(root)
    {
        if(root->left && root->right)
        {
            result = min( (root->left->v ^ root->right->v ^ minium), result);
            root = root->dir == true ? root->right : root->left;
        } else break;
    }
    return result;
}


int main() {
    int A[100000];
    double dur;
    clock_t start,end;
    start = clock();
    srand(unsigned(time(nullptr)));
    for(int n = 0; n < 100000; ++n){
        A[n] = rand()%100000+rand()%100000;
    }
    //counting_sort(A, B, 100000);
    int result = second_smallest_element(A, 100000);
    end = clock();
    dur = (double)(end - start);
    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));
    cout << result << endl;
    
    return 0;
}