// RBTree.cpp : ��������̨Ӧ�ó��������ڵ㡣
//

#include "RBTree.h"

#include <time.h>

using namespace std;

class CountTime {
	clock_t start, finish;
public:
	CountTime() {
		start = clock();
	}
	~CountTime() {
		finish = clock();
		cout << "time : " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	}
};

int main()
{
	CountTime count_time;

	RBTree<int> rbt;
	for (unsigned i = 0; i < 1000000; ++i)
		rbt.insert(i);
	rbt.inOrder();

	// rbt.insert(31);
	// rbt.insert(25);
	// rbt.insert(3);
	// rbt.insert(10);
	// rbt.insert(33);
	// rbt.insert(7);
	// rbt.insert(131);
	// rbt.insert(321);
	// rbt.insert(32);
	// rbt.insert(1);
	// rbt.insert(41);
	// rbt.insert(11);
	// rbt.insert(333);
	// rbt.insert(-23);
	// rbt.insert(9);
	// rbt.insert(32);
	// rbt.inOrder();
	// rbt.deleteNode(33);
// 	rbt.inOrder();
	return 0;
}

