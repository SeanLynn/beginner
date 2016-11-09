#pragma once
#include <string>
#include <list>
#include "edge.h"
using namespace std;
class vertex {
public:
	vertex(string n, int i) 
		: name(n), number(i), visited(false), edgeAdj() {}
	
	void addEdge(edge* e){
		edgeAdj.push_back(e);
	}

	vertex* getFirstAdjVertex() {
		if (edgeAdj.front()) {
			return edgeAdj.front()->getTo();
		}
		return nullptr;
	}

	unsigned int getNumber() {
		return number;
	}

	bool isVisited() {
		return visited;
	}

	void setVisited(bool bIV) {
		visited = bIV;
	}

	const string& getName() {
		return name;
	}

	const list<edge*>& getEdgeAdj() {
		return edgeAdj;
	}
private:
	string name;
	unsigned int number;
	bool visited;
	list<edge*> edgeAdj;
};