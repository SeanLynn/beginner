#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <queue>
using namespace std;
struct Vertex {
	int color;
	int depth;
	int last;
};

class graph {
public:
	graph() : matrix(vector<vector<int>>(10, vector<int>(10, 0))), vertexs(vector<Vertex>(10)){ }
	void BFS() { return bfs(1); }
	void printPath(int from, int to);
	vector<vector<int>> matrix;
	vector<Vertex> vertexs;
	void newGraph();
private:
	void bfs(int src);
	bool addEdge(int from, int to);
	enum { WHITE, GREY, BLACK };
	int V;
};

inline void graph::printPath(int from, int to)
{
	if(from == to) {
		cout << from << ' ';
	}
	else if (vertexs[to].last == 0) {
		cout << "no path from " << from << " to " << to << " exists." << endl;
	}
	else {
		printPath(from, vertexs[to].last);
	}
}

void graph::bfs(int src)
{
	vertexs[src].color = GREY;
	vertexs[src].depth = 0;
	queue<int> Q;
	Q.push(src);
	while (!Q.empty()) {
		int crt = Q.front();
		Q.pop();
		for (int i = 1; i <= V; i++) {
			if (matrix[crt][i] == 1 && vertexs[i].color == WHITE) {
				vertexs[i].color = GREY;
				vertexs[i].depth = vertexs[crt].depth + 1;
				vertexs[i].last = crt;
				Q.push(i);
			}
		}
		vertexs[crt].color = BLACK;
	}
}

inline bool graph::addEdge(int from, int to)
{
	if (from <= V && to <= V) {
		matrix[to][from] = 1;
		matrix[from][to] = 1;
		return true;
	}
	return false;
}

void graph::newGraph()
{
	FILE* f = fopen("graph.abc", "r");
	if (f == nullptr) {
		cerr << "No input file." << endl;
		return ;
	}
	fscanf(f, "%d", &V);
	vertexs.resize(V + 1);
	for (auto vertex : vertexs) {
		vertex.color = WHITE;
		vertex.depth = -1;
		vertex.last = 0;
	}
	int from, to;
	while (!feof(f)) {
		fscanf(f, "%d %d", &from, &to);
		addEdge(from, to);
	}
	fclose(f);
}