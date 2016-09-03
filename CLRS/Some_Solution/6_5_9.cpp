#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// https://github.com/KickAlgorithm/leetcode/blob/master/cpp/021-030/Merge%20k%20Sorted%20Lists%20.cpp
struct ListNode
{
    int value;
    ListNode* next;
    ListNode(int x) : value(x), next(nullptr) {}
};

struct cmp
{
    bool operator()(ListNode* n1, ListNode* n2){
        return n1->value >= n2->value;
    }
};

class Merge_k_sorted_lists
{
public:
    Merge_k_sorted_lists(){}
    ~Merge_k_sorted_lists(){}
    ListNode *mergeKLists(vector<ListNode*> &lists){
        priority_queue<ListNode*, vector<ListNode*>, cmp> qs;
        for(size_t i = 0; i < lists.size(); ++i){
            if(lists[i])
                qs.push(lists[i]);
        }
        if(qs.empty()) return nullptr;
        ListNode* head(qs.top()), *backup(head);
        while(!qs.empty()){
            ListNode* node = qs.top();
            qs.pop();
            if(node->next) qs.push(node->next);
            head->next = qs.top();
            head = head->next;
        }
        head->next = nullptr;
        return backup;
    }
};

int main(int argc, char const *argv[])
{
    Merge_k_sorted_lists m;
    ListNode* n1 = new ListNode(1);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(3);
    ListNode* n4 = new ListNode(4);
    ListNode* n5 = new ListNode(10);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;

    ListNode* n6 = new ListNode(4);
    ListNode* n7 = new ListNode(6);
    ListNode* n8 = new ListNode(7);
    ListNode* n9 = new ListNode(8);
    ListNode* n10 = new ListNode(9);
    n6->next = n7;
    n7->next = n8;
    n8->next = n9;
    n9->next = n10;

    vector<ListNode*> v;
    v.push_back(n1);
    v.push_back(n6);
    ListNode *head = m.mergeKLists(v);
    while(head){
        cout << head->value << endl;
        head = head->next;
    }
    return 0;
}