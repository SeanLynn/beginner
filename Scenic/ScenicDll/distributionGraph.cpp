#include "stdafx.h"
#include "distributionGraph.h"

//用户输入的关键字进行景点的查找
unsigned distributionGraph::searchWithKeyWords(char* msg) {

	if (isGraphEmpty())
		return 0;

	string key(msg);
	string MSG = ""; //作为临时的输出记录string
	vector<shared_ptr<vertex>> vtHasInfo;
	queryWords(key, vtHasInfo);//KMP匹配
	if (vtHasInfo.empty()) {
		MSG.append("没有与“" + key + "”相关的内容。");
		return 0;
	}
	MSG.append("含有相关信息的有：\n");
	for each (shared_ptr<vertex> var in vtHasInfo)
	{
		MSG.append("景点：" + var->getName().substr(1));
		MSG.append("\n景点介绍：" + var->getInfo() + "\n");
	}

	auto buf = MSG.c_str();
	strcpy_s(msg, strlen(buf) + 1, buf);
	return 1;
}

//按景点欢迎度进行排序
unsigned distributionGraph::sortedByPopularity(char* msg) {
	vector<shared_ptr<vertex>> vertexSet;
	for each (auto& var in *pVertexAdj)
		vertexSet.push_back(var.second);

	quickSort(vertexSet, 0, vertexSet.size());

	string MSG = "按景点热度排序：\n";
	for each (auto v in vertexSet)
	{
		MSG.append(v->getName().substr(1) + " " + to_string(v->getPopularity()) + "\n");
	}

	auto buf = MSG.c_str();
	strcpy_s(msg, strlen(buf) + 1, buf);
	return 1;
}

//输出道路修建规划图
unsigned distributionGraph::miniSpanTree(char* msg) {
	if (isGraphEmpty()) {
		return 0;
	}

	vector<unsigned> newVertexSet(vertexNumber + 1, 0); //存储新景点的集合
	vector<shared_ptr<edge>> newEdgeSet;				//存储要建设的边的集合
	auto& rVertexAdj = *pVertexAdj;						//邻接矩阵
	auto& rVertexNames = *pVertexNames;					//景点集合
	newVertexSet[1] = 1;

	//newVertexSet首位存储目前新景点集合的点数量
	while (++newVertexSet[0] < vertexNumber) {

		unsigned v, e = 32767;
		shared_ptr<edge> minPowerEdge = nullptr;
		//找出起点在、终点不在新点集中，而边power最小的边
		for (unsigned i = 1; i <= vertexNumber; ++i)
			if (newVertexSet[i] == 1) {//如果此点在新景点集中
				auto& r = *rVertexAdj[rVertexNames[i]]->getEdgeAdj();
				for each (weak_ptr<edge> eg in r) { //遍历此点出发的所有边
					shared_ptr<edge> seg = eg.lock();
					if (seg != nullptr) {
						v = seg->getTo()->getNumber();
						//符合以下条件：终点不在新景点集中，边power较小
						if (newVertexSet[v] == 0 && seg->getPower() < e) {
							e = seg->getPower();
							minPowerEdge = seg;
						}
					}
				}
			}

		//记录符合以上条件的边和边终点的信息
		if (minPowerEdge != nullptr) {
			newVertexSet[minPowerEdge->getTo()->getNumber()] = 1;
			newEdgeSet.push_back(minPowerEdge);
		}
	}

	string MSG = "最小连通图：\n";

	//输出所有符合条件的边，即是最小生成树
	for each (shared_ptr<edge> eg in newEdgeSet)
		MSG.append("从" + eg->getFrom()->getName().substr(1) + "到"
			+ eg->getTo()->getName().substr(1) + "修一条路\n");

	auto buf = MSG.c_str();
	strcpy_s(msg, strlen(buf) + 1, buf);
	return newEdgeSet.size();
}

unsigned distributionGraph::miniDistanse(char* msg, char* start, char* end) {

	if (isGraphEmpty())
		return 0;

	string from(start), to(end);
	string MSG = "";

	auto iterator_from = pVertexAdj->find(from);
	auto iterator_to = pVertexAdj->find(to);
	if (iterator_from == (*pVertexAdj).end() || iterator_to == (*pVertexAdj).end()) {
		MSG.append("你输入的景点名称不存在，请检查！\n");
		return 0;
	}


	if (from == to) {
		MSG.append(from.substr(1) + " -> " + to.substr(1));
		MSG.append("\n最短距离：0");
		return 0;
	}

	unsigned int uintFrom = pVertexAdj->at(from)->getNumber();   //起点编号
	unsigned int uintTo = pVertexAdj->at(to)->getNumber();     //终点编号
	vector<unsigned int> shortPathTable(vertexNumber + 1);//表示V0到Vw各顶点的最短路径权值和
	vector<unsigned int> path(vertexNumber + 1);		  //表示V0到Vw各顶点的前驱顶点下标值


														  //shortestPathDijkstra(f0, path, shortPathTable);		  //迪杰斯特拉算法寻找最短路径
														  //outPutShortestPath(t1, path, shortPathTable, MSG);     //输出两景点最短路径和最短距离


	shortestPathFloyd(uintFrom, uintTo, path, MSG);

	auto buf = MSG.c_str();
	strcpy_s(msg, strlen(buf) + 1, buf);
	return 1;
}

//深度优先遍历
void distributionGraph::DFSTraverse(list<shared_ptr<vertex>>& rTourGuide) {

	stack<shared_ptr<vertex>> stackVertex; //存储路径
	size_t         count = 1;              //已发现的景点数量

										   //选择一个景点开始，并压入栈,添加进路线图
	shared_ptr<vertex> pCurrentVertex = (*pVertexAdj)[(*pVertexNames)[1]];
	pCurrentVertex->setVisited(true);
	stackVertex.push(pCurrentVertex);
	rTourGuide.push_back(pCurrentVertex);

	//栈中还有点说明还有些边没有尝试
	while (!stackVertex.empty()) {

		const shared_ptr<list<weak_ptr<edge>>> pAulEdgeAdj = stackVertex.top()->getEdgeAdj();//以该景点为出度的边
		auto ile = pAulEdgeAdj->begin();   //起始边iterator
		auto ileEnd = pAulEdgeAdj->end();

		//遍历所有可能经过的边
		while (ile != ileEnd) {
			//判断是否访问过该边入度景点
			//如果该景点没有被访问过，将该景点状态改变，并压入栈，填进路线图
			auto sile = (*ile).lock();
			if (sile != nullptr && !sile->getTo()->isVisited()) {
				pCurrentVertex = sile->getTo(); //一般确定 (*ile).lock()不是空悬指针
				pCurrentVertex->setVisited(true);
				stackVertex.push(pCurrentVertex);
				rTourGuide.push_back(pCurrentVertex);

				if (++count >= pVertexAdj->size()) {//如果访问过所有的景点，退出遍历
					updateVertexVisited();
					return;
				}

				break;
			}
			else {			//若有访问过这个景点iterator++
				++ile;
			}
		}
		//如果是因为遍历无果退出上边的循环，pop辅助栈的景点
		if (ile == ileEnd) {
			stackVertex.pop();
			if (!stackVertex.empty()) //pop后栈顶的景点将会再次被访问
				rTourGuide.push_back(stackVertex.top());
		}
	}

	//更新所有点的访问状态。
	updateVertexVisited();
}

//判断导游线路图有无回路
unsigned distributionGraph::topoSort(string& MSG) {

	//重新生成导游图
	if (!pTourGuide->empty()) {
		pTourGuide.swap(make_shared<list<shared_ptr<vertex>>>());
	}

	auto& rTourGuide = *pTourGuide;
	//非递归栈辅助深度优先遍历,并把路线图简单地存储在tourGuide中
	DFSTraverse(rTourGuide);

	//拓扑排序方法
	//内部逻辑,返回值为vector<string>*
	shared_ptr<vector<int>> result = make_shared<vector<int>>();
	//拓扑排序辅助
	aluToposort(result);
	auto& rResult = *result;

	//将结果写入msg
	for (unsigned i = 1; i <= vertexNumber; ++i)
		if (rResult[i] > 0) {
			MSG.append("图中有回路\n");

			auto& rNames = *pVertexNames;
			for (unsigned j = i; j <= vertexNumber; ++j)
				if (rResult[j] > 0)
					MSG.append(rNames[j].substr(1) + " ");

			rResult[0] = 1;
			break;
		}

	if (rResult[0] == 0) {
		MSG.append("图中没有回路");
	}
	return vertexNumber;
}

//拓扑排序方法，只为这道题而写的。
void distributionGraph::aluToposort(shared_ptr<vector<int>>& result) {
	//初始化导游图中的景点入度
	shared_ptr<matrix> map = make_shared<matrix>
		(vertexNumber + 1, vector<unsigned>(vertexNumber + 1, 0));

	shared_ptr<vector<int>> indegree = make_shared<vector<int>>(vertexNumber + 1, 0);
	auto& rMap = *map;
	auto& rIndegree = *indegree;
	auto  it = pTourGuide->begin();
	auto  iy = it;
	auto  itEnd = pTourGuide->end();
	unsigned  startNumber = (*(it))->getNumber();
	//初始化导游图的邻接矩阵
	while (++iy != itEnd) {
		unsigned from = (*it++)->getNumber();
		unsigned in = (*iy)->getNumber();
		++rMap[from][in];//权值+1
		++rIndegree[in];//入度+1
	}

	//下边这段专门为本题写,去除所有与起始点有关系的边
	rIndegree[startNumber] = -1;
	for (unsigned k = 1; k <= vertexNumber; k++) {
		if (rMap[startNumber][k] == 1)
			--rIndegree[k];
		rMap[k][startNumber] = 0;
	}
	//进行拓扑排序
	for (unsigned i = 1; i <= vertexNumber; ++i) //遍历n次
		for (unsigned j = 1; j <= vertexNumber; ++j) //找出入度为0的节点
			if (rIndegree[j] == 0) {

				rIndegree[j]--;//入度减为-1，说明已排序

				for (unsigned k = 1; k <= vertexNumber; k++) //删除与该节点关联的边
					if (rMap[j][k] == 1)
						rIndegree[k]--;
				break;
			}

	result.swap(indegree);
}

//迪杰斯特拉算法求最短路径
void distributionGraph::shortestPathDijkstra(
	unsigned startPoint, vector<unsigned>& path, vector<unsigned>& shortPathTable)
{
	vertexMtx = make_shared<matrix>(vertexNumber + 1, vector<unsigned>(vertexNumber + 1, 32767));
	Adj2Mtx(*vertexMtx);

	auto& rMatrix = *vertexMtx;
	unsigned v, w, k, min, num = vertexNumber + 1;
	vector<int> final(num); //final[k]=1表示求得startPoint到k点的最短权值了
	for (v = 1; v < num; ++v) {
		final[v] = 0;
		shortPathTable[v] = rMatrix[startPoint][v];
		path[v] = startPoint; //初始定义所有点的前驱都是startPoint，之后逐渐更新
	}
	final[startPoint] = 1;	//startPoint到startPoint不需要求路径
	path[startPoint] = 0;
	//开始主循环，每次求得startPoint到某个景点的最短路径
	for (v = 1; v < num; ++v) {
		min = 32767;
		for (w = 1; w < num; ++w) {//寻找离startPoint最近的景点
			if (!final[w] && shortPathTable[w] < min) {
				k = w;
				min = shortPathTable[w];
			}
		}
		final[k] = 1; //将目前找到的最近的景点置为1,代表找不到从startPoint到k点更近的路了
		for (w = 1; w <num;++w) {
			//如果离startPoint点最近的k点距离 + k点到w点距离 小于startPoint到w点的距离，更新并记录
			if (!final[w] && (min + rMatrix[k][w]) < shortPathTable[w]) {
				shortPathTable[w] = min + rMatrix[k][w];  //更新
				path[w] = k;                                //记录w点的前驱是k点
			}
		}
	}
}


//弗洛伊德算法求最短路径
void distributionGraph::shortestPathFloyd(unsigned startPoint, unsigned endPoint,
	vector<unsigned>& path, string& MSG)
{
	vertexMtx = make_shared<matrix>(vertexNumber + 1, vector<unsigned>(vertexNumber + 1, 32767));
	Adj2Mtx(*vertexMtx);
	auto vPath = make_shared<matrix>(vertexNumber + 1, vector<unsigned>(vertexNumber + 1, 0));
	auto& rvPath = *vPath;
	auto& rMatrix = *vertexMtx;
	//初始化路径矩阵
	for (unsigned i = 1; i <= vertexNumber; ++i)
		for (unsigned j = 1; j <= vertexNumber; ++j)
			rvPath[i][j] = j;                // "顶点i"到"顶点j"的最短路径是经过顶点j。

	for (unsigned k = 1; k <= vertexNumber; ++k) {
		for (unsigned i = 1; i <= vertexNumber; ++i) {
			for (unsigned j = 1; j <= vertexNumber; ++j) {
				unsigned tmp = (rMatrix[i][k] == 32767 || rMatrix[k][j] == 32767)
					? 32767 : (rMatrix[i][k] + rMatrix[k][j]);
				if (rMatrix[i][j] > tmp) { //如果i->j经过k点小于此前记录，更新
					rMatrix[i][j] = tmp;
					rvPath[i][j] = rvPath[i][k];
				}
			}
		}
	}

	//计算v0->v1的路径和距离
	unsigned distance = 0;
	unsigned s = startPoint;
	path[1] = startPoint;
	auto& rVertexNames = *pVertexNames;
	MSG.append("从 " + rVertexNames[startPoint].substr(1) + " 到 " + rVertexNames[endPoint].substr(1) + " :\n");
	for (unsigned i = 2; i <= vertexNumber; ++i) {
		if (rvPath[s][endPoint] != endPoint) {
			path[i] = rvPath[s][endPoint];
			distance += rMatrix[s][path[i]];
			MSG.append(rVertexNames[s].substr(1) + " -> " + rVertexNames[path[i]].substr(1) + "~~~\n");
		}
		else {
			path[i] = endPoint;
			distance += rMatrix[s][endPoint];
			MSG.append(rVertexNames[s].substr(1) + " -> " + rVertexNames[endPoint].substr(1) + "\n");
			MSG.append("最短距离： " + to_string(distance));
			break;
		}
		s = path[i];
	}
}

//输出最短路径和最短距离
void distributionGraph::outPutShortestPath(unsigned endPoint, vector<unsigned>& path,
	vector<unsigned>& shortPathTable, string& MSG)
{
	vector<unsigned int> result;
	auto& rVertexNames = *pVertexNames;
	unsigned int v = endPoint;
	do {
		result.push_back(v);
		v = path[v];
	} while (v != 0);

	v = result.size() - 1;
	while (v > 0) //起点终点不匹配
		MSG.append(rVertexNames[result[v--]].substr(1) + " -> " + rVertexNames[result[v]].substr(1) + "\n");

	MSG.append("最短距离：" + to_string(shortPathTable[endPoint]));
}


//邻接链表转邻接矩阵
void distributionGraph::Adj2Mtx(matrix& rMatrix) {
	size_t         size = pVertexAdj->size();

	//遍历所有的边，更新邻接矩阵的数据
	for each (shared_ptr<edge> eg in *pEdgeVec) {
		unsigned int from = eg->getFrom()->getNumber();
		unsigned int to = eg->getTo()->getNumber();
		rMatrix[from][to] = eg->getPower();
		rMatrix[from][from] = 0;
	}
}


//快速排序按景点受欢迎度 [from, to)
void distributionGraph::quickSort(vector<shared_ptr<vertex>>& set, unsigned from, unsigned end) {
	if (end - from < 4) { //如果区间小于4，使用插入排序
		insertSort(set, from, end);
		return;
	}
	shared_ptr<vertex> mark = set[(from + end) >> 1];
	unsigned popl = mark->getPopularity();
	unsigned left = from;
	unsigned right = end - 1;
	while (right > left) {
		while (set[left]->getPopularity() > popl)
			++left;
		while (set[right]->getPopularity() < popl)
			--right;
		//两个标兵分别从区间最左和最右相向而行，没有相遇之前，交换不符合的数
		if (right > left) {
			swap(set[left], set[right]);
			++left;
			--right;
		}
	}
	if (from < right)
		quickSort(set, from, right + 1);
	if (left < end)
		quickSort(set, left, end);
}

//kmp算法匹配图景点名称或者间接，如果content中含有target，返回true
//KMP算法的核心思想是利用已经得到的部分匹配信息来进行后面的匹配过程。 O(m+n)
bool distributionGraph::kmp(const string& target, const string& content) {
	unsigned tgLen = target.size();
	unsigned ctLen = content.size();
	if (tgLen > ctLen) {
		return false;
	}
	vector<int> vi;
	computePrefixFunction(vi, target); //kmp前缀函数
	int q = -1;
	for (unsigned i = 0; i < ctLen; ++i) {
		while (q > -1 && target[q + 1] != content[i])
			q = vi[q]; //如果出现不相等的，修正
		if (target[q + 1] == content[i])
			++q;
		if (q == tgLen - 1)
			return true;
	}
	return false;
}

//kmp前缀函数
void distributionGraph::computePrefixFunction(vector<int>& vi, const string& str) {
	vi.resize(str.size());
	unsigned m = str.size();
	vi[0] = -1;
	int k = -1;
	for (unsigned q = 1; q < m; ++q) {
		while (k >= 0 && str[k + 1] != str[q])
			k = vi[k];
		if (str[k + 1] == str[q])
			++k;
		vi[q] = k;
	}
}