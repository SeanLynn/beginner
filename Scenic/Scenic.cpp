// Scenic.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "distributionGraph.h"
#include <memory>
#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>
void welcomeWords();
int main()
{
	{
		shared_ptr<distributionGraph> graph = make_shared<distributionGraph>();
		while (true) {
			int cmd;
			welcomeWords();
			cin >> cmd;
			switch (cmd)
			{
			case 0:
				break;
			case 1:
				graph->createGraph();
				break;
			case 2:
				graph->outputGraph();
				break;
			case 3:
				graph->creatTourSortGraph();
				break;
			case 4:
				graph->topoSort();
				break;
			case 5:
				graph->miniDistanse();
				break;
			case 6:
				graph->miniSpanTree();
				break;
			case 7:
				graph->sortedByPopularity();
				break;
			case 8:
				graph->searchWithKeyWords();
				break;
			case 9:
				graph->parkingLotMagm();
				break;
			default:
				break;
			}
			if (cmd < 1 || cmd > 9)
				break;
			Sleep(500);
		}
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

void welcomeWords() {
	cout << "================================\n";
	cout << "     欢迎使用景区信息管理系统\n";
	cout << "         ***请选择菜单***\n";
	cout << "================================\n";
	cout << "1、创建景区景点分布图。\n";
	cout << "2、输出景区景点分布图。\n";
	cout << "3、输出导游线路图。\n";
	cout << "4、输出导游线路图中的回路。\n";
	cout << "5、求两个景点间的最短路径和最短距离。\n";
	cout << "6、输出道路修建规划图。\n";
	cout << "7、按景点欢迎度进行排序并输出。\n";
	cout << "8、根据用户输入的关键字进行景点的查找。\n";
	cout << "9、停车场车辆进出记录信息。\n";
	cout << "0、退出系统。" << endl;
	cout << "请输入您要选择的菜单项：";
}