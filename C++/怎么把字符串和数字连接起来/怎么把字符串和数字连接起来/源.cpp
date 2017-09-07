#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
using namespace std;

//第一种C风格的转化(以前一直喜欢的  sprintf 功能强大)
void test()
{
	char *s = "dong";
	int a = 52;
	float b = .1314;
	char *buf = new char[strlen(s) + sizeof(a) + 1];
	sprintf(buf, "%s%d%.4f", s, a, b);
	printf("%s\n", buf);
}
//半C半C++风格
void test1()
{
	string s = "dong";
	int a = 520;
	char *buf = new char[10];//2147483647 int最大值
	_itoa(a, buf, 10);		//itoa虽然可以转化为各种进制，但是注意不能是float或者double
	s += buf;
	cout << s << "\t";
	_itoa(a, buf, 16);
	s += buf;
	cout << s << endl;
}
//纯C++风格
void test2()
{
	string s = "陈明东";
	int a = 52;
	double b = .1314;
	ostringstream oss;
	oss << s << a << b << endl;
	s = oss.str();
	cout << s << endl;
}
int main()
{
	test();
	test1();
	test2();
	return 0;
}
/*
dong520.1314
dong520 dong520208
陈明东520.1314
*/