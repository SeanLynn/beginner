#include <iostream>
#include <thread>
using namespace std;

class scoped_guard {
    thread t;
public:
    explicit scoped_guard(thread t_) :
        t(move(t_))
    {
        cout << "scoped_guard()" << endl;
        if(!t.joinable())
            throw logic_error("No thread");
    }
    ~scoped_guard() {
        cout << "~scoped_guard()" << endl;
        t.join();
    }
    scoped_guard(scoped_guard const &) = delete;
    scoped_guard& operator=(scoped_guard const&) = delete;
};

struct func {
    int& i;
    func(int& i_) : i(i_) {
        cout << "func(int& i)" << endl;
    }
    func(func const & f): i(f.i) {
        cout << "func(func const &)" << endl;
    }
    void operator()() {
        for (unsigned j = 0; j < 1000000; ++j) {
            i++;
        }
    }
    ~func() {
        cout << "func is over i = " << i << endl;
    }
};
void do_something_in_current_thread(){
    cout << "do_something_in_current_thread()" << endl;
}

void f() {
    cout << "f()" << endl;
    int some_local_state = 0;
    scoped_guard g(move(thread(func(some_local_state))));
    do_something_in_current_thread();
}


int main()
{
    f();
    return 0;
}