#pragma once
#include <string>
#include <list>
#include "edge.h"
using namespace std;
class vertex {
public:
	vertex(string n, unsigned i, unsigned p = 0) 
		: name(n), number(i), visited(false),
		  edgeAdj(new list<edge*>()), popularity(p) {}
	
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

	void setPopularity(unsigned p) {
		popularity = p;
	}

	unsigned getPopularity() {
		return popularity;
	}
private:
	string name;         //景点名字
	unsigned number;     //景点编号
	bool visited;        //景点是否被访问过
	list<edge*>* edgeAdj;//从景点出发的边
	unsigned popularity; //景点欢迎度
};