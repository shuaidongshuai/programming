#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <cstdio>
#include <graphics.h>
#include <conio.h>

using namespace std;

class Mpu
{
public:
	string name;
	string date;
	int No;
	int degree;
};

class Man
{
public:
	void sortPowerAll()
	{
		map<int, Mpu *> powerMap;
		for (auto it = UserMap.begin(); it != UserMap.end(); ++it)
		{
			auto UserVec = it->second;
			powerMap[UserVec[UserVec.size() - 1]->degree] = UserVec[UserVec.size() - 1];
		}
		for (auto it = powerMap.rbegin(); it != powerMap.rend(); ++it)
		{
			cout << " 总用电量：" << it->second->degree << endl << endl;
		}
	}
	int getMonth(string date)
	{
		int start = date.find('-') + 1;
		int end = date.find('-', start);
		string monthStr(date.begin() + start, date.begin() + end);
		stringstream ss;
		int monthInt;
		ss << monthStr;
		ss >> monthInt;
		return monthInt;
	}
	int countPowerUse(string name, int startMonth, int endMonth)
	{
		if (UserMap.empty() || name.empty() || startMonth < 1 || startMonth > endMonth ||
			endMonth > 12 || UserMap.find(name) == UserMap.end())
			return -1;
		vector<Mpu *> userVec = UserMap[name];
		int startPower, endPower;
		for (auto it = userVec.begin(); it != userVec.end(); ++it)
		{
			int month = getMonth((*it)->date);
			if (month == startMonth)
				startPower = (*it)->degree;
			else if (month == endMonth + 1)
				endPower = (*it)->degree;
		}
		return endPower - startPower;
	}
	int getPowerUseByNo(int No, int startMonth, int endMonth)
	{
		int sumPower = 0;
		for (auto it = UserMap.begin(); it != UserMap.end(); ++it)
		{
			vector<Mpu *> userVec = it->second;
			if (No == userVec[0]->No)
				sumPower += countPowerUse(userVec[userVec.size() - 1]->name, startMonth, endMonth);
		}
		return sumPower == 0 ? -1 : sumPower;
	}
	map<int, double> getAllNoPower()
	{
		map<int, double> noPowerMap;
		int sumPower = 0;
		for (auto it = UserMap.begin(); it != UserMap.end(); ++it)
		{
			vector<Mpu *> userVec = it->second;
			if (noPowerMap.find(userVec[0]->No) == noPowerMap.end())
				noPowerMap[userVec[0]->No] = userVec[userVec.size() - 1]->degree;
			else
				noPowerMap[userVec[0]->No] += userVec[userVec.size() - 1]->degree;

			sumPower += userVec[userVec.size() - 1]->degree;
		}
		for (auto it = noPowerMap.begin(); it != noPowerMap.end(); ++it)
		{
			it->second = it->second / sumPower * 360;
		}
		return noPowerMap;
	}
	map<string, vector<Mpu *>> UserMap;
};

class MyGreaphic
{
public:
	void show(map<int, double> anglgMap)
	{
		initgraph(1000, 600);
		setorigin(500, 300);
		//setbkcolor(0xFFFFFF);

		double val = PI / 180;
		double curAngle = 0;

		auto it = anglgMap.begin();
		line(0, 0, 0, -200);
		setcolor(0x4941F2);
		settextstyle(50, 0, "黑体");
		char *word = new char[20];
		sprintf(word, "%.2lf", it->second / 360);
		outtextxy(-100, -250, word);

		for (++it; it != anglgMap.end(); ++it)
		{
			curAngle += it->second;
			setcolor(0x4941F2);
			settextstyle(50, 0, "黑体");
			char *word = new char[20];
			sprintf(word, "%.2lf",it->second / 360);

			outtextxy(1.2 * R * sin(curAngle * val), -0.5 * R * cos(curAngle* val), word);

			setcolor(0xFFFFFF);
			line(0, 0, R * sin(curAngle * val), -R * cos(curAngle * val));
		}
		setcolor(0x6FDAFF);
		circle(0, 0, 200);
	}
	const int R = 200;
	const double PI = 3.14159265;
};

int main()
{
	Man *manage = new Man;
	int startMonth, endMonth, No;
	string user;
	cout << "请输入：用户名，楼栋号，抄表日期，电表读数" << endl;
	while (1)
	{
		Mpu *mpu = new Mpu;
		if (cin >> mpu->name >> mpu->No >> mpu->date >> mpu->degree)
		{
			map<string, vector<Mpu *>>::iterator it = manage->UserMap.find(mpu->name);
			if (it == manage->UserMap.end())
			{
				vector<Mpu *> v(1, mpu);
				manage->UserMap[mpu->name] = v;
			}
			else
			{
				manage->UserMap[mpu->name].push_back(mpu);
			}
		}
		else
			break;
	}
	cin.clear();
	cout << "从高到低排出每个用户的总用电量" << endl;
	manage->sortPowerAll();

	cout << "统计某用户某月的总用电量" << endl;
	cin >> user >> startMonth >> endMonth;
	cout << "用户：【" << user << "】" << startMonth << "月 -- " << endMonth << "月 "
		<< "总用电量【" << manage->countPowerUse(user, startMonth, endMonth) << "】" << endl << endl;

	cout << "统计某楼栋从某月到某月的总用电量" << endl;
	cin >> No >> startMonth >> endMonth;
	int sumPower = manage->getPowerUseByNo(No, startMonth, endMonth);
	if (sumPower == -1)
	{
		cout << "没有这栋楼" << endl;
		return 0;
	}
	cout << "楼号：【" << No << "】 " << startMonth << "月 -- " << endMonth << "月 " << "总用电量【" << sumPower << "】" << endl << endl;
	system("pause");

	MyGreaphic g;
	g.show(manage->getAllNoPower());

	
	system("pause");
	return 0;
}
/*
石一凡 1 2016-1-1 300
王帅 1 2016-1-1 300
姚烨 2 2016-1-1 300
白杨 3 2016-1-1 300

石一凡 1 2016-2-1 520
王帅 1 2016-2-1 510
姚烨 2 2016-2-1 620
白杨 3 2016-2-1 550

石一凡 1 2016-3-1 720
王帅 1 2016-3-1 710
姚烨 2 2016-3-1 820
白杨3 2016-3-1 750

*/