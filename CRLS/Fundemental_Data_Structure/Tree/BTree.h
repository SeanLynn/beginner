#pragma once
#include "BNode.h"
#include <iostream>
#include <utility>
using namespace std;
template <typename T>
class BTree {
private:
	BNode<T>* root;
	pair<BNode<T>*, T&>* search(BNode<T>* b, T& k);
	void splitChild(BNode<T>* p, int i);
	void insertNotFull(BNode<T>* b, const T& k);
	void inOrder(BNode<T>* b);
	void postDestruction(BNode<T>* b);
	void deleteNode(const T& k, BNode<T>* b);
	T & maximum(BNode<T>* b);
	T & minimum(BNode<T>* b);
public:
	BTree() : root(new BNode<T>()) {}
	~BTree() { postDestruction(root); root = nullptr; }
	pair<BNode<T>*, T&>* search(T& k) { return search(root, k); }
	void insert(const T& k);
	void inOrder();
	void deleteNode(const T& k);
};

template<typename T>
inline T & BTree<T>::minimum(BNode<T>* b) {
	while (!b->isLeaf() && (b = b->getChild(0)) != nullptr);
	return b->getKey(0);
}

template<typename T>
inline T & BTree<T>::maximum(BNode<T>* b)
{
	// TODO: 在此处插入 return 语句
	while (!b->isLeaf() && (b = b->getChild(b->getCount())) != nullptr);
	return b->getKey(b->getCount() - 1);
}

template<typename T>
void BTree<T>::deleteNode(const T & k, BNode<T>* b)
{
	size_t currn = b->getCount();
	size_t i = b->search(k);
	unsigned int t = BNode<T>::degree / 2;
	if (i == currn) { //case 3
		i = b->findPlaceInsert(k);
		auto left = b->getChild(i);
		auto leftn = left->getCount();
		if (leftn < t) {
			if (i != 0 && b->getChild(i - 1)->getCount() >= t) {
				auto lleftN = b->getChild(i - 1);
				left->setChild(leftn + 1, left->getChild(leftn));
				for (size_t j = leftn; j > 0; j--) {
					left->setKey(j, left->getKey(j - 1));
					left->setChild(j, left->getChild(j - 1));
				}
				left->setKey(0, b->getKey(i - 1));
				b->setKey(i - 1, lleftN->getKey(lleftN->getCount() - 1));
				left->setChild(0, lleftN->getChild(lleftN->getCount()));
				lleftN->cutCount();
				left->addCount();
				deleteNode(k, left);
			}
			else if (i != currn && b->getChild(i + 1)->getCount() >= t) {
				auto right = b->getChild(i + 1);
				auto rightn = right->getCount();
				left->setKey(leftn, b->getKey(i));
				left->addCount();
				left->setChild(leftn + 1, right->getChild(0));
				b->setKey(i, right->getKey(0));
				for (size_t j = 0; j < rightn - 1; j++) {
					right->setKey(j, right->getKey(j + 1));
					right->setChild(j, right->getChild(j + 1));
				}
				right->setChild(rightn - 1, right->getChild(rightn));
				right->cutCount();
				deleteNode(k, left);
			}
			else {
				if (i != currn) {
					left->setKey(leftn, b->getKey(i));
					auto right = b->getChild(i + 1);
					auto rightn = right->getCount();
					for (size_t j = 0; j < rightn; j++) {
						left->setKey(leftn + 1 + j, right->getKey(j));
						left->setChild(leftn + 1 + j, right->getChild(j));
					}
					left->setChild(leftn + rightn + 1, right->getChild(rightn));
					for (size_t j = i; j < currn - 1; j++) {
						b->setKey(j, b->getKey(j + 1));
						b->setChild(j + 1, b->getChild(j + 2));
					}
					b->cutCount();
					left->setCount(leftn + 1 + rightn);
					delete right;
					deleteNode(k, left);
				}
				else {
					auto lleftN = b->getChild(i - 1);
					auto lleftNn = lleftN->getCount();
					lleftN->setKey(lleftNn, b->getKey(i - 1));
					for (size_t j = 0; j < leftn; j++) {
						lleftN->setKey(lleftNn + 1 + j, left->getKey(j));
						left->setChild(leftn + 1 + j, left->getChild(j));
					}
					lleftN->setChild(lleftNn + leftn + 1, left->getChild(leftn));
					delete left;
					b->cutCount();
					lleftN->setCount(lleftNn + 1 + leftn);
					if (b == root && b->getCount() == 0) {
						root = lleftN;
						delete b;
					}
					deleteNode(k, lleftN);
				}
			}
		}
		else {
			deleteNode(k, left);
		}
		return;
	}
	if (b->isLeaf()) { //case 1
		while (i < currn - 1) {
			b->setKey(i, b->getKey(i + 1));
			i++;
		}
		b->cutCount();
	}
	else {//case 2
		if (b->getChild(i)->getCount() >= t) {
			T& pre = maximum(b->getChild(i));
			b->setKey(i, pre);
			deleteNode(pre, b->getChild(i));
		}
		else if (b->getChild(i + 1)->getCount() >= t) {
			T& succ = minimum(b->getChild(i + 1));
			b->setKey(i, succ);
			deleteNode(succ, b->getChild(i + 1));
		}
		else {
			auto leftNode = b->getChild(i);
			auto rightNode = b->getChild(i + 1);
			size_t leftn = leftNode->getCount();
			size_t rightn = rightNode->getCount();
			leftNode->setKey(leftn, k);
			for (size_t j = 0; j < rightn; j++) {
				leftNode->setKey(leftn + 1 + j, rightNode->getKey(j));
				leftNode->setChild(leftn + 1 + j, rightNode->getChild(j));
			}
			leftNode->setChild(leftn + 1 + rightn, rightNode->getChild(rightn));
			leftNode->setCount(leftn + 1 + rightn);
			if (b == root && currn == 1) {
				delete b;
				root = leftNode;
			}
			else {
				b->cutCount();
				for (size_t j = i; j < currn - 1; j++) {
					b->setKey(j, b->getKey(j + 1));
					b->setChild(j+1, b->getChild(j + 2));
				}
			}
			delete rightNode;
			deleteNode(k, leftNode);
		}
	}
}

template<typename T>
inline void BTree<T>::deleteNode(const T & k)
{
	if (root) {
		deleteNode(k, root);
	}
}

template<typename T>
inline void BTree<T>::postDestruction(BNode<T>* b)
{
	if (!b->isLeaf()) {
		size_t n = b->getCount();
		for (size_t i = 0; i <= n; i++) {
			postDestruction(b->getChild(i));
		}
	}
	delete b;
}

template<typename T>
inline void BTree<T>::inOrder()
{
	if (root) {
		inOrder(root);
	}
	cout << endl;
}

template<typename T>
void BTree<T>::inOrder(BNode<T>* b)
{
	if (b->isLeaf()) {
		for (size_t j = 0; j < b->getCount(); j++) {
			cout << b->getKey(j) << ' ';
		}
	}
	else {
		size_t i;
		for (i = 0; i < b->getCount(); i++) {
			inOrder(b->getChild(i));
			cout << b->getKey(i) << ' ';
		}
		inOrder(b->getChild(i));
	}

}

template<typename T>
void BTree<T>::insertNotFull(BNode<T>* p, const T & k)
{
	int i = p->getCount() - 1;
	if (p->isLeaf()) {
		while (i >= 0 && k < p->getKey(i)) {
			p->setKey(i + 1, p->getKey(i));
			i--;
		}
		p->setKey(i + 1, k);
		p->addCount();
	}
	else {
		while (i >= 0 && k < p->getKey(i)) {
			i--;
		}
		i++;
		if (p->getChild(i)->getCount() == BNode<T>::degree - 1) {
			splitChild(p, i);
			if (k > p->getKey(i)) {
				i++;
			}
		}
		insertNotFull(p->getChild(i), k);
	}
}

template<typename T>
void BTree<T>::splitChild(BNode<T>* p, int i)
{
	BNode<T>* right = new BNode<T>();
	BNode<T>* left = p->getChild(i);
	right->setLeaf(left->isLeaf());
	right->setCount(BNode<T>::degree / 2 - 1);
	for (int j = 0; j < BNode<T>::degree / 2 - 1; j++) {
		right->setKey(j, left->getKey(j + BNode<T>::degree / 2));
	}
	if (!left->isLeaf()) {
		for (int j = 0; j < BNode<T>::degree / 2; j++) {
			right->setChild(j, left->getChild(j + BNode<T>::degree / 2));
		}
	}
	left->setCount(BNode<T>::degree / 2 - 1);
	for (int j = p->getCount(); j >= i + 1; j--) {
		p->setChild(j + 1, p->getChild(j));
	}
	p->setChild(i + 1, right);
	for (int j = p->getCount() - 1; j >= i; j--) {
		p->setKey(j + 1, p->getKey(j));
	}
	p->setKey(i, left->getKey(BNode<T>::degree / 2 - 1));
	p->addCount();
}

template<typename T>
void BTree<T>::insert(const T & k)
{
	BNode<T>* cur = root;
	if (cur->getCount() == BNode<T>::degree - 1) {
		BNode<T>* newRoot = new BNode<T>();
		root = newRoot;
		newRoot->setLeaf(false);
		newRoot->setChild(0, cur);
		splitChild(newRoot, 0);
		insertNotFull(newRoot, k);
	}
	else {
		insertNotFull(cur, k);
	}
}

template<typename T>
pair<BNode<T>*, T&>* BTree<T>::search(BNode<T>* b, T & k)
{
	int i = 0;
	while (i<b->getCount() && k > b->getKey(i)) {
		i++;
	}
	if (i < b->getCount() && k == b->getKey(i)) {
		return &make_pair<BNode<T>*, T&>(b, k);
	}
	else if (b->isLeaf()) {
		return nullptr;
	}
	else {
		return search(b->getChild(i), k);
	}
}
