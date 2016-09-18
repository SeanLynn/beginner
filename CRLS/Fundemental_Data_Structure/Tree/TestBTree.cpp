// BTree.cpp : ��������̨Ӧ�ó��������ڵ㡣
//

#include "BTree.h"

int main()
{
	BTree<int> tree;
	tree.insert(10);
	tree.insert(312);
	tree.insert(31);
	tree.insert(23);
	tree.insert(15);
	tree.insert(76);
	tree.insert(3);
	tree.insert(43);
	tree.insert(27);
	tree.insert(82);
	tree.insert(112);
	tree.inOrder();
	tree.deleteNode(31);
	tree.inOrder();
    return 0;
}

