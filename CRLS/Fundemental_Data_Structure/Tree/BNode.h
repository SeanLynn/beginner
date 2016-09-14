#pragma once

template <typename T>
class BNode {//max-degree is 4
private:
	static const int degree = 4;
	int count;
	T[degree-1] key;
	BNode<T>*[degree] children;
	bool leaf;
	int height;
public:
	BNode() : count(0), leaf(true), height(0){}
	T& getKey(int i) { return key[i]; }
	const int getDegree() { return degree; }
	void setKey(int i, T& k) { key[i] = k; }
	bool isLeaf() { return leaf; }
	void setLeaf(bool l) { leaf = l; }
	int getCount() { return count; }
	void setCount(int c) { count = c; }
	void addCount() { count++; }
	void cutCount() { count--; }
	BNode<T>* getChild(int i) { return children[i]; }
	void setChild(int i, BNode<T>* c) { children[i] = c; }
	int getHeight() { return height; }
	void setHeight(int height) { height = h; }
};