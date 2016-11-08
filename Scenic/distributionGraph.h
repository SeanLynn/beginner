#pragma once
#include <unordered_map>
#include "vertex.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class distributionGraph {
public:
	distributionGraph() {}
	~distributionGraph() {
		for each (pair<string, vertex*> var in vertexAdj)
			delete var.second;
		for each (edge* var in edgeVec){
			delete var;
		}
	}
	void createGraph();//创建图的邻接表存储
	void outputGraph();//输出图的邻接表
private:
	unordered_map<string ,vertex*> vertexAdj;
	vector<edge*> edgeVec;
	vector<string> vertexNames;//按景点初始化顺序存储景点的名字
};

void distributionGraph::createGraph() {
	//打开存有景区信息的文件
	ifstream in("info.txt");

	//读取节点数和边数,字符串转数字
	char c[128];
	memset(c, '\0', 128);
	in.getline(c, 128, ' ');
	int vertexs = atoi(c);
	memset(c, '\0', 128);
	in.getline(c, 128);
	int edges = atoi(c);
	cout << "请输入定点数和边数：" << vertexs << ' ' << edges << endl;

	//循环读取文件中的景点名字信息
	cout << "\n\t\t\"请输入各顶点的信息\"\n请输入各顶点的名字：";
	vertexNames.push_back(string(" "));
	string name;
	int i = 1;
	for (i = 1; i < vertexs; ++i) {
		memset(c, '\0', 128);
		in.getline(c, 128, ' ');
		name = c;
		cout << name << ' ';
		vertexAdj[name] = new vertex(name, i);
		vertexNames.push_back(name);
	}
	memset(c, '\0', 128);
	in.getline(c, 128);
	name = c;
	cout << name << ' ';
	vertexAdj[name] = new vertex(name, i);
	vertexNames.push_back(name);
	cout << endl;
	
	for (i = 1; i <= edges; ++i) {
		string f, t;
		int power;
		cout << "请输入第" << i << "条边的两个顶点以及该边的权值：";
		
		//获得边的起点、终点、权值
		memset(c, '\0', 128);
		in.getline(c, 128, ' ');
		f = c;
		cout << f << ' ';
		memset(c, '\0', 128);
		in.getline(c, 128, ' ');
		t = c;
		cout << t << ' ';
		memset(c, '\0', 128);
		in.getline(c, 128);
		power = atoi(c);
		cout << power << endl;

		//为节点和边添加关联关系
		vertex* from = vertexAdj[f];
		vertex* to = vertexAdj[t];
		edge* e1 = new edge(from, to, power);
		edge* e2 = new edge(to, from, power);
		edgeVec.push_back(e1);
		edgeVec.push_back(e2);
		from->addEdge(e1);
		to->addEdge(e2);
	}
	in.close();
}

//输出图的邻接表
void distributionGraph::outputGraph(){

	//判断若vertexAdj是空的，就退出重新进入控制选项
	if (vertexAdj.empty()) {
		cout << "错误!\n你还没有创建景区景点分布图，请输入 1 ！" << endl;
	}

	size_t              size = vertexAdj.size();
	vector<int>         aulVec(size+1, 32767);
	vector<vector<int>> vertexMtx(size+1, aulVec); //将要输出的邻接矩阵
	
	//遍历所有的边，更新邻接矩阵的数据
	for each (edge* eg in edgeVec){
		unsigned int from = eg->getFrom()->getNumber();
		unsigned int to   = eg->getTo()->getNumber();
		vertexMtx[from][to] = eg->getPower();
		vertexMtx[from][from] = 0;
	}

	//遍历输出
	for each (string str in vertexNames){
		printf("%8s", str.c_str());
	}
	cout << endl;

	for(size_t j = 1; j <= size; ++j){
		printf("%8s", vertexNames[j].c_str());
		for (size_t k = 1; k <= size; ++k) {
			printf("%8d", vertexMtx[j][k]);
		}
		cout << endl;
	}

}
