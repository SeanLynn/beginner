#pragma once
#include <iostream>
using namespace std;
template <typename T>
class BNode {//max-degree is 4
public:
	static const unsigned int degree = 4;
	BNode() : count(0), key(), children(), leaf(true), height(0){}
	T& getKey(size_t i) { return key[i]; }
	const unsigned int getDegree() { return degree; }
	void setKey(size_t i, const T& k) { key[i] = k; }
	bool isLeaf() { return leaf; }
	void setLeaf(bool l) { leaf = l; }
	size_t getCount() { return count; }
	void setCount(int c) { count = c; }
	void addCount() { count++; }
	void cutCount() { count--; }
	BNode<T>* getChild(size_t i) { return children[i]; }
	void setChild(size_t i, BNode<T>* c) { children[i] = c; }
	int getHeight() { return height; }
	void setHeight(int height) { height = h; }
	size_t search(const T& k);
	size_t findPlaceInsert(const T& k);
private:
	size_t count;
	T key[degree - 1];
	BNode<T>* children[degree];
	bool leaf;
	int height;
};

template<typename T>
inline size_t BNode<T>::search(const T & k)
{
	size_t i = 0;
	while (i < count && key[i] != k) {
		i++;
	}
	return i;
}

template<typename T>
inline size_t BNode<T>::findPlaceInsert(const T & k)
{
	size_t i = 0;
	while (i < count && key[i] < k) {
		i++;
	}
	return i;
}
