#pragma once
#include "vertex.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>
class distributionGraph {
public:
	unsigned createLoopGraph(char *);				//按题目要求生成回路。
	unsigned createTourGuide(char*);				//创建导游图
	unsigned createVertex(char*, unsigned, char*, bool, bool);	//创建新节点或者更新纠结点
	unsigned createEdge(char*, char*, unsigned);	//创建新的无向边
	unsigned searchWithKeyWords(char*);				//用户输入的关键字进行景点的查找
	unsigned sortedByPopularity(char* msg);			//按景点欢迎度进行排序
	unsigned miniDistanse(char*, char*, char*);		//求两景点间的最短路径
	unsigned topoSort(string&);						//判断导游线路图有无回路
	unsigned miniSpanTree(char*);					//输出道路修建规划图
	distributionGraph();							//构造函数
private:
	typedef vector<vector<unsigned>> matrix;		//matrix的typedef
	shared_ptr<unordered_map<string,
		shared_ptr<vertex>>> pVertexAdj;             //名字->景点 hash表
	shared_ptr<vector<shared_ptr<edge>>> pEdgeVec;  //所有边的集合，方便析构
	shared_ptr<vector<string>> pVertexNames;			//按景点初始化顺序存储景点的名字
	shared_ptr<list<shared_ptr<vertex>>> pTourGuide;	//存储导游路线图
	shared_ptr<matrix> vertexMtx;					//存储邻接矩阵
	unsigned vertexNumber;							//景点数量
	unsigned edgeNumber;							//无向边数量，实际边*2

	void DFSTraverse(list<shared_ptr<vertex>>&);	//深度优先遍历
	bool isEdge(const string&, const string&);		//判断两个顶点之间是否有直接相连的边
	void aluToposort(shared_ptr<vector<int>>&);		//求有无回路,拓扑排序改编
	void Adj2Mtx(matrix&);					    	//邻接链表转邻接矩阵
	bool isGraphEmpty();							//判断图是否空
	void updateVertexVisited();						//更新所有点的访问状态
	void shortestPathDijkstra(unsigned,
		vector<unsigned>&, vector<unsigned>&);		//迪杰斯特拉算法求最短路径
	void shortestPathFloyd(unsigned, unsigned,
		vector<unsigned>&, string&);				//弗洛伊德算法求最短路径
	void outPutShortestPath(unsigned, vector<unsigned>&,
		vector<unsigned>&, string&);				//输出所求的最短路径
	void quickSort(vector<shared_ptr<vertex>>&,
		unsigned, unsigned);						//快速排序按景点受欢迎度
	void insertSort(vector<shared_ptr<vertex>>&,
		unsigned, unsigned);						//插入排序按景点受欢迎度
	void queryWords(const string&,
		vector<shared_ptr<vertex>>&);				//在景点及其简介中搜索关键字
	bool kmp(const string&, const string&);			//kmp算法匹配图景点名称或者间接
	void computePrefixFunction(vector<int>&,
		const string&);								//kmp前缀函数
};

//按题目要求生成回路。
inline unsigned distributionGraph::createLoopGraph(char * msg)
{
	if (isGraphEmpty()) {
		return 0;
	}
	string MSG = "";
	unsigned i = topoSort(MSG); //拓扑排序根据导游图生成回路
	auto buf = MSG.c_str();
	strcpy_s(msg, strlen(buf) + 1, buf);
	return i;
}

//创建导游图
inline unsigned distributionGraph::createTourGuide(char* msg) {
	//判断图是否为空
	if (isGraphEmpty())
		return 0;

	//将以前创建的tourGuide清空
	if (!pTourGuide->empty()) {
		pTourGuide.swap(make_shared<list<shared_ptr<vertex>>>());
	}

	auto& rTourGuide = *pTourGuide;
	//非递归栈辅助深度优先遍历,并把路线图简单地存储在tourGuide中
	DFSTraverse(rTourGuide);

	auto iterator_current = rTourGuide.begin();
	auto iterator_end = rTourGuide.end();
	//记录所有遍历路上经历的节点
	string MSG = (*iterator_current)->getName().substr(1);;
	while (++iterator_current != iterator_end)
		MSG.append(" --> " + (*iterator_current)->getName().substr(1));

	auto buf = MSG.c_str();
	strcpy_s(msg, strlen(buf) + 1, buf);
	return rTourGuide.size();
}

//创建新无向边，即两条有向边
inline unsigned distributionGraph::createEdge(char* start, char* end, unsigned distance) {
	//点的存在是确定的，已经在UI层判断
	auto pStartVertex = (*pVertexAdj)[start];
	auto pEndVertex = (*pVertexAdj)[end];

	//遍历所有边，确保无重复，若有重复更新权值即可
	for each (auto pEdge in *pEdgeVec)
		if (pEdge->getFrom() == pStartVertex && pEdge->getTo() == pEndVertex) {
			pEdge->setPower(distance);
			return pEdgeVec->size();
		}
	shared_ptr<edge> pEdge1 = make_shared<edge>(pStartVertex, pEndVertex, distance);
	shared_ptr<edge> pEdge2 = make_shared<edge>(pEndVertex, pStartVertex, distance);
	pEdgeVec->push_back(pEdge1);
	pEdgeVec->push_back(pEdge2);
	++edgeNumber;
	pStartVertex->addEdge(pEdge1);
	pEndVertex->addEdge(pEdge2);
	return pEdgeVec->size();
}

//被WPF调用创建或更改节点
inline unsigned distributionGraph::createVertex(char* name, unsigned popu, char* info, bool r, bool w)
{
	auto it = (*pVertexAdj).find(name);
	unsigned i;
	if (it != (*pVertexAdj).end()) { //如果已经存在这个点，更新这个点的信息即可
		it->second->setPopularity(popu);
		it->second->setInfo(info);
		it->second->setRestArea(r);
		it->second->setWC(w);
		i = it->second->getNumber();
	}
	else {//如果不存在这个点创建
		i = (*pVertexAdj).size() + 1;
		(*pVertexAdj)[name] = make_shared<vertex>(name, i, popu, info, r, w);
		pVertexNames->push_back(name);
		++vertexNumber;
	}
	return vertexNumber;
}

//判断是否存在f->t的边
inline bool distributionGraph::isEdge(const string& f, const string& t) {
	return pVertexAdj->at(f)->isAccessDirect(pVertexAdj->at(t));
}

//判断图是否空
inline bool distributionGraph::isGraphEmpty() {
	//判断若vertexAdj是空的，就退出重新进入控制选项
	if (!pVertexAdj->empty())
		return false;
	return true;
}

//更新所有点的访问状态
inline void distributionGraph::updateVertexVisited() {
	for each (auto& var in *pVertexAdj)
		var.second->setVisited(false);
}

//插入排序按景点受欢迎度
inline void distributionGraph::insertSort(vector<shared_ptr<vertex>>& set, unsigned from, unsigned to) {
	if (to - from <= 1)
		return;
	for (unsigned i = from + 1; i < to; ++i)
		for (unsigned j = i;
			j > from && set[j - 1]->getPopularity() < set[j]->getPopularity();
			--j)
			swap(set[j - 1], set[j]); //第j位数与前一位数比较，若比它大，交换
}

//构造函数
inline distributionGraph::distributionGraph()
	:pVertexAdj(make_shared<unordered_map<string, shared_ptr<vertex>>>()),
	pEdgeVec(make_shared<vector<shared_ptr<edge>>>()),
	pVertexNames(make_shared<vector<string>>()),
	pTourGuide(make_shared<list<shared_ptr<vertex>>>()),
	vertexNumber(0),
	edgeNumber(0)
{
	pVertexNames->push_back(" ");//插首位空位
}

//在景点及其简介中搜索关键字
inline void distributionGraph::queryWords(const string& key, vector<shared_ptr<vertex>>& vtHasInfo) {
	for each (auto& var in *pVertexAdj) {
		const string& name = var.first;
		const string& info = var.second->getInfo();
		if (kmp(key, name) || kmp(key, info)) {//匹配景点名字和简介
			vtHasInfo.push_back(var.second);
		}
	}
}