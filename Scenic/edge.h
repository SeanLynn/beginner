#pragma once
#include "vertex.h"
#include <memory>
using std::shared_ptr;
class vertex;
class edge {
public:
	edge(shared_ptr<vertex> f, shared_ptr<vertex> t, int d)
	: from(f), to(t), distance(d){}

	shared_ptr<vertex>& getFrom(){
		return from;
	}

	shared_ptr<vertex>& getTo(){
		return to;
	}

	const unsigned getPower() const{
		return distance;
	}
private:
	shared_ptr<vertex> from;
	shared_ptr<vertex> to;
	unsigned distance;
};