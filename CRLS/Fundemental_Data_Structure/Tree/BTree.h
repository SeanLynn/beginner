#pragma once
#include "BNode.h"
#include <iostream>
#include <utility>
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
template <typename T>
class BTree {
private:
	BNode<T>* root;
	pair<BNode<T>*, T&>* search(BNode<T>* b, T& k);
	void splitChild(BNode<T>* p, int i);
	void insertNotFull(BNode<T>* b, T& k);
public:
	BTree() : root(new BNode<T>()) {}
	pair<BNode<T>*, T&>* search(T& k) { return search(root, k); }
	void insert(T& k);
};

template<typename T>
inline void BTree<T>::insertNotFull(BNode<T>* p, T & k)
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
inline void BTree<T>::splitChild(BNode<T>* p, int i)
{
	BNode<T>* right = new BNode<T>();
	BNode<T>* left = p->getChild(i);
	right->setLeaf(left->isLeaf());
	right->setCount(BNode<T>::degree / 2 - 1);
	for (int j = 0; j < BNode<T>::degree / 2 - 1; j++) {
		right->setKey(j, left->getKey(j + BNode<T>::degree / 2));
	}
	if (!left->isLeaf()) {
		for (int j = 0; j < BNode<T>::degree/2; j++) {
			right->setChild(j, left->getChild(j + BNode<T>::degree / 2));
		}
	}
	left->setCount(BNode<T>::degree / 2 - 1);
	for (int j = p->getCount(); j >= i + 1; j--) {
		p->setChild(j + 1, p->getChild(j));
	}
	p->setChild(i + 1, z);
	for (int j = p->getCount()-1; j >= 0; j--) {
		p->setKey(j + 1, p->getKey(j));
	}
	p->setKey(i, left->getKey(BNode<T>::degree / 2 - 1);
	p->addCount();
}

template<typename T>
inline void BTree<T>::insert(T & k)
{
	BNode<T>* cur = root;
	if (cur->getCount() == BNode<T>::degree - 1;) {
		BNode<T>* newRoot = new BNode<T>();
		root = newRoot;
		newRoot->setLeaf(true);
		newRoot->setChild(0, cur);
		splitChild(newRoot, 0);
		insertNotFull(newRoot, k);
	}
	else {
		insertNotFull(cur, k);
	}
}

template<typename T>
inline pair<BNode<T>*, T&>* BTree<T>::search(BNode<T>* b, T & k)
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
