#pragma once
#include "RBNode.h"
template <typename T>
class RBTree {
private:
	RBNode<T>* root;
	RBNode<T>* nil;
	RBNode<T>* minumum(RBNode<T>* r);
	RBNode<T>* maximum(RBNode<T>* r);
	RBNode<T>* predecessor(RBNode<T>* r);
	RBNode<T>* successor(RBNode<T>* r);
	void in_order(RBNode<T>* r);
	void leftRotate(RBNode<T>* left);
	void rightRotate(RBNode<T>* right);
	void insertFixup(RBNode<T>* newNode);
	void postOrderDestruction(RBNode<T>* r);
	bool isLeftNode(RBNode<T>* r) { return r->getParent() != nil ? r->getParent()->getLeftNode() == r : false; }
	void transplant(RBNode<T>* u, RBNode<T>* v);//v replace u
	void deleteFixUp(RBNode<T>* x);
public:
	RBTree(RBNode<T>* r = nullptr, RBNode<T>* n = nullptr) {
		nil = new RBNode<T>(BLACK);
		root = nil;
		root->setParent(nil);
	}
	~RBTree() { postOrderDestruction(this->root); }
	RBNode<T>* search(const T& x);
	RBNode<T>* minimum();
	RBNode<T>* maximum();
	void insert(const T& x);
	void inOrder();
	void deleteNode(const T& x);
};

template<typename T>
inline RBNode<T>* RBTree<T>::minumum(RBNode<T>* r)
{
	if (r != this->nil) {
		while (r->getLeftNode() != this->nil) {
			r = r->getLeftNode();
		}
	}
	return r;
}

template<typename T>
inline RBNode<T>* RBTree<T>::maximum(RBNode<T>* r)
{
	if (r != this->nil) {
		while (r->getRightNode() != this->nil) {
			r = r->getRightNode();
		}
	}
	return r;
}

template<typename T>
inline RBNode<T>* RBTree<T>::predecessor(RBNode<T>* r)
{
	if (r == this->nil) {
		return r;
	}
	if (r->getLeftNode()) {
		return this->maximum(r->getLeftNode());
	}
	RBNode<T>* temp = r->getParent();
	while (temp != this->nil && temp->getLeftNode() == r) {
		r = temp;
		temp = temp->getParent();
	}
	return temp;
}

template<typename T>
inline RBNode<T>* RBTree<T>::search(const T & x)
{
	RBNode<T>* temp = this->root;
	while (temp != this->nil && temp->getKey() != x) {
		if (temp->getKey() > x) {
			temp = temp->getLeftNode();
		}
		else {
			temp = temp->getRightNode();
		}
	}
	return temp;
}

template<typename T>
inline RBNode<T>* RBTree<T>::minimum()
{
	return this->minimum(this->root);
}

template<typename T>
inline RBNode<T>* RBTree<T>::maximum()
{
	return this->maximum(this->root);
}

template<typename T>
inline void RBTree<T>::insert(const T & x)
{
	RBNode<T>* al = this->nil;
	RBNode<T>* current = this->root;
	while (current != this->nil) {
		al = current;
		if (x < current->getKey()) {
			current = current->getLeftNode();
		}
		else {
			current = current->getRightNode();
		}
	}
	RBNode<T>* newNode = new RBNode<T>(x, al, RED, this->nil, this->nil);
	if (al == this->nil) {
		this->root = newNode;
	}
	else if (x < al->getKey()) {
		al->setLeftNode(newNode);
	}
	else {
		al->setRightNode(newNode);
	}
	this->insertFixup(newNode);
}

template<typename T>
inline void RBTree<T>::inOrder()
{
	this->in_order(this->root);
	cout << endl;
}

template<typename T>
inline void RBTree<T>::deleteNode(const T & xl)
{
	RBNode<T>* x;
	RBNode<T>* z = this->search(xl); //the node I want to delete
	RBNode<T>* y = z;
	RBColor ycolor = y->getColor();
	if (z->getLeftNode() == this->nil) {
		x = z->getRightNode();
		this->transplant(z, x);
	}
	else if (z->getRightNode() == this->nil) {
		x = z->getLeftNode();
		this->transplant(z, x);
	}
	else {
		y = this->minumum(z->getRightNode());
		ycolor = y->getColor();
		x = y->getRightNode();
		if (y->getParent() == z) {
			x->setParent(y);//??
		}
		else {
			this->transplant(y, y->getRightNode());
			y->setRightNode(z->getRightNode());
			y->getRightNode()->setParent(y);
		}
		this->transplant(z, y);
		y->setLeftNode(z->getLeftNode());
		y->getLeftNode()->setParent(y);
		y->setColor(z->getColor());
	}
	if (ycolor == BLACK) {
		this->deleteFixUp(x);
	}
}

template<typename T>
inline void RBTree<T>::deleteFixUp(RBNode<T>* x)
{
	while (x != this->root && x->getColor() == BLACK) {
		if (this->isLeftNode(x)) {
			RBNode<T>* w = x->getParent()->getRightNode();
			if (w->getColor() == RED) {
				w->setColor(BLACK);
				x->getParent()->setColor(RED);
				this->leftRotate(x->getParent());
				w = x->getParent()->getRightNode();
			}
			if (w->getLeftNode()->getColor() == BLACK && w->getRightNode()->getColor() == BLACK) {
				w->setColor(RED);
				x = x->getParent();
			}
			else if (w->getRightNode()->getColor() == BLACK) {
				w->getLeftNode()->setColor(BLACK);
				w->setColor(RED);
				this->rightRotate(w);
				w = x->getParent()->getRightNode();
			}
			w->setColor(x->getParent()->getColor());
			x->getParent()->setColor(BLACK);
			w->getRightNode()->setColor(BLACK);
			this->leftRotate(x->getParent());
			x = this->root;
		}
		else {
			RBNode<T>* w = x->getParent()->getLeftNode();
			if (w->getColor() == RED) {
				w->setColor(BLACK);
				x->getParent()->setColor(RED);
				this->rightRotate(x->getParent());
				w = x->getParent()->getLeftNode();
			}
			if (w->getRightNode()->getColor() == BLACK && w->getLeftNode()->getColor() == BLACK) {
				w->setColor(RED);
				x = x->getParent();
			}
			else if (w->getLeftNode()->getColor() == BLACK) {
				w->getRightNode()->setColor(BLACK);
				w->setColor(RED);
				this->leftRotate(w);
				w = x->getParent()->getLeftNode();
			}
			w->setColor(x->getParent()->getColor());
			x->getParent()->setColor(BLACK);
			w->getLeftNode()->setColor(BLACK);
			this->rightRotate(x->getParent());
			x = this->root;
		}
	}
	x->setColor(BLACK);
}

template<typename T>
inline RBNode<T>* RBTree<T>::successor(RBNode<T>* r)
{
	if (r == this->nil) {
		return r;
	}
	if (r->getRightNode() != this->nil) {
		return this->minimum(r->getRightNode());
	}
	RBNode<T>* temp = t->getParent();
	while (temp != this->nil && temp->getRightNode() == r) {
		r = temp;
		temp = temp->getParent();
	}
	return temp;
}

template<typename T>
inline void RBTree<T>::in_order(RBNode<T>* r)
{
	if (r != this->nil) {
		this->in_order(r->getLeftNode());
		cout << r->getKey() << ' ' << r->getColor() << ' ';
		this->in_order(r->getRightNode());
	}
}

template<typename T>
inline void RBTree<T>::leftRotate(RBNode<T>* left)
{
	RBNode<T>* right = left->getRightNode();
	left->setRightNode(right->getLeftNode());
	if (right->getLeftNode() != this->nil) {
		right->getLeftNode()->setParent(left);
	}
	right->setParent(left->getParent());
	if (left->getParent() == this->nil) {
		this->root = right;
	}
	else if (left == left->getParent()->getLeftNode()) {
		left->getParent()->setLeftNode(right);
	}
	else {
		left->getParent()->setRightNode(right);
	}
	right->setLeftNode(left);
	left->setParent(right);
}

template<typename T>
inline void RBTree<T>::rightRotate(RBNode<T>* right)
{
	RBNode<T>* left = right->getLeftNode();
	right->setLeftNode(left->getRightNode());
	if (left->getRightNode() != this->nil) {
		left->getRightNode()->setParent(right);
	}
	left->setParent(right->getParent());
	if (right->getParent() == this->nil) {
		this->root = left;
	}
	else if (right->getParent()->getLeftNode() == right) {
		right->getParent()->setLeftNode(left);
	}
	else {
		right->getParent()->setRightNode(left);
	}
	left->setRightNode(right);
	right->setParent(left);
}

template<typename T>
inline void RBTree<T>::insertFixup(RBNode<T>* newNode)
{
	while (newNode->getParent()->getColor() == RED) {
		if (this->isLeftNode(newNode->getParent())) {
			RBNode<T>* temp = newNode->getParent()->getParent()->getRightNode();
			if (temp->getColor() == RED) { //true if newNode's uncle is RED
				newNode->getParent()->setColor(BLACK);
				temp->setColor(BLACK);
				newNode->getParent()->getParent()->setColor(RED);
				newNode = newNode->getParent()->getParent();
			}
			else {
				if (!this->isLeftNode(newNode)) {//true if newNode is a right child
					newNode = newNode->getParent();
					this->leftRotate(newNode);
				}
				newNode->getParent()->setColor(BLACK);
				newNode->getParent()->getParent()->setColor(RED);
				this->rightRotate(newNode->getParent()->getParent());
			}
		}
		else {
			RBNode<T>* temp = newNode->getParent()->getParent()->getLeftNode();
			if (temp->getColor() == RED) {
				newNode->getParent()->setColor(BLACK);
				temp->setColor(BLACK);
				newNode->getParent()->getParent()->setColor(RED);
				newNode = newNode->getParent()->getParent();
			}
			else {
				if (this->isLeftNode(newNode)) {
					newNode = newNode->getParent();
					this->rightRotate(newNode);
				}
				newNode->getParent()->setColor(BLACK);
				newNode->getParent()->getParent()->setColor(RED);
				this->leftRotate(newNode->getParent()->getParent());
			}
		}
	}
	this->root->setColor(BLACK);
}

template<typename T>
inline void RBTree<T>::postOrderDestruction(RBNode<T>* r)
{
	if (r != this->nil) {
		postOrderDestruction(r->getLeftNode());
		postOrderDestruction(r->getRightNode());
		delete r;
	}
}

template<typename T>
inline void RBTree<T>::transplant(RBNode<T>* u, RBNode<T>* v)
{
	if (u->getParent() == this->nil) {
		this->root = v;
	}
	else if (this->isLeftNode(u)) {
		u->getParent()->setLeftNode(v);
	}
	else {
		u->getParent()->setRightNode(v);
	}
	v->setParent(u->getParent());
}
