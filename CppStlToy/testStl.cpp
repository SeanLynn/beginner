#include <iostream>
// #include <thread>
#include <vector>
#include <algorithm>
// #include <time.h>
// #include <list>
#include <functional>
#include <iterator>
// #include <exception>
// #include <stack>
// #include <mutex>
// #include <deque>
// #include <bits/stl_tree.h>
// #include <memory>
// #include <stdexcept>
// #include <numeric>
// #include <string>

using namespace std;


class Int {
public:
    explicit Int(int i) : m_i(i) {}
    void print1() const {cout << '[' << m_i << ']';}
private:
    int m_i;
};

int main(int argc, char const *argv[])
{
    ostream_iterator<int> outite(cout, " ");
    int ia[6] = {2, 21, 12, 7, 19, 23};
    vector<int> iv(ia, ia + 6);

    cout << count_if(iv.begin(), iv.end(), not1(bind2nd(less<int>(), 12)));
    cout << endl;


    transform(iv.begin(), iv.end(), outite, [](int x) {return 3 * ( 2 + x);});
    cout << endl;

    for_each(iv.begin(), iv.end(), [](int i) {cout << i << ' ';});
    cout << endl;

    Int t1(3), t2(7), t3(20), t4(14), t5(68);
    vector<Int> Iv;
    Iv.push_back(t1);
    Iv.push_back(t2);
    Iv.push_back(t3);
    Iv.push_back(t4);
    Iv.push_back(t5);

    for_each(Iv.begin(), Iv.end(), mem_fun_ref(&Int::print1));
    cout << endl;
    return 0;
}


//---------------------------------------------------------------------
// int main(int argc, char const *argv[])
// {
//     ostream_iterator<int> outite(cout, " ");
//     int ia[] = {0, 1, 2, 3, 4, 5};
//     deque<int> id(ia, ia + 6);

//     copy(id.begin(), id.end(), outite);
//     cout << endl;

//     copy(ia + 1, ia + 2, front_inserter(id));
//     copy(id.begin(), id.end(), outite);
//     cout << endl;

//     copy(ia + 3, ia + 4, back_inserter(id));
//     copy(id.begin(), id.end(), outite);
//     cout << endl;

//     deque<int>::iterator ite = find(id.begin(), id.end(), 5);
//     copy(ia, ia + 3, inserter(id, ite));
//     copy(id.begin(), id.end(), outite);
//     cout << endl;

//     copy(id.rbegin(), id.rend(), outite);
//     cout << endl;

//     istream_iterator<int> inite(cin), eos;
//     copy(inite, eos, inserter(id, id.begin()));


//     copy(id.begin(), id.end(), outite);
//     cout << endl;

//     return 0;
// }

//--------------------------------------------------------------------------
// void __unguarded_linear_insert(int * __last, int __val) {
//     int * __next = __last;
//     --__next;
//     while (__val < *__next) {
//         *__last = *__next;
//         __last = __next;
//         --__next;
//     }
//     *__last = __val;
// }

// inline void __linear_insert(int * __first,
//                             int * __last) {
//     int __val = *__last;
//     if (__val < *__first) {
//         copy_backward(__first, __last, __last + 1);
//         *__first = __val;
//     }
//     else
//         __unguarded_linear_insert(__last, __val);
// }

// void insertion_sort(int * __first, int * __last) {
//     if (__first == __last) return;
//     for (int * __i = __first + 1; __i != __last; ++__i)
//         __linear_insert(__first, __i);
// }


// int main(int argc, char const *argv[])
// {
//     int iv[] = {9, 3, 6, 1, 7, 8, 2, 5, 4, 10, 12, 14, 19, 11, 16, 0, -3, -4, -20};
//     // insertion_sort(iv, iv + sizeof(iv) / sizeof(int));
//     sort(iv, iv + sizeof(iv) / sizeof(int), greater<int>());
//     for (auto i : iv)
//         cout << i << ' ';
//     return 0;
// }





//---------------------------------------------------------------------------------------
// struct even {
//     bool operator()(int x) const {
//         return x % 2 ? false : true;
//     }
// };

// int main(int argc, char const *argv[])
// {
//     int ia[] = {12, 17, 20, 22, 23, 30, 33, 40};
//     vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));

//     cout << *lower_bound(iv.begin(), iv.end(), 21) << endl;
//     cout << *upper_bound(iv.begin(), iv.end(), 21) << endl;
//     cout << *lower_bound(iv.begin(), iv.end(), 22) << endl;
//     cout << *upper_bound(iv.begin(), iv.end(), 22) << endl;

//     cout << binary_search(iv.begin(), iv.end(), 33) << endl;
//     cout << binary_search(iv.begin(), iv.end(), 34) << endl;

//     next_permutation(iv.begin(), iv.end());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;

//     prev_permutation(iv.begin(), iv.end());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;

//     random_shuffle(iv.begin(), iv.end());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;

//     partial_sort(iv.begin(), iv.begin() + 4, iv.end());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;

//     sort(iv.begin(), iv.end());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;

//     sort(iv.begin(), iv.end(), greater<int>());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;

//     iv.push_back(22);
//     iv.push_back(30);
//     iv.push_back(17);

//     stable_sort(iv.begin(), iv.end());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;

//     auto pairIte = equal_range(iv.begin(), iv.end(), 22);
//     cout << *(pairIte.first) << endl;
//     cout << *(pairIte.second) << endl;

//     pairIte = equal_range(iv.begin(), iv.end(), 25);
//     cout << *(pairIte.first) << endl;
//     cout << *(pairIte.second) << endl;

//     random_shuffle(iv.begin(), iv.end());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;

//     random_shuffle(iv.begin(), iv.end());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;

//     nth_element(iv.begin(), iv.begin() + 5, iv.end());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;

//     nth_element(iv.begin(), iv.begin() + 5, iv.end(), greater<int>());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;

//     stable_partition(iv.begin(), iv.end(), even());
//     copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
//     cout << endl;


//     return 0;
// }


//------------------------------------------------------------------------------------
// int main(int argc, char const *argv[])
// {
//     int ia[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
//     vector<int> iv1(ia, ia + 5);
//     vector<int> iv2(ia, ia + 9);

//     cout << *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).second) << endl;

//     cout << equal(iv1.begin(), iv1.end(), iv2.begin()) << endl;

//     fill(iv1.begin(), iv1.end(), 9);
//     for_each(iv1.begin(), iv1.end(), [](int a) {cout << a << ' ';});
//     cout << endl;
//     fill_n(iv1.begin(), 3, 7);
//     for_each(iv1.begin(), iv1.end(), [](int a) {cout << a << ' ';});
//     cout << endl;

//     auto ite1 = iv1.begin();
//     auto ite2 = ite1;
//     advance(ite2, 3);
//     iter_swap(ite1, ite2);
//     for_each(iv1.begin(), iv1.end(), [](int a) {cout << a << ' ';});
//     cout << endl;

//     swap(*iv1.begin(), *iv2.begin());
//     for_each(iv1.begin(), iv1.end(), [](int a) {cout << a << ' ';});
//     cout << endl;
//     for_each(iv2.begin(), iv2.end(), [](int a) {cout << a << ' ';});
//     cout << endl;

//     string stra1[] = {"syk", "SSyk"};
//     string stra2[] = {"syk", "SSYk"};

//     cout << lexicographical_compare(stra1, stra1 + 2, stra2, stra2 + 2) << endl;
//     cout << lexicographical_compare(stra1, stra1 + 2, stra2, stra2 + 2, greater<string>()) << endl;
//     return 0;
// }


//----------------------------------------------------------------------------------------------
// int main(int argc, char const *argv[])
// {
// int ia[5] = {1, 2, 3, 4, 5};
// vector<int> iv(ia, ia + 5);

// cout << accumulate(iv.begin(), iv.end(), 0) << endl;

// cout << accumulate(iv.begin(), iv.end(), 0, minus<int>()) << endl;

// cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;

// cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>()) << endl;

// ostream_iterator<int> oite(cout, " ");

// partial_sum(iv.begin(), iv.end(), oite);
// cout << endl;

// partial_sum(iv.begin(), iv.end(), oite, minus<int>());
// cout << endl;

// adjacent_difference(iv.begin(), iv.end(), oite);
// cout << endl;

// adjacent_difference(iv.begin(), iv.end(), oite, plus<int>());
// cout << endl;

// int n = 3;
// iota(iv.begin(), iv.end(), n);
// for_each(iv.begin(), iv.end(), [](int a) {cout << a << ' ';});
// return 0;
// }
//----------------------------------------------------------------------------------
// class CountTime {
//     clock_t start, finish;
// public:
//     CountTime() {
//         start = clock();
//     }
//     ~CountTime() {
//         finish = clock();
//         cout << "time : " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
//     }
// };

// int main(int argc, char const *argv[])
// {
//     CountTime count_time;
//     _Rb_tree<int, int, _Identity<int>, less<int>> itree;
//     for (unsigned i = 0; i < 1000000; ++i)
//         itree._M_insert_unique(i);
//     //1.44s

//     // cout << itree.size() << endl;
//     // itree._M_insert_unique(10);
//     // itree._M_insert_unique(7);
//     // itree._M_insert_unique(8);
//     // itree._M_insert_unique(15);
//     // itree._M_insert_unique(5);
//     // itree._M_insert_unique(6);
//     // itree._M_insert_unique(11);
//     // itree._M_insert_unique(13);
//     // itree._M_insert_unique(12);
//     // cout << itree.size() << endl;

//     // auto ite1 = itree.begin();
//     // auto ite2 = itree.end();
//     // for(; ite1 != ite2; ++ite1)
//     //     cout << *ite1 << ' '; // 5 6 7 8 10 11 12 13 15
//     // cout << endl;

//     // ite1 = itree.begin();
//     // for(; ite1 != ite2; ++ite1){
//     //     auto rbite = _Rb_tree_iterator<int>(ite1);
//     //     cout << *ite1 << '(' << rbite._M_node->_M_color << ") ";
//     // } // 5(0) 6(1) 7(0) 8(1) 10(1) 11(0) 12(0) 13(1) 15(0)
//     return 0;
// }




//-----------------------------------------------------------------
// class hierarchical_mutex
// {
//     std::mutex internal_mutex;
//     unsigned long const hierarchy_value;
//     unsigned long previous_hierarchy_value;
//     static thread_local unsigned long this_thread_hierarchy_value;

//     void check_for_hierarchy_violation()
//     {
//         if(this_thread_hierarchy_value <= hierarchy_value)
//         {
//             throw std::logic_error("mutex hierarchy violated");
//         }
//     }
//     void update_hierarchy_value()
//     {
//         previous_hierarchy_value=this_thread_hierarchy_value;
//         this_thread_hierarchy_value=hierarchy_value;
//     }
// public:
//     explicit hierarchical_mutex(unsigned long value):
//         hierarchy_value(value),
//         previous_hierarchy_value(0)
//     {}
//     void lock()
//     {
//         check_for_hierarchy_violation();
//         internal_mutex.lock();
//         update_hierarchy_value();
//     }
//     void unlock()
//     {
//         this_thread_hierarchy_value=previous_hierarchy_value;
//         internal_mutex.unlock();
//     }
//     bool try_lock()
//     {
//         check_for_hierarchy_violation();
//         if(!internal_mutex.try_lock())
//             return false;
//         update_hierarchy_value();
//         return true;
//     }
// };
// thread_local unsigned long
//     hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);

// int main()
// {
//     hierarchical_mutex m1(42);
//     hierarchical_mutex m2(2000);

// }
//-------------------------------------------------------
// struct empty_stack: std::exception
// {
//     const char* what() const throw()
//     {
//         return "empty stack";
//     }

// };

// template<typename T>
// class threadsafe_stack
// {
// private:
//     std::stack<T> data;
//     mutable std::mutex m;
// public:
//     threadsafe_stack(){}
//     threadsafe_stack(const threadsafe_stack& other)
//     {
//         std::lock_guard<std::mutex> lock(other.m);
//         data=other.data;
//     }
//     threadsafe_stack& operator=(const threadsafe_stack&) = delete;

//     void push(T new_value)
//     {
//         std::lock_guard<std::mutex> lock(m);
//         data.push(new_value);
//     }
//     std::shared_ptr<T> pop()
//     {
//         std::lock_guard<std::mutex> lock(m);
//         if(data.empty()) throw empty_stack();
//         std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
//         data.pop();
//         return res;
//     }
//     void pop(T& value)
//     {
//         std::lock_guard<std::mutex> lock(m);
//         if(data.empty()) throw empty_stack();
//         value=data.top();
//         data.pop();
//     }
//     bool empty() const
//     {
//         std::lock_guard<std::mutex> lock(m);
//         return data.empty();
//     }
// };

// int main()
// {
//     threadsafe_stack<int> si;
//     si.push(5);
//     si.pop();
//     if(!si.empty())
//     {
//         int x;
//         si.pop(x);
//     }

// }
//--------------------------------------------------
// class some_data
// {
//     int a;
//     std::string b;
// public:
//     void do_something()
//     {}
// };

// class data_wrapper
// {
// private:
//     some_data data;
//     std::mutex m;
// public:
//     template<typename Function>
//     void process_data(Function func)
//     {
//         std::lock_guard<std::mutex> l(m);
//         func(data);
//     }
// };

// some_data* unprotected;

// void malicious_function(some_data& protected_data)
// {
//     unprotected=&protected_data;
// }

// data_wrapper x;

// void foo()
// {
//     x.process_data(malicious_function);
//     unprotected->do_something();
// }

// int main()
// {
//     foo();
// }


//----------------------------------------------------------------------------
// list<int> some_list;
// mutex some_mutex;

// void add_to_list(int new_value) {
//     lock_guard<mutex> guard(some_mutex);
//     some_list.push_back(new_value);
// }

// bool list_contains(int value_to_find) {
//     lock_guard<mutex> guard(some_mutex);
//     return find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
// }

// int main()
// {
//     add_to_list(42);
//     cout << "contains(1)=" << list_contains(1) << ", contains(42)=" << list_contains(42) << endl;
// }

//--------------------------------------------------------------------
// class scoped_guard {
//     thread t;
// public:
//     explicit scoped_guard(thread t_) :
//         t(move(t_))
//     {
//         cout << "scoped_guard()" << endl;
//         if(!t.joinable())
//             throw logic_error("No thread");
//     }
//     ~scoped_guard() {
//         cout << "~scoped_guard()" << endl;
//         t.join();
//     }
//     scoped_guard(scoped_guard const &) = delete;
//     scoped_guard& operator=(scoped_guard const&) = delete;
// };

// struct func {
//     int& i;
//     func(int& i_) : i(i_) {
//         cout << "func(int& i)" << endl;
//     }
//     func(func const & f): i(f.i) {
//         cout << "func(func const &)" << endl;
//     }
//     void operator()() {
//         for (unsigned j = 0; j < 1000000; ++j) {
//             i++;
//         }
//     }
//     ~func() {
//         cout << "func is over i = " << i << endl;
//     }
// };
// void do_something_in_current_thread(){
//     cout << "do_something_in_current_thread()" << endl;
// }

// void f() {
//     cout << "f()" << endl;
//     int some_local_state = 0;
//     scoped_guard g(move(thread(func(some_local_state))));
//     do_something_in_current_thread();
// }

//-----------------------------------------------------------------------

// template<typename Iterator,typename T>
// struct accumulate_block
// {
//     void operator()(Iterator first,Iterator last,T& result)
//     {
//         result=std::accumulate(first,last,result);
//     }
// };

// template<typename Iterator,typename T>
// T parallel_accumulate(Iterator first,Iterator last,T init)
// {
//     unsigned long const length=std::distance(first,last);

//     if(!length)
//         return init;

//     unsigned long const min_per_thread=25;
//     unsigned long const max_threads=
//         (length+min_per_thread-1)/min_per_thread;

//     unsigned long const hardware_threads=
//         std::thread::hardware_concurrency();

//     unsigned long const num_threads=
//         std::min(hardware_threads!=0?hardware_threads:2,max_threads);

//     unsigned long const block_size=length/num_threads;

//     std::vector<T> results(num_threads);
//     std::vector<std::thread>  threads(num_threads-1);

//     Iterator block_start=first;
//     for(unsigned long i=0;i<(num_threads-1);++i)
//     {
//         Iterator block_end=block_start;
//         std::advance(block_end,block_size);
//         threads[i]=std::thread(
//             accumulate_block<Iterator,T>(),
//             block_start,block_end,std::ref(results[i]));
//         block_start=block_end;
//     }
//     accumulate_block<Iterator,T>()(block_start,last,results[num_threads-1]);

//     std::for_each(threads.begin(),threads.end(),
//         std::mem_fn(&std::thread::join));

//     return std::accumulate(results.begin(),results.end(),init);
// }
// int main()
// {
//     clock_t start, finish;
//     std::vector<int> vi;
//     for(int i=0;i<10000000;++i)
//     {
//         vi.push_back(10);
//     }
//     start = clock();
//     int sum=parallel_accumulate(vi.begin(),vi.end(),5);
//     finish = clock();
//     cout << "parallel time : " << (double)(finish-start)/CLOCKS_PER_SEC << endl;

//     start = clock();
//     sum = accumulate(vi.begin(), vi.end(), 5);
//     finish = clock();
//     cout << "single thread time : " << (double)(finish-start)/CLOCKS_PER_SEC << endl;

//     std::cout<<"sum="<<sum<<std::endl;
// }