#pragma once
#include "vertex.h"
class vertex;
class edge {
public:
	edge(vertex* f, vertex* t, int d)
	: from(f), to(t), distance(d){}

	vertex* getFrom(){
		return from;
	}

	vertex* getTo(){
		return to;
	}

	const unsigned getPower() const{
		return distance;
	}
private:
	vertex* from;
	vertex* to;
	unsigned distance;
};