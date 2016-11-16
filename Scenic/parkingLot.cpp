#include "stdafx.h"
#include "parkingLot.h"
#include <string>
#include <iostream>
#include <stack>
#include <iomanip>
#include <time.h>
using std::cout;
using std::endl;
using std::cin;
using std::string;
//管理程序入口
void parkingLot::management() {
	while (true) {
		printWelcome();
		char select;
		cin >> select;
		if (select == 'A') {
			pushBackCar();
		}
		else if (select == 'D') {
			popBackCar();
		}
		else if (select == 'E') {
			break;
		}
	}
}

//打印欢迎词
inline void parkingLot::printWelcome() {
	cout << "\t\t** 停车场管理程序 **\n";
	cout << "============================================================\n";
	cout << "**\t\t\t\t\t\t\t**\n";
	cout << "**\tA --- 汽车 进 车场\tD --- 汽车 出 车场\t**\n";
	cout << "**\t\t\t\t\t\t\t**\n";
	cout << "**\t\t\tE --- 退出 程序\t\t\t**\n";
	cout << "============================================================" << endl;
	cout << " 请选择：<A,D,E>:";
}

//汽车出车场函数接口，只对数据结构作微小的改变
void parkingLot::popBackCar() {
	if (carStack.empty()) {
		cout << "停车场是空的。\n" << endl;
		//cout << "=========================================================" << endl;
		return;
	}
	string lic;
	cout << "出场车辆牌号：";
	cin >> lic;

	if (popBack(lic) && !carQueue.empty()) { //popBack成功并且便道上有车
		car* r = carQueue.front();
		r->start = std::chrono::system_clock::now(); //重置进场时间
		carQueue.pop();
		cout << "进场车牌为：" << r->license << endl;
		pushBack(r);
	}
}

//汽车出车场
bool parkingLot::popBack(const string& lic) {

	std::stack<car*> tempCarStack;
	car* r = nullptr;
	unsigned size = carStack.size();
	for (unsigned i = 0; i < size; ++i) {
		car* tempCar = carStack.top();
		if (tempCar->license == lic) {
			r = tempCar;
			carStack.pop();
			break;
		}
		tempCarStack.push(tempCar);
		carStack.pop();
	}
	//复原carStack
	while (!tempCarStack.empty()) {
		carStack.push(tempCarStack.top());
		tempCarStack.pop();
	}

	if (r == nullptr) //如果找不到licence为lic的car
		return false;

	auto end = std::chrono::system_clock::now(); //出场时间
	auto t = std::chrono::system_clock::to_time_t(end); //转化时间格式
	auto parkingTime = std::chrono::duration_cast<std::chrono::seconds>(end - r->start).count();//停留时间

																								//出场时间转换成本地时间
	char buf[32];
	getLocalTime(t, buf);

	cout << "下面是离开停车场的车辆信息：" << endl;
	cout << "车辆牌号：" << r->license << endl;
	cout << "出场的时刻:" << *buf << endl;
	cout << "停车时长：" << parkingTime << " seconds" << endl;//停留时间
	cout << "停车花费：" << parkingCost(parkingTime) << " 元。\n" << endl;	//计算停车消费
																	//cout << "=========================================================" << endl;
	return true;
}

//汽车进车场
void parkingLot::pushBackCar() {
	//以下输入车辆信息并创建车辆
	string lic;
	cout << "进场车牌为：";
	cin >> lic;
	auto time = std::chrono::system_clock::now();

	//添加进车辆栈，并输出相关信息
	pushBack(new car(lic, time));
}

//汽车进车场
void parkingLot::pushBack(car* r) {
	if (carStack.size() < capacity) {
		carStack.push(r);
		auto t = std::chrono::system_clock::to_time_t(r->start); //把时间转换成数字
		char buf[32];
		getLocalTime(t, buf);
		//输出车辆进场时间信息和位置信息
		cout << "进场的时刻：" << buf;
		cout << "该车已进入停车场在：" << carStack.size() << "号车道\n" << endl;
	}
	else {
		carQueue.push(r);
		cout << "停车场已满，该车停在便道上。\n" << endl;
	}
	Sleep(500);
	//cout << "=========================================================\n" << endl;
}


//计算停车消费
inline unsigned long long parkingLot::parkingCost(long long parkingTime) {
	return (unsigned long long)parkingTime * 2;
}


inline void parkingLot::getLocalTime(__time64_t t, char* buf) {
	struct tm newtime;
	localtime_s(&newtime, &t);
	asctime_s(buf, 32, &newtime);
}

//析构函数
parkingLot::~parkingLot() {
	for_each(carStack._Get_container().begin(), carStack._Get_container().end(), [](car* r) {delete r;});
	for_each(carQueue._Get_container().begin(), carQueue._Get_container().end(), [](car* r) {delete r;});
}
