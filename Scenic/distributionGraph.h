#pragma once
#include <unordered_map>
#include "vertex.h"
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
class distributionGraph {
public:
	void createGraph();//创建图的邻接表存储
	void outputGraph();//输出图的邻接表
	void creatTourSortGraph();//输出导游线路图
	void DFSTraverse(list<vertex*>&);//深度优先遍历
	void TopoSort();//判断导游线路图有无回路
	bool isEdge();//判断两个顶点之间是否有直接相连的边
	distributionGraph() {}
	~distributionGraph();
private:
	unordered_map<string ,vertex*> vertexAdj;
	vector<edge*> edgeVec;
	vector<string> vertexNames;//按景点初始化顺序存储景点的名字
	
	bool isGraphEmpty(); //判断图是否空
	void updateVertexVisited();//更新所有点的访问状态
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

	//判断图是否为空
	if (isGraphEmpty())
		return;

	size_t              size = vertexAdj.size();
	vector<vector<int>> vertexMtx(size+1, vector<int>(size+1, 32767)); //将要输出的邻接矩阵
	
	//遍历所有的边，更新邻接矩阵的数据
	for each (edge* eg in edgeVec){
		unsigned int from = eg->getFrom()->getNumber();
		unsigned int to   = eg->getTo()->getNumber();
		vertexMtx[from][to] = eg->getPower();
		vertexMtx[from][from] = 0;
	}

	//遍历输出
	for each (string str in vertexNames)
		printf("%8s", str.c_str());
	cout << endl;

	for(size_t j = 1; j <= size; ++j){
		printf("%8s", vertexNames[j].c_str());
		for (size_t k = 1; k <= size; ++k)
			printf("%8d", vertexMtx[j][k]);
		cout << endl;
	}
}

//输出导游线路图
void distributionGraph::creatTourSortGraph() {
	
	//判断图是否为空
	if (isGraphEmpty())
		return;

	list<vertex*> tourGuide;//存储遍历路径
	DFSTraverse(tourGuide);//非递归栈辅助深度优先遍历

	list<vertex*>::const_iterator lvcbg = tourGuide.begin();
	list<vertex*>::const_iterator lvced = tourGuide.end();
	//打印所有遍历路上经历的节点
	cout << (*lvcbg)->getName();
	while (++lvcbg != lvced)
		cout << " --> " << (*lvcbg)->getName();
	cout << endl;

	//更新所有点的访问状态。
	updateVertexVisited();
}

//深度优先遍历
void distributionGraph::DFSTraverse(list<vertex*>& tourGuide) {

	stack<vertex*> stackVertex; //存储路径
	size_t         count = 1;   //已发现的景点数量

	//选择一个景点开始，并压入栈,添加进路线图
	vertex*        pCurrentVertex = vertexAdj[vertexNames[1]];
	pCurrentVertex->setVisited(true);
	stackVertex.push(pCurrentVertex);
	tourGuide.push_back(pCurrentVertex);

	//栈中还有点说明还有些边没有尝试
	while (!stackVertex.empty()) {

		const list<edge*>&          aulEdgeAdj = stackVertex.top()->getEdgeAdj();//以该景点为出度的边
		list<edge*>::const_iterator lcibg = aulEdgeAdj.begin();   //起始边iterator
		list<edge*>::const_iterator lcied = aulEdgeAdj.end();

		//遍历所有可能经过的边
		while (lcibg != lcied) {
			//判断是否访问过该边入度景点
			//如果该景点没有被访问过，将该景点状态改变，并压入栈，填进路线图
			if (!(*lcibg)->getTo()->isVisited()) {
				pCurrentVertex = (*lcibg)->getTo();
				pCurrentVertex->setVisited(true);
				stackVertex.push(pCurrentVertex);
				tourGuide.push_back(pCurrentVertex);
				
				if (++count >= vertexAdj.size()) //如果访问过所有的景点，退出遍历
					return;

				break;
			}
			else {			//若有访问过这个景点iterator++
				lcibg++;
			}
		}
		//如果是因为遍历无果退出上边的循环，pop辅助栈的景点
		if (lcibg == lcied) {
			stackVertex.pop();
			if (!stackVertex.empty()) //pop后栈顶的景点将会再次被访问
				tourGuide.push_back(stackVertex.top());
		}
	}
}


//判断图是否空
bool distributionGraph::isGraphEmpty() {
	//判断若vertexAdj是空的，就退出重新进入控制选项
	if (!vertexAdj.empty())
		return false;

	cout << "错误!\n你还没有创建景区景点分布图，请输入 1 ！" << endl;
	return true;
}


//析构函数
distributionGraph::~distributionGraph() {
	for each (const pair<string, vertex*>& var in vertexAdj)
		delete var.second;
	for each (const edge* var in edgeVec)
		delete var;
}

//更新所有点的访问状态
void distributionGraph::updateVertexVisited() {
	for each (const pair<string, vertex*>& var in vertexAdj)
		var.second->setVisited(false);
}