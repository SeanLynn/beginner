#pragma once
#include <iostream>
using std::cout;
using std::endl;
typedef enum { RED, BLACK } RBColor;
template <typename T>
class RBNode {
private:
	T key;
	RBNode<T>* parent;
	RBNode<T>* left;
	RBNode<T>* right;
	RBColor color;
public:
	RBNode(RBColor c = RED) : color(c) {}
	RBNode(T k, RBNode<T>* p = nullptr, RBColor c = RED, RBNode<T>* l = nullptr, RBNode<T>* r = nullptr)
		: key(k), parent(p), left(l), right(r), color(c) {}
	void setColor(RBColor c) { color = c; }
	RBColor getColor() { return color; }
	void setKey(const T& k) { key = k; }
	void setParent(RBNode<T>* p) { parent = p; }
	void setLeftNode(RBNode<T>* l) { left = l; }
	void setRightNode(RBNode<T>* r) { right = r; }
	const T& getKey() { return key; }
	RBNode<T>* getParent() { return parent; }
	RBNode<T>* getLeftNode() { return left; }
	RBNode<T>* getRightNode() { return right; }
};