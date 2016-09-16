#pragma once

template <typename T>
class BNode {//max-degree is 4
public:
	static const int size_t = 4;
	BNode() : count(0), key(), children(), leaf(true), height(0){}
	T& getKey(size_t i) { return key[i]; }
	const int getDegree() { return degree; }
	void setKey(size_t i, const T& k) { key[i] = k; }
	bool isLeaf() { return leaf; }
	void setLeaf(bool l) { leaf = l; }
	int getCount() { return count; }
	void setCount(int c) { count = c; }
	void addCount() { count++; }
	void cutCount() { count--; }
	BNode<T>* getChild(size_t i) { return children[i]; }
	void setChild(size_t i, BNode<T>* c) { children[i] = c; }
	int getHeight() { return height; }
	void setHeight(int height) { height = h; }
private:
	size_t count;
	T key[degree - 1];
	BNode<T>* children[degree];
	bool leaf;
	int height;
};