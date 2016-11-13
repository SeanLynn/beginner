#pragma once
#include <string>
#include <list>
#include "edge.h"
using namespace std;
class vertex {
public:
	vertex(string n, int i) 
		: name(n), number(i), visited(false), edgeAdj(new list<edge*>()) {}
	
	~vertex() {
		delete edgeAdj;
	}

	void addEdge(edge* e){
		edgeAdj->push_back(e);
	}

	const list<edge*>* getEdgeAdj() const {
		return edgeAdj;
	}

	unsigned int getNumber() const {
		return number;
	}

	bool isVisited() const {
		return visited;
	}

	void setVisited(bool bIV) {
		visited = bIV;
	}

	const string& getName() const{
		return name;
	}

	bool isAccessDirect(const vertex* t) {
		for each (const auto eg in *edgeAdj)
			if (eg->getTo() == t)
				return true;
		return false;
	}
private:
	string name;
	unsigned int number;
	bool visited;
	list<edge*>* edgeAdj;
};