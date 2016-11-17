#pragma once

#include <Windows.h>
#include <chrono>
#include <queue>
#include <stack>
#include <queue>
#include <string>
#include <memory>
using std::string;
using std::shared_ptr;
struct car {
	car(string l, std::chrono::system_clock::time_point s):
		license(l), start(s){}

	string license;
	std::chrono::system_clock::time_point start;
};

class parkingLot {
public:
	void management();   //管理程序入口
	parkingLot(unsigned s = 5) : capacity(s) {}      //构造函数
private:
	unsigned capacity;		  //停车场容量
	std::stack<shared_ptr<car>> carStack; //停车场
	std::queue<shared_ptr<car>> carQueue; //便道
	void pushBackCar();  //车辆进车场函数接口
	void popBackCar();   //车辆出车场函数接口
	void printWelcome(); //打印欢迎词
	unsigned long long parkingCost(long long);//计算停车消费
	void pushBack(shared_ptr<car>); //车辆进车场
	bool popBack(const string&); //车辆出车场
	void getLocalTime(__time64_t, char*); //获取本地时间
};