#pragma once
#include <unordered_map>
#include "vertex.h"
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
class distributionGraph {
public:
	void creatTourSortGraph();//输出导游线路图
	void DFSTraverse(list<vertex*>*);//深度优先遍历
	void TopoSort();//判断导游线路图有无回路
	bool isEdge(const string&, const string&);//判断两个顶点之间是否有直接相连的边
	void outputGraph();//输出图的邻接表
	void createGraph();//创建图的邻接表存储
	distributionGraph() {}
	~distributionGraph();
private:
	unordered_map<string ,vertex*>* vertexAdj;
	vector<edge*>* pEdgeVec;
	vector<string>* vertexNames;//按景点初始化顺序存储景点的名字
	list<vertex*>* tourGuide;//存储导游路线图
	vector<string>* toposort(vector<vector<int>>*, vector<int>*);
	vector<vector<int>>* Adj2Mtx();
	bool isGraphEmpty(); //判断图是否空
	void updateVertexVisited();//更新所有点的访问状态
};

//输出导游线路图
void distributionGraph::creatTourSortGraph() {
	
	//判断图是否为空
	if (isGraphEmpty())
		return;

	list<vertex*>* tempTourGuide = new list<vertex*>();
	DFSTraverse(tempTourGuide);//非递归栈辅助深度优先遍历

	list<vertex*>::const_iterator lvcbg = tempTourGuide->begin();
	list<vertex*>::const_iterator lvced = tempTourGuide->end();
	//打印所有遍历路上经历的节点
	cout << (*lvcbg)->getName();
	while (++lvcbg != lvced)
		cout << " --> " << (*lvcbg)->getName();
	cout << endl;

	//更新所有点的访问状态。
	updateVertexVisited();
	tourGuide = tempTourGuide;
}

//深度优先遍历
void distributionGraph::DFSTraverse(list<vertex*>* tourGuide) {

	stack<vertex*>* stackVertex = new stack<vertex*>(); //存储路径
	size_t         count = 1;   //已发现的景点数量

	//选择一个景点开始，并压入栈,添加进路线图
	vertex*        pCurrentVertex = (*vertexAdj)[(*vertexNames)[1]];
	pCurrentVertex->setVisited(true);
	stackVertex->push(pCurrentVertex);
	tourGuide->push_back(pCurrentVertex);

	//栈中还有点说明还有些边没有尝试
	while (!stackVertex->empty()) {

		const list<edge*>*          aulEdgeAdj = stackVertex->top()->getEdgeAdj();//以该景点为出度的边
		list<edge*>::const_iterator lcibg = aulEdgeAdj->begin();   //起始边iterator
		list<edge*>::const_iterator lcied = aulEdgeAdj->end();

		//遍历所有可能经过的边
		while (lcibg != lcied) {
			//判断是否访问过该边入度景点
			//如果该景点没有被访问过，将该景点状态改变，并压入栈，填进路线图
			if (!(*lcibg)->getTo()->isVisited()) {
				pCurrentVertex = (*lcibg)->getTo();
				pCurrentVertex->setVisited(true);
				stackVertex->push(pCurrentVertex);
				tourGuide->push_back(pCurrentVertex);
				
				if (++count >= vertexAdj->size()) { //如果访问过所有的景点，退出遍历
					delete stackVertex;
					return;
				}

				break;
			}
			else {			//若有访问过这个景点iterator++
				lcibg++;
			}
		}
		//如果是因为遍历无果退出上边的循环，pop辅助栈的景点
		if (lcibg == lcied) {
			stackVertex->pop();
			if (!stackVertex->empty()) //pop后栈顶的景点将会再次被访问
				tourGuide->push_back(stackVertex->top());
		}
	}
	delete stackVertex;
}

//判断导游线路图有无回路
void distributionGraph::TopoSort() {
	auto size = vertexNames->size();
	//初始化导游图中的景点入度
	vector<vector<int>>* map = new vector<vector<int>>(size, vector<int>(size, 0));
	vector<int>*         indegree = new vector<int>(size, 0);
	auto                 it = tourGuide->begin();

	while(it != tourGuide->end()){
		auto iy = ++it;
		if (iy != tourGuide->end()) {
			int & power = (*map)[(*it)->getNumber()][(*iy)->getNumber()];
			if (!power) {
				power++;
				(*indegree)[(*it)->getNumber()]++;
			}
		}
	}
	//内部逻辑,返回值为vector<string>*
	auto result = toposort(map, indegree);

	if (result->size() != size-1) {
		cout << "图中有回路" << endl;
	}

	delete result;
	delete map;
	delete indegree;
}

vector<string>* distributionGraph::toposort(vector<vector<int>>* map, vector<int>* indegree) {
	unsigned i, j, k, size = indegree->size();
	vector<string>* result = new vector<string>(indegree->size()-1);
	for (i = 1;i<size;i++){ //遍历n次
		for (j = 1;j<size;j++){ //找出入度为0的节点
			if ((*indegree)[j] == 0){
				(*indegree)[j]--;
				result->push_back((*vertexNames)[j]);
				for (k = 1;k<size;k++) //删除与该节点关联的边
					if ((*map)[j][k] == 1)
						(*indegree)[k]--;
				break;
			}
		}
	}
	return result;
}

inline bool distributionGraph::isEdge(const string& f, const string& t) {
	return vertexAdj->at(f)->isAccessDirect(vertexAdj->at(t));
}

//输出图的邻接表
void distributionGraph::outputGraph(){

	//判断图是否为空
	if (isGraphEmpty())
		return;

	auto vertexMtx = Adj2Mtx();
	auto tempVertexNames = vertexNames;
	auto size = vertexAdj->size();

	//遍历输出
	for each (string str in *tempVertexNames)
		printf("%8s", str.c_str());
	cout << endl;

	for(size_t j = 1; j <= size; ++j){
		printf("%8s", (*tempVertexNames)[j].c_str());
		for (size_t k = 1; k <= size; ++k)
			printf("%8d", (*vertexMtx)[j][k]);
		cout << endl;
	}
}

//创建图的邻接表存储
void distributionGraph::createGraph() {

	vertexNames  = new vector<string>();
	pEdgeVec     = new vector<edge*>();
	vertexAdj    = new unordered_map<string, vertex*>();
	string name;
	int i;
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
	
	vertexNames->push_back(string(" "));
	
	for (i = 1; i < vertexs; ++i) {
		memset(c, '\0', 128);
		in.getline(c, 128, ' ');
		name = c;
		cout << name << ' ';
		(*vertexAdj)[name] = new vertex(name, i);
		vertexNames->push_back(name);
	}
	memset(c, '\0', 128);
	in.getline(c, 128);
	name = c;
	cout << name << ' ';
	(*vertexAdj)[name] = new vertex(name, i);
	vertexNames->push_back(name);
	cout << endl;
	
	//读取边信息
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
		vertex* from = (*vertexAdj)[f];
		vertex* to = (*vertexAdj)[t];
		edge* e1 = new edge(from, to, power);
		edge* e2 = new edge(to, from, power);
		pEdgeVec->push_back(e1);
		pEdgeVec->push_back(e2);
		from->addEdge(e1);
		to->addEdge(e2);
	}
	in.close();
}

//判断图是否空
inline bool distributionGraph::isGraphEmpty() {
	//判断若vertexAdj是空的，就退出重新进入控制选项
	if (!vertexAdj->empty())
		return false;

	cout << "错误!\n你还没有创建景区景点分布图，请输入 1 ！" << endl;
	return true;
}

//邻接链表转邻接矩阵
vector<vector<int>>* distributionGraph::Adj2Mtx(){
	vector<edge*>* tempPEdgeVec = pEdgeVec;
	size_t         size = vertexAdj->size();
	 
	//将要输出的邻接矩阵及其初始化
	vector<vector<int>>* vertexMtx = new vector<vector<int>>(size + 1, vector<int>(size + 1, 32767));

	//遍历所有的边，更新邻接矩阵的数据
	for each (edge* eg in *tempPEdgeVec){
		unsigned int from = eg->getFrom()->getNumber();
		unsigned int to   = eg->getTo()->getNumber();
		(*vertexMtx)[from][to] = eg->getPower();
		(*vertexMtx)[from][from] = 0;
	}

	return vertexMtx;
}

//析构函数
distributionGraph::~distributionGraph() {
	for each (const pair<string, vertex*>& var in *vertexAdj)
		delete var.second;
	for each (const edge* var in *pEdgeVec)
		delete var;
	delete vertexAdj;
	delete pEdgeVec;
	delete tourGuide;
}

//更新所有点的访问状态
inline void distributionGraph::updateVertexVisited() {
	for each (auto var in *vertexAdj)
		var.second->setVisited(false);
}