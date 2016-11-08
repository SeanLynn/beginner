#pragma once
#include <string>
#include <vector>
#include "edge.h"
using namespace std;
class vertex {
public:
	vertex(string n, int i) : name(n), number(i), edgeAdj() {}
	
	void addEdge(edge* e){
		edgeAdj.push_back(e);
	}

	unsigned int getNumber() {
		return number;
	}
private:
	string name;
	unsigned int number;
	vector<edge*> edgeAdj;
};