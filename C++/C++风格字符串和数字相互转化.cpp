#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//数字转化为字符串 
void test1(){
	int a = 20;
	double b = 80.88;
	string res;
	stringstream ss;

	ss << a;
	ss >> res;
	cout << res << endl;

	ss.clear();

	ss << b;
	ss >> res;
	cout << res << endl;
}
//字符串转化为数字 
void test2(){
	string a = "20";
	string b = "80.88";
	int res1;
	double res2;
	stringstream ss;

	ss << a;
	ss >> res1;
	cout << res1 << endl;

	ss.clear();

	ss << b;
	ss >> res2;
	cout << res2 << endl;
}
//还可以连接字符串和数字
void test3(){
	ostringstream oss;
	oss << "chen " << 5 << " ming " << 2.1 << " dong";
	cout << oss.str() << endl;
}
int main(){
	test1();
	cout << "----------" << endl;
	test2();
	cout << "----------" << endl;
	test3();
}
/*
20
80.88
----------
20
80.88
----------
chen 5 ming 2.1 dong
*/
