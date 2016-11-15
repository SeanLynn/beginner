#pragma once

#include <string>
#include <chrono>
#include <iostream>
#include <stack>
#include <iomanip>
#include <queue>
using std::cout;
using std::endl;
using std::string;
struct car {

	car(string l, std::chrono::system_clock::time_point s):
		license(l), start(s){}

	string license;
	std::chrono::system_clock::time_point start;
};

class parkingLot {
public:
	void management();   //管理程序入口
	parkingLot(unsigned s = 5):size(s) {}      //构造函数
private:
	unsigned size;
	stack<car*> carStack;
	queue<car*> carQueue;
	void pushBackCar();  //汽车进车场
	void printWelcome(); //打印欢迎词
};

//管理程序入口
void parkingLot::management() {

	while (true) {
		char select;

		cin >> select;
		if (select == 'A') {
			pushBackCar();
		}


		//std::chrono::system_clock::time_point t2 = std::chrono::system_clock::now();
		//cout << (t2 - t1).count() << " tick count" << endl;
		//cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " microseconds" << endl;
	}
}

//打印欢迎词
void parkingLot::printWelcome() {
	cout << "\t\t\t** 停车场管理程序 **\n";
	cout << "=========================================================\n";
	cout << "**\t\t\t\t\t**\n";
	cout << "**\tA --- 汽车 进 车场\tD --- 汽车 出 车场\t**\n";
	cout << "**\t\t\t\t\t**\n";
	cout << "**\t\t\tE --- 退出\t程序\t\t\t**\n";
	cout << "=========================================================" << endl;
	cout << " 请选择：<A,D,E>:";
}

//汽车进车场
void parkingLot::pushBackCar() {
	string lic;
	cin >> lic;
	auto time = std::chrono::system_clock::now();
	auto t = chrono::system_clock::to_time_t(time);
	car* r = new car(lic, time);
	cout << "进场的时刻：" << std::put_time(std::localtime(&t), "%Y-%m-%d %X") << endl;
	if (carStack.size() < size) {
		carStack.push(r);
	}else {
		carQueue.push(r);
	}
}
