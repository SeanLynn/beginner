// RBTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "RBTree.h"

int main()
{
	RBTree<int> rbt;
	rbt.insert(31);
	rbt.insert(25);
	rbt.insert(3);
	rbt.insert(10);
	rbt.insert(33);
	rbt.insert(7);
	rbt.insert(131);
	rbt.insert(321);
	rbt.inOrder();
    return 0;
}

