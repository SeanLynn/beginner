// Scenic.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "distributionGraph.h"
#include <memory>
#include <stdlib.h>
#include <crtdbg.h>
shared_ptr<distributionGraph> graph = make_shared<distributionGraph>();

//主程序提供程序所需的各种接口
extern "C" __declspec(dllexport) unsigned CreateNewVertex(
	char*, unsigned, char*, bool, bool);   //创建或者更新点
extern "C" __declspec(dllexport) unsigned CreateNewEdge(char*, char*, unsigned);   //创建或者更新边
extern "C" __declspec(dllexport) unsigned GetTourGuide(char*);                     //获得导游图
extern "C" __declspec(dllexport) unsigned GetLoopGraph(char*);					   //获得回路
extern "C" __declspec(dllexport) unsigned MiniDistance(char*, char*, char*);	   //两景点间的最短路径和距离
extern "C" __declspec(dllexport) unsigned MiniSpanTree(char*);                     //建设规划，最小生成树
extern "C" __declspec(dllexport) unsigned SortByPopularity(char*);				   //根据欢迎度排序
extern "C" __declspec(dllexport) unsigned KeySearch(char*);						   //关键词搜索


int main()
{
	_CrtDumpMemoryLeaks(); //检测内存泄漏
	return 0;
}

//关键词搜索
extern "C" __declspec(dllexport) unsigned KeySearch(char* msg) {
	return graph->searchWithKeyWords(msg);
}

//根据欢迎度排序
extern "C" __declspec(dllexport) unsigned SortByPopularity(char* msg) {
	return graph->sortedByPopularity(msg);
}

//建设规划，最小生成树
extern "C" __declspec(dllexport) unsigned MiniSpanTree(char* msg) {
	return graph->miniSpanTree(msg);
}

//两景点间的最短路径和距离
extern "C" __declspec(dllexport) unsigned MiniDistance(char* msg, char* start, char* end) {
	return graph->miniDistanse(msg, start, end);
}

//获得回路
extern "C" __declspec(dllexport) unsigned GetLoopGraph(char* msg) {
	return graph->createLoopGraph(msg);
}

//获得导游图
extern "C" __declspec(dllexport) unsigned GetTourGuide(char* msg) {
	return graph->createTourGuide(msg);
}

//创建或者更新边
extern "C" __declspec(dllexport) unsigned CreateNewEdge(char* start, char* end, unsigned distance) {
	return graph->createEdge(start, end, distance);
}

//创建或者更新点
extern "C" __declspec(dllexport) unsigned CreateNewVertex(char* name, unsigned popu, char* info, bool r, bool w) {
	return graph->createVertex(name, popu, info, r, w);
}